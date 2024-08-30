/*!
 * @file CodeTester.cpp
 * The CodeTester is a utility to run the output of the compiler as part of a unit test.
 * This is effective for tests which try all combinations of registers, etc.
 *
 * The CodeTester can't be used for tests requiring the full GOAL language/linking.
 */

#include "common/common_types.h"

#include "goalc/emitter/Instruction.h"
#ifdef OS_POSIX
#include <sys/mman.h>
#elif _WIN32
#include "third-party/mman/mman.h"
#endif

#include <cstdio>

#include "CodeTester.h"
#include "IGen.h"

#include "fmt/core.h"

namespace emitter {

CodeTester::CodeTester() : m_info(RegisterInfo::make_register_info()) {}

/*!
 * Convert to a string for comparison against an assembler or tests.
 */
std::string CodeTester::dump_to_hex_string(bool nospace) {
  std::string result;
  char buff[32];
  for (int i = 0; i < code_buffer_size; i++) {
    if (nospace) {
      sprintf(buff, "%02X", code_buffer[i]);
    } else {
      sprintf(buff, "%02x ", code_buffer[i]);
    }

    result += buff;
  }

  // remove trailing space
  if (!nospace && !result.empty()) {
    result.pop_back();
  }
  return result;
}

/*!
 * Add an instruction to the buffer.
 */
void CodeTester::emit(const emitter::Instruction* instr) {
  code_buffer_size += instr->emit(code_buffer + code_buffer_size);
  ASSERT(code_buffer_size <= code_buffer_capacity);
}

/*!
 * Add a return instruction to the buffer.
 */
void CodeTester::emit_return() {
  emit(IGen::ret());
}

/*!
 * Pop all GPRs off of the stack. Optionally exclude rax.
 * Pops RSP always, which is weird, but doesn't cause issues.
 */
void CodeTester::emit_pop_all_gprs(bool exclude_rax) {
#ifndef __aarch64__
  for (int i = 16; i-- > 0;) {
    if (i != RAX || !exclude_rax) {
      emit(IGen::pop_gpr64(i));
    }
  }
#else
  // TODO find uses for excluding RAX
  for (int i = 0; i < 32; i++) {
    emit(IGen::pop_gpr64(i));
  }
#endif
}

/*!
 * Push all GPRs onto the stack. Optionally exclude RAX.
 * Pushes RSP always, which is weird, but doesn't cause issues.
 */
void CodeTester::emit_push_all_gprs(bool exclude_rax) {
#ifndef __aarch64__
  for (int i = 0; i < 16; i++) {
    if (i != RAX || !exclude_rax) {
      emit(IGen::push_gpr64(i));
    }
  }
#else
  // TODO find uses for excluding RAX
  for (int i = 0; i < 32; i++) {
    emit(IGen::push_gpr64(i));
  }
#endif
}

/*!
 * Push all xmm registers (all 128-bits) to the stack.
 */
void CodeTester::emit_push_all_xmms() {
  emit(IGen::sub_gpr64_imm8s(RSP, 8));
  for (int i = 0; i < 16; i++) {
    emit(IGen::sub_gpr64_imm8s(RSP, 16));
    emit(IGen::store128_gpr64_xmm128(RSP, XMM0 + i));
  }
}

/*!
 * Pop all xmm registers (all 128-bits) from the stack
 */
void CodeTester::emit_pop_all_xmms() {
  for (int i = 0; i < 16; i++) {
    emit(IGen::load128_xmm128_gpr64(XMM0 + i, RSP));
    emit(IGen::add_gpr64_imm8s(RSP, 16));
  }
  emit(IGen::add_gpr64_imm8s(RSP, 8));
}

/*!
 * Remove everything from the code buffer
 */
void CodeTester::clear() {
  code_buffer_size = 0;
}

/*!
 * Execute the buffered code with no arguments, return the value of RAX.
 */
u64 CodeTester::execute() {
#if defined(__APPLE__) && defined(__aarch64__)
  mprotect(code_buffer, code_buffer_capacity, PROT_EXEC | PROT_READ);
  auto ret = ((u64(*)())code_buffer)();
  mprotect(code_buffer, code_buffer_capacity, PROT_WRITE | PROT_READ);
  return ret;
#else
  return ((u64(*)())code_buffer)();
#endif
}

/*!
 * Execute code buffer with arguments. Use get_c_abi_arg to figure out which registers the
 * arguments will appear in (will handle windows/linux differences)
 */
u64 CodeTester::execute(u64 in0, u64 in1, u64 in2, u64 in3) {
#if defined(__APPLE__) && defined(__aarch64__)
  mprotect(code_buffer, code_buffer_capacity, PROT_EXEC | PROT_READ);
  auto ret = ((u64(*)(u64, u64, u64, u64))code_buffer)(in0, in1, in2, in3);
  mprotect(code_buffer, code_buffer_capacity, PROT_WRITE | PROT_READ);
  return ret;
#else
  return ((u64(*)(u64, u64, u64, u64))code_buffer)(in0, in1, in2, in3);
#endif
}

/*!
 * Allocate a code buffer of the given size.
 */
void CodeTester::init_code_buffer(int capacity) {
// TODO Apple Silicone - You cannot make a page be RWX,
// or more specifically it can't be both writable and executable at the same time
//
// https://github.com/zherczeg/sljit/issues/99
//
// The solution to this is to flip-flop between permissions, or perhaps have two threads
// one that has writing permission, and another with executable permission
#if defined(__APPLE__) && defined(__aarch64__)
  code_buffer =
      (u8*)mmap(nullptr, capacity, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
#else
  code_buffer = (u8*)mmap(nullptr, capacity, PROT_EXEC | PROT_READ | PROT_WRITE,
                          MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
#endif
  if (code_buffer == (u8*)(-1)) {
    ASSERT_MSG(false, "[CodeTester] Failed to map memory!");
  }

  code_buffer_capacity = capacity;
  code_buffer_size = 0;
}

CodeTester::~CodeTester() {
  if (code_buffer_capacity) {
    munmap(code_buffer, code_buffer_capacity);
  }
}
}  // namespace emitter
