#pragma once

#include "IGenX86.h"

#include <stdexcept>

#include "Instruction.h"
#include "Register.h"

#include "common/util/Assert.h"

namespace emitter {
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   MOVES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*!
 * Move data from src to dst. Moves all 64-bits of the GPR.
 */
Instruction* IGenX86::mov_gpr64_gpr64(Register dst, Register src) {
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, true);
  return instr;
}

/*!
 * Move a 64-bit constant into a register.
 */
Instruction* IGenX86::mov_gpr64_u64(Register dst, uint64_t val) {
  ASSERT(dst.is_gpr());
  bool rex_b = false;
  auto dst_hw_id = dst.hw_id();
  if (dst_hw_id >= 8) {
    dst_hw_id -= 8;
    rex_b = true;
  }
  auto instr = new InstructionX86(0xb8 + dst_hw_id);
  instr->set(REX(true, false, false, rex_b));
  instr->set(Imm(8, val));
  return instr;
}

/*!
 * Move a 32-bit constant into a register. Zeros the upper 32 bits.
 */
Instruction* IGenX86::mov_gpr64_u32(Register dst, uint64_t val) {
  ASSERT(val <= UINT32_MAX);
  ASSERT(dst.is_gpr());
  auto dst_hw_id = dst.hw_id();
  bool rex_b = false;
  if (dst_hw_id >= 8) {
    dst_hw_id -= 8;
    rex_b = true;
  }

  auto instr = new InstructionX86(0xb8 + dst_hw_id);
  if (rex_b) {
    instr->set(REX(false, false, false, rex_b));
  }
  instr->set(Imm(4, val));
  return instr;
}

/*!
 * Move a signed 32-bit constant into a register. Sign extends for the upper 32 bits.
 * When possible prefer mov_gpr64_u32. (use this only for negative values...)
 * This is always bigger than mov_gpr64_u32, but smaller than a mov_gpr_u64.
 */
Instruction* IGenX86::mov_gpr64_s32(Register dst, int64_t val) {
  ASSERT(val >= INT32_MIN && val <= INT32_MAX);
  ASSERT(dst.is_gpr());
  auto instr = new InstructionX86(0xc7);
  instr->set_modrm_and_rex(0, dst.hw_id(), 3, true);
  instr->set(Imm(4, val));
  return instr;
}

/*!
 * Move 32-bits of xmm to 32 bits of gpr (no sign extension).
 */
Instruction* IGenX86::movd_gpr32_xmm32(Register dst, Register src) {
  ASSERT(dst.is_gpr());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x0f);
  instr->set_op3(0x7e);
  instr->set_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Move 32-bits of gpr to 32-bits of xmm (no sign extension)
 */
Instruction* IGenX86::movd_xmm32_gpr32(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_gpr());
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x0f);
  instr->set_op3(0x6e);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Move 64-bits of xmm to 64 bits of gpr (no sign extension).
 */
Instruction* IGenX86::movq_gpr64_xmm64(Register dst, Register src) {
  ASSERT(dst.is_gpr());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x0f);
  instr->set_op3(0x7e);
  instr->set_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, true);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Move 64-bits of gpr to 64-bits of xmm (no sign extension)
 */
Instruction* IGenX86::movq_xmm64_gpr64(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_gpr());
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x0f);
  instr->set_op3(0x6e);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Move 32-bits between xmm's
 */
Instruction* IGenX86::mov_xmm32_xmm32(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

// todo - GPR64 -> XMM64 (zext)
// todo - XMM -> GPR64

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   GOAL Loads and Stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * movsx dst, BYTE PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load8s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbe);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true,
                                                 false);
  return instr;
}

Instruction* IGenX86::store8_gpr64_gpr64_plus_gpr64(Register addr1,
                                                    Register addr2,
                                                    Register value) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x88);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(value.hw_id(), addr1.hw_id(), addr2.hw_id());
  if (value.real_id() > R3) {
    instr->add_rex();
  }
  return instr;
}

Instruction* IGenX86::load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                            Register addr1,
                                                            Register addr2,
                                                            s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbe);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                            Register addr2,
                                                            Register value,
                                                            s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x88);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);
  if (value.real_id() > R3) {
    instr->add_rex();
  }
  return instr;
}

Instruction* IGenX86::load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbe);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

Instruction* IGenX86::store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                             Register addr2,
                                                             Register value,
                                                             s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x88);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, false);
  if (value.real_id() > R3) {
    instr->add_rex();
  }
  return instr;
}

/*!
 * movzx dst, BYTE PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load8u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb6);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true,
                                                 false);
  return instr;
}

Instruction* IGenX86::load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                            Register addr1,
                                                            Register addr2,
                                                            s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb6);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb6);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

/*!
 * movsx dst, WORD PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load16s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbf);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true,
                                                 false);
  return instr;
}

Instruction* IGenX86::store16_gpr64_gpr64_plus_gpr64(Register addr1,
                                                     Register addr2,
                                                     Register value) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(value.hw_id(), addr1.hw_id(), addr2.hw_id());
  instr->swap_op0_rex();  // why?????
  return instr;
}

Instruction* IGenX86::store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                             Register addr2,
                                                             Register value,
                                                             s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);
  instr->swap_op0_rex();  // why?????
  return instr;
}

Instruction* IGenX86::store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, false);
  instr->swap_op0_rex();  // why?????
  return instr;
}

Instruction* IGenX86::load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbf);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbf);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

/*!
 * movzx dst, WORD PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load16u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb7);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true,
                                                 false);
  return instr;
}

Instruction* IGenX86::load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb7);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb7);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

/*!
 * movsxd dst, DWORD PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load32s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x63);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true);
  return instr;
}

Instruction* IGenX86::store32_gpr64_gpr64_plus_gpr64(Register addr1,
                                                     Register addr2,
                                                     Register value) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(value.hw_id(), addr1.hw_id(), addr2.hw_id());
  return instr;
}

Instruction* IGenX86::load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x63);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                             Register addr2,
                                                             Register value,
                                                             s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);
  return instr;
}

Instruction* IGenX86::load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x63);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

Instruction* IGenX86::store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, false);
  return instr;
}

/*!
 * movzxd dst, DWORD PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load32u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id());
  return instr;
}

Instruction* IGenX86::load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);
  return instr;
}

Instruction* IGenX86::load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, false);
  return instr;
}

/*!
 * mov dst, QWORD PTR [addr1 + addr2]
 * addr1 and addr2 have to be different registers.
 * Cannot use rsp.
 */
Instruction* IGenX86::load64_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(), true);
  return instr;
}

Instruction* IGenX86::store64_gpr64_gpr64_plus_gpr64(Register addr1,
                                                     Register addr2,
                                                     Register value) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(value.hw_id(), addr1.hw_id(), addr2.hw_id(), true);
  return instr;
}

Instruction* IGenX86::load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                            Register addr1,
                                                            Register addr2,
                                                            s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                             Register addr2,
                                                             Register value,
                                                             s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, true);
  return instr;
}

Instruction* IGenX86::load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

Instruction* IGenX86::store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) {
  ASSERT(value.is_gpr());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, true);
  return instr;
}

Instruction* IGenX86::store_goal_vf(Register addr, Register value, Register off, s64 offset) {
  if (offset == 0) {
    return storevf_gpr64_plus_gpr64(value, addr, off);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return storevf_gpr64_plus_gpr64_plus_s8(value, addr, off, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return storevf_gpr64_plus_gpr64_plus_s32(value, addr, off, offset);
  }
  ASSERT(false);
  return new InstructionX86(0b0);
}

Instruction* IGenX86::store_goal_gpr(Register addr,
                                     Register value,
                                     Register off,
                                     int offset,
                                     int size) {
  switch (size) {
    case 1:
      if (offset == 0) {
        return store8_gpr64_gpr64_plus_gpr64(addr, off, value);
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        return store8_gpr64_gpr64_plus_gpr64_plus_s8(addr, off, value, offset);
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        return store8_gpr64_gpr64_plus_gpr64_plus_s32(addr, off, value, offset);
      } else {
        ASSERT(false);
      }
    case 2:
      if (offset == 0) {
        return store16_gpr64_gpr64_plus_gpr64(addr, off, value);
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        return store16_gpr64_gpr64_plus_gpr64_plus_s8(addr, off, value, offset);
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        return store16_gpr64_gpr64_plus_gpr64_plus_s32(addr, off, value, offset);
      } else {
        ASSERT(false);
      }
    case 4:
      if (offset == 0) {
        return store32_gpr64_gpr64_plus_gpr64(addr, off, value);
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        return store32_gpr64_gpr64_plus_gpr64_plus_s8(addr, off, value, offset);
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        return store32_gpr64_gpr64_plus_gpr64_plus_s32(addr, off, value, offset);
      } else {
        ASSERT(false);
      }
    case 8:
      if (offset == 0) {
        return store64_gpr64_gpr64_plus_gpr64(addr, off, value);
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        return store64_gpr64_gpr64_plus_gpr64_plus_s8(addr, off, value, offset);
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        return store64_gpr64_gpr64_plus_gpr64_plus_s32(addr, off, value, offset);
      } else {
        ASSERT(false);
      }
    default:
      ASSERT(false);
      return new InstructionX86(0);
  }
}

Instruction* IGenX86::load_goal_xmm128(Register dst, Register addr, Register off, int offset) {
  if (offset == 0) {
    return loadvf_gpr64_plus_gpr64(dst, addr, off);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return loadvf_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return loadvf_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

/*!
 * Load memory at addr + offset, where addr is a GOAL pointer and off is the offset register.
 * This will pick the appropriate fancy addressing mode instruction.
 */
Instruction* IGenX86::load_goal_gpr(Register dst,
                                    Register addr,
                                    Register off,
                                    int offset,
                                    int size,
                                    bool sign_extend) {
  switch (size) {
    case 1:
      if (offset == 0) {
        if (sign_extend) {
          return load8s_gpr64_gpr64_plus_gpr64(dst, addr, off);
        } else {
          return load8u_gpr64_gpr64_plus_gpr64(dst, addr, off);
        }
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        if (sign_extend) {
          return load8s_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        } else {
          return load8u_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        }
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        if (sign_extend) {
          return load8s_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        } else {
          return load8u_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        }
      } else {
        ASSERT(false);
      }
    case 2:
      if (offset == 0) {
        if (sign_extend) {
          return load16s_gpr64_gpr64_plus_gpr64(dst, addr, off);
        } else {
          return load16u_gpr64_gpr64_plus_gpr64(dst, addr, off);
        }
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        if (sign_extend) {
          return load16s_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        } else {
          return load16u_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        }
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        if (sign_extend) {
          return load16s_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        } else {
          return load16u_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        }
      } else {
        ASSERT(false);
      }
    case 4:
      if (offset == 0) {
        if (sign_extend) {
          return load32s_gpr64_gpr64_plus_gpr64(dst, addr, off);
        } else {
          return load32u_gpr64_gpr64_plus_gpr64(dst, addr, off);
        }
      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        if (sign_extend) {
          return load32s_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        } else {
          return load32u_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);
        }
      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        if (sign_extend) {
          return load32s_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        } else {
          return load32u_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);
        }
      } else {
        ASSERT(false);
      }
    case 8:
      if (offset == 0) {
        return load64_gpr64_gpr64_plus_gpr64(dst, addr, off);

      } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
        return load64_gpr64_gpr64_plus_gpr64_plus_s8(dst, addr, off, offset);

      } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
        return load64_gpr64_gpr64_plus_gpr64_plus_s32(dst, addr, off, offset);

      } else {
        ASSERT(false);
      }
    default:
      ASSERT(false);
      return new InstructionX86(0);
  }
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - XMM32
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* IGenX86::store32_xmm32_gpr64_plus_gpr64(Register addr1,
                                                     Register addr2,
                                                     Register xmm_value) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(xmm_value.hw_id(), addr1.hw_id(), addr2.hw_id());

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load32_xmm32_gpr64_plus_gpr64(Register xmm_dest,
                                                    Register addr1,
                                                    Register addr2) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_and_rex_for_reg_plus_reg_addr(xmm_dest.hw_id(), addr1.hw_id(), addr2.hw_id());

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                             Register addr2,
                                                             Register xmm_value,
                                                             s64 offset) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(xmm_value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                            Register addr1,
                                                            Register addr2,
                                                            s64 offset) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s8(xmm_dest.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                    offset, false);

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                              Register addr2,
                                                              Register xmm_value,
                                                              s64 offset) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(xmm_value.hw_id(), addr1.hw_id(),
                                                     addr2.hw_id(), offset, false);

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::lea_reg_plus_off32(Register dest, Register base, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8d);
  instr->set_modrm_rex_sib_for_reg_reg_disp(dest.hw_id(), 2, base.hw_id(), true);
  instr->set(Imm(4, offset));
  return instr;
}

Instruction* IGenX86::lea_reg_plus_off8(Register dest, Register base, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x8d);
  instr->set_modrm_rex_sib_for_reg_reg_disp(dest.hw_id(), 1, base.hw_id(), true);
  instr->set(Imm(1, offset));
  return instr;
}

Instruction* IGenX86::lea_reg_plus_off(Register dest, Register base, s64 offset) {
  if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return lea_reg_plus_off8(dest, base, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return lea_reg_plus_off32(dest, base, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

Instruction* IGenX86::store32_xmm32_gpr64_plus_s32(Register base, Register xmm_value, s64 offset) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_value.hw_id(), 2, base.hw_id(), false);
  instr->set(Imm(4, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store32_xmm32_gpr64_plus_s8(Register base, Register xmm_value, s64 offset) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_value.hw_id(), 1, base.hw_id(), false);
  instr->set(Imm(1, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_and_rex_for_reg_plus_reg_plus_s32(xmm_dest.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     offset, false);

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load32_xmm32_gpr64_plus_s32(Register xmm_dest, Register base, s64 offset) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_dest.hw_id(), 2, base.hw_id(), false);
  instr->set(Imm(4, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(base.is_gpr());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_dest.hw_id(), 1, base.hw_id(), false);
  instr->set(Imm(1, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load_goal_xmm32(Register xmm_dest, Register addr, Register off, s64 offset) {
  if (offset == 0) {
    return load32_xmm32_gpr64_plus_gpr64(xmm_dest, addr, off);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return load32_xmm32_gpr64_plus_gpr64_plus_s8(xmm_dest, addr, off, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return load32_xmm32_gpr64_plus_gpr64_plus_s32(xmm_dest, addr, off, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

Instruction* IGenX86::store_goal_xmm32(Register addr,
                                       Register xmm_value,
                                       Register off,
                                       s64 offset) {
  if (offset == 0) {
    return store32_xmm32_gpr64_plus_gpr64(addr, off, xmm_value);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return store32_xmm32_gpr64_plus_gpr64_plus_s8(addr, off, xmm_value, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return store32_xmm32_gpr64_plus_gpr64_plus_s32(addr, off, xmm_value, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

Instruction* IGenX86::store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) {
  ASSERT(base.is_gpr());
  ASSERT(xmm_value.is_128bit_simd());
  if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return store32_xmm32_gpr64_plus_s8(base, xmm_value, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return store32_xmm32_gpr64_plus_s32(base, xmm_value, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

Instruction* IGenX86::load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) {
  ASSERT(base.is_gpr());
  ASSERT(xmm_dest.is_128bit_simd());
  if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return load32_xmm32_gpr64_plus_s8(xmm_dest, base, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return load32_xmm32_gpr64_plus_s32(xmm_dest, base, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - XMM128
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * Store a 128-bit xmm into an address stored in a register, no offset
 */
Instruction* IGenX86::store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_value.is_128bit_simd());
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x7f);
  instr->set_modrm_and_rex_for_reg_addr(xmm_value.hw_id(), gpr_addr.hw_id(), false);
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store128_gpr64_xmm128_s32(Register gpr_addr, Register xmm_value, s64 offset) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x7f);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_value.hw_id(), 2, gpr_addr.hw_id(), false);
  instr->set(Imm(4, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store128_gpr64_xmm128_s8(Register gpr_addr, Register xmm_value, s64 offset) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x7f);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_value.hw_id(), 1, gpr_addr.hw_id(), false);
  instr->set(Imm(1, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_dest.is_128bit_simd());
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x6f);
  instr->set_modrm_and_rex_for_reg_addr(xmm_dest.hw_id(), gpr_addr.hw_id(), false);
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load128_xmm128_gpr64_s32(Register xmm_dest, Register gpr_addr, s64 offset) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x6f);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_dest.hw_id(), 2, gpr_addr.hw_id(), false);
  instr->set(Imm(4, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load128_xmm128_gpr64_s8(Register xmm_dest, Register gpr_addr, s64 offset) {
  ASSERT(gpr_addr.is_gpr());
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x66);
  //    InstructionX86 *instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x6f);
  instr->set_modrm_rex_sib_for_reg_reg_disp(xmm_dest.hw_id(), 1, gpr_addr.hw_id(), false);
  instr->set(Imm(1, offset));
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) {
  if (offset == 0) {
    return load128_xmm128_gpr64(xmm_dest, base);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return load128_xmm128_gpr64_s8(xmm_dest, base, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return load128_xmm128_gpr64_s32(xmm_dest, base, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

Instruction* IGenX86::store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) {
  if (offset == 0) {
    return store128_gpr64_xmm128(base, xmm_val);
  } else if (offset >= INT8_MIN && offset <= INT8_MAX) {
    return store128_gpr64_xmm128_s8(base, xmm_val, offset);
  } else if (offset >= INT32_MIN && offset <= INT32_MAX) {
    return store128_gpr64_xmm128_s32(base, xmm_val, offset);
  } else {
    ASSERT(false);
    return new InstructionX86(0);
  }
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   RIP loads and stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenX86::load64_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::load32s_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x63);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::load32u_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, false);
  return instr;
}

Instruction* IGenX86::load16u_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb7);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::load16s_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbf);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::load8u_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xb6);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::load8s_rip_s32(Register dest, s64 offset) {
  ASSERT(dest.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xbe);
  instr->set_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::static_load(Register dest, s64 offset, int size, bool sign_extend) {
  switch (size) {
    case 1:
      if (sign_extend) {
        return load8s_rip_s32(dest, offset);
      } else {
        return load8u_rip_s32(dest, offset);
      }
      break;
    case 2:
      if (sign_extend) {
        return load16s_rip_s32(dest, offset);
      } else {
        return load16u_rip_s32(dest, offset);
      }
      break;
    case 4:
      if (sign_extend) {
        return load32s_rip_s32(dest, offset);
      } else {
        return load32u_rip_s32(dest, offset);
      }
      break;
    case 8:
      return load64_rip_s32(dest, offset);
    default:
      ASSERT(false);
  }
}

Instruction* IGenX86::store64_rip_s32(Register src, s64 offset) {
  ASSERT(src.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_rip_plus_s32(src.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::store32_rip_s32(Register src, s64 offset) {
  ASSERT(src.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_and_rex_for_rip_plus_s32(src.hw_id(), offset, false);
  return instr;
}

Instruction* IGenX86::store16_rip_s32(Register src, s64 offset) {
  ASSERT(src.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x66);
  instr->set_op2(0x89);
  instr->set_modrm_and_rex_for_rip_plus_s32(src.hw_id(), offset, false);
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::store8_rip_s32(Register src, s64 offset) {
  ASSERT(src.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x88);
  instr->set_modrm_and_rex_for_rip_plus_s32(src.hw_id(), offset, false);
  if (src.real_id() > R3) {
    instr->add_rex();
  }
  return instr;
}

Instruction* IGenX86::static_store(Register value, s64 offset, int size) {
  switch (size) {
    case 1:
      return store8_rip_s32(value, offset);
    case 2:
      return store16_rip_s32(value, offset);
    case 4:
      return store32_rip_s32(value, offset);
    case 8:
      return store64_rip_s32(value, offset);
    default:
      ASSERT(false);
  }
}

Instruction* IGenX86::static_addr(Register dst, s64 offset) {
  ASSERT(dst.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x8d);
  instr->set_modrm_and_rex_for_rip_plus_s32(dst.hw_id(), offset, true);
  return instr;
}

Instruction* IGenX86::static_load_xmm32(Register xmm_dest, s64 offset) {
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x10);
  instr->set_modrm_and_rex_for_rip_plus_s32(xmm_dest.hw_id(), offset, false);

  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::static_store_xmm32(Register xmm_value, s64 offset) {
  ASSERT(xmm_value.is_128bit_simd());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x11);
  instr->set_modrm_and_rex_for_rip_plus_s32(xmm_value.hw_id(), offset, false);

  instr->swap_op0_rex();
  return instr;
}

// TODO, special load/stores of 128 bit values.

// TODO, consider specialized stack loads and stores?
Instruction* IGenX86::load64_gpr64_plus_s32(Register dst_reg, int32_t offset, Register src_reg) {
  ASSERT(dst_reg.is_gpr());
  ASSERT(src_reg.is_gpr());
  auto instr = new InstructionX86(0x8b);
  instr->set_modrm_rex_sib_for_reg_reg_disp(dst_reg.hw_id(), 2, src_reg.hw_id(), true);
  instr->set_disp(Imm(4, offset));
  return instr;
}

/*!
 * Store 64-bits from gpr into memory located at 64-bit reg + 32-bit signed offset.
 */
Instruction* IGenX86::store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) {
  ASSERT(addr.is_gpr());
  ASSERT(value.is_gpr());
  auto instr = new InstructionX86(0x89);
  instr->set_modrm_rex_sib_for_reg_reg_disp(value.hw_id(), 2, addr.hw_id(), true);
  instr->set_disp(Imm(4, offset));
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FUNCTION STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*!
 * Function return. Pops the 64-bit return address (real) off the stack and jumps to it.
 */
Instruction* IGenX86::ret() {
  return new InstructionX86(0xc3);
}

/*!
 * Instruction to push gpr (64-bits) onto the stack
 */
Instruction* IGenX86::push_gpr64(Register reg) {
  ASSERT(reg.is_gpr());
  if (reg.hw_id() >= 8) {
    auto i = new InstructionX86(0x50 + reg.hw_id() - 8);
    i->set(REX(false, false, false, true));
    return i;
  }
  return new InstructionX86(0x50 + reg.hw_id());
}

/*!
 * Instruction to pop 64 bit gpr from the stack
 */
Instruction* IGenX86::pop_gpr64(Register reg) {
  ASSERT(reg.is_gpr());
  if (reg.hw_id() >= 8) {
    auto i = new InstructionX86(0x58 + reg.hw_id() - 8);
    i->set(REX(false, false, false, true));
    return i;
  }
  return new InstructionX86(0x58 + reg.hw_id());
}

/*!
 * Call a function stored in a 64-bit gpr
 */
Instruction* IGenX86::call_r64(Register reg_) {
  ASSERT(reg_.is_gpr());
  auto reg = reg_.hw_id();
  auto instr = new InstructionX86(0xff);
  if (reg >= 8) {
    instr->set(REX(false, false, false, true));
    reg -= 8;
  }
  ASSERT(reg < 8);
  ModRM mrm;
  mrm.rm = reg;
  mrm.reg_op = 2;
  mrm.mod = 3;
  instr->set(mrm);
  return instr;
}

/*!
 * Jump to an x86-64 address stored in a 64-bit gpr.
 */
Instruction* IGenX86::jmp_r64(Register reg_) {
  ASSERT(reg_.is_gpr());
  auto reg = reg_.hw_id();
  auto instr = new InstructionX86(0xff);
  if (reg >= 8) {
    instr->set(REX(false, false, false, true));
    reg -= 8;
  }
  ASSERT(reg < 8);
  ModRM mrm;
  mrm.rm = reg;
  mrm.reg_op = 4;
  mrm.mod = 3;
  instr->set(mrm);
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   INTEGER MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* IGenX86::sub_gpr64_imm8s(Register reg, int64_t imm) {
  ASSERT(reg.is_gpr());
  ASSERT(imm >= INT8_MIN && imm <= INT8_MAX);
  // SUB r/m64, imm8 : REX.W + 83 /5 ib
  auto instr = new InstructionX86(0x83);
  instr->set_modrm_and_rex(5, reg.hw_id(), 3, true);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::sub_gpr64_imm32s(Register reg, int64_t imm) {
  ASSERT(reg.is_gpr());
  ASSERT(imm >= INT32_MIN && imm <= INT32_MAX);
  auto instr = new InstructionX86(0x81);
  instr->set_modrm_and_rex(5, reg.hw_id(), 3, true);
  instr->set(Imm(4, imm));
  return instr;
}

Instruction* IGenX86::add_gpr64_imm8s(Register reg, int64_t v) {
  ASSERT(v >= INT8_MIN && v <= INT8_MAX);
  auto instr = new InstructionX86(0x83);
  instr->set_modrm_and_rex(0, reg.hw_id(), 3, true);
  instr->set(Imm(1, v));
  return instr;
}

Instruction* IGenX86::add_gpr64_imm32s(Register reg, int64_t v) {
  ASSERT(v >= INT32_MIN && v <= INT32_MAX);
  auto instr = new InstructionX86(0x81);
  instr->set_modrm_and_rex(0, reg.hw_id(), 3, true);
  instr->set(Imm(4, v));
  return instr;
}

Instruction* IGenX86::add_gpr64_imm(Register reg, int64_t imm) {
  if (imm >= INT8_MIN && imm <= INT8_MAX) {
    return add_gpr64_imm8s(reg, imm);
  } else if (imm >= INT32_MIN && imm <= INT32_MAX) {
    return add_gpr64_imm32s(reg, imm);
  } else {
    throw std::runtime_error("Invalid `add` with reg[" + reg.print() + "]/imm[" +
                             std::to_string(imm) + "]");
  }
}

Instruction* IGenX86::sub_gpr64_imm(Register reg, int64_t imm) {
  if (imm >= INT8_MIN && imm <= INT8_MAX) {
    return sub_gpr64_imm8s(reg, imm);
  } else if (imm >= INT32_MIN && imm <= INT32_MAX) {
    return sub_gpr64_imm32s(reg, imm);
  } else {
    throw std::runtime_error("Invalid `sub` with reg[" + reg.print() + "]/imm[" +
                             std::to_string(imm) + "]");
  }
}

Instruction* IGenX86::add_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0x01);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, true);
  return instr;
}

Instruction* IGenX86::sub_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0x29);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, true);
  return instr;
}

/*!
 * Multiply gprs (32-bit, signed).
 * (Note - probably worth doing imul on gpr64's to implement the EE's unsigned multiply)
 */
Instruction* IGenX86::imul_gpr32_gpr32(Register dst, Register src) {
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xaf);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  return instr;
}

/*!
 * Multiply gprs (64-bit, signed).
 * DANGER - this treats all operands as 64-bit. This is not like the EE.
 */
Instruction* IGenX86::imul_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0xf);
  instr->set_op2(0xaf);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  return instr;
}

/*!
 * Divide (idiv, 32 bit)
 */
Instruction* IGenX86::idiv_gpr32(Register reg) {
  auto instr = new InstructionX86(0xf7);
  ASSERT(reg.is_gpr());
  instr->set_modrm_and_rex(7, reg.hw_id(), 3, false);
  return instr;
}

Instruction* IGenX86::unsigned_div_gpr32(Register reg) {
  auto instr = new InstructionX86(0xf7);
  ASSERT(reg.is_gpr());
  instr->set_modrm_and_rex(6, reg.hw_id(), 3, false);
  return instr;
}

/*!
 * Convert doubleword to quadword for division.
 */
Instruction* IGenX86::cdq() {
  auto instr = new InstructionX86(0x99);
  return instr;
}

/*!
 * Move from gpr32 to gpr64, with sign extension.
 * Needed for multiplication/divsion madness.
 */
Instruction* IGenX86::movsx_r64_r32(Register dst, Register src) {
  auto instr = new InstructionX86(0x63);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  return instr;
}

/*!
 * Compare gpr64.  This sets the flags for the jumps.
 * todo UNTESTED
 */
Instruction* IGenX86::cmp_gpr64_gpr64(Register a, Register b) {
  auto instr = new InstructionX86(0x3b);
  ASSERT(a.is_gpr());
  ASSERT(b.is_gpr());
  instr->set_modrm_and_rex(a.hw_id(), b.hw_id(), 3, true);
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   BIT STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * Or of two gprs
 */
Instruction* IGenX86::or_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0x0b);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  return instr;
}

/*!
 * And of two gprs
 */
Instruction* IGenX86::and_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0x23);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  return instr;
}

/*!
 * Xor of two gprs
 */
Instruction* IGenX86::xor_gpr64_gpr64(Register dst, Register src) {
  auto instr = new InstructionX86(0x33);
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, true);
  return instr;
}

/*!
 * Bitwise not a gpr
 */
Instruction* IGenX86::not_gpr64(Register reg) {
  auto instr = new InstructionX86(0xf7);
  ASSERT(reg.is_gpr());
  instr->set_modrm_and_rex(2, reg.hw_id(), 3, true);
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   SHIFTS
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * Shift 64-bit gpr left by CL register
 */
Instruction* IGenX86::shl_gpr64_cl(Register reg) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xd3);
  instr->set_modrm_and_rex(4, reg.hw_id(), 3, true);
  return instr;
}

/*!
 * Shift 64-bit gpr right (logical) by CL register
 */
Instruction* IGenX86::shr_gpr64_cl(Register reg) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xd3);
  instr->set_modrm_and_rex(5, reg.hw_id(), 3, true);
  return instr;
}

/*!
 * Shift 64-bit gpr right (arithmetic) by CL register
 */
Instruction* IGenX86::sar_gpr64_cl(Register reg) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xd3);
  instr->set_modrm_and_rex(7, reg.hw_id(), 3, true);
  return instr;
}

/*!
 * Shift 64-ptr left (logical) by the constant shift amount "sa".
 */
Instruction* IGenX86::shl_gpr64_u8(Register reg, uint8_t sa) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xc1);
  instr->set_modrm_and_rex(4, reg.hw_id(), 3, true);
  instr->set(Imm(1, sa));
  return instr;
}

/*!
 * Shift 64-ptr right (logical) by the constant shift amount "sa".
 */
Instruction* IGenX86::shr_gpr64_u8(Register reg, uint8_t sa) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xc1);
  instr->set_modrm_and_rex(5, reg.hw_id(), 3, true);
  instr->set(Imm(1, sa));
  return instr;
}

/*!
 * Shift 64-ptr right (arithmetic) by the constant shift amount "sa".
 */
Instruction* IGenX86::sar_gpr64_u8(Register reg, uint8_t sa) {
  ASSERT(reg.is_gpr());
  auto instr = new InstructionX86(0xc1);
  instr->set_modrm_and_rex(7, reg.hw_id(), 3, true);
  instr->set(Imm(1, sa));
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   CONTROL FLOW
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * Jump, 32-bit constant offset.  The offset is by default 0 and must be patched later.
 */
Instruction* IGenX86::jmp_32() {
  auto instr = new InstructionX86(0xe9);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump if equal.
 */
Instruction* IGenX86::je_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x84);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump not equal.
 */
Instruction* IGenX86::jne_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x85);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump less than or equal.
 */
Instruction* IGenX86::jle_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x8e);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump greater than or equal.
 */
Instruction* IGenX86::jge_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x8d);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump less than
 */
Instruction* IGenX86::jl_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x8c);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump greater than
 */
Instruction* IGenX86::jg_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x8f);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump below or equal
 */
Instruction* IGenX86::jbe_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x86);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump above or equal
 */
Instruction* IGenX86::jae_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x83);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump below
 */
Instruction* IGenX86::jb_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x82);
  instr->set(Imm(4, 0));
  return instr;
}

/*!
 * Jump above
 */
Instruction* IGenX86::ja_32() {
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x87);
  instr->set(Imm(4, 0));
  return instr;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FLOAT MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * Compare two floats and set flag register for jump (ucomiss)
 */
Instruction* IGenX86::cmp_flt_flt(Register a, Register b) {
  ASSERT(a.is_128bit_simd());
  ASSERT(b.is_128bit_simd());
  auto instr = new InstructionX86(0x0f);
  instr->set_op2(0x2e);
  instr->set_modrm_and_rex(a.hw_id(), b.hw_id(), 3, false);
  return instr;
}

Instruction* IGenX86::sqrts_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x51);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Multiply two floats in xmm's
 */
Instruction* IGenX86::mulss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x59);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Divide two floats in xmm's
 */
Instruction* IGenX86::divss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x5e);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Subtract two floats in xmm's
 */
Instruction* IGenX86::subss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x5c);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Add two floats in xmm's
 */
Instruction* IGenX86::addss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x58);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Floating point minimum.
 */
Instruction* IGenX86::minss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x5d);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Floating point maximum.
 */
Instruction* IGenX86::maxss_xmm_xmm(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x5f);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Convert GPR int32 to XMM float (single precision)
 */
Instruction* IGenX86::int32_to_float(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_gpr());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x2a);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

/*!
 * Convert XMM float to GPR int32(single precision) (truncate)
 */
Instruction* IGenX86::float_to_int32(Register dst, Register src) {
  ASSERT(dst.is_gpr());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xf3);
  instr->set_op2(0x0f);
  instr->set_op3(0x2c);
  instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  instr->swap_op0_rex();
  return instr;
}

Instruction* IGenX86::nop() {
  // NOP
  auto instr = new InstructionX86(0x90);
  return instr;
}

// TODO - rsqrt / abs / sqrt

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   UTILITIES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*!
 * A "null" instruction.  This instruction does not generate any bytes
 * but can be referred to by a label.  Useful to insert in place of a real instruction
 * if the real instruction has been optimized out.
 */
Instruction* IGenX86::null() {
  InstructionX86* i = new InstructionX86(0);
  i->m_flags |= InstructionX86::kIsNull;
  return i;
}

/////////////////////////////
// AVX (VF - Vector Float) //
/////////////////////////////

Instruction* IGenX86::nop_vf() {
  auto instr = new InstructionX86(0xd9);  // FNOP
  instr->set_op2(0xd0);
  return instr;
}

Instruction* IGenX86::wait_vf() {
  auto instr = new InstructionX86(0x9B);  // FWAIT / WAIT
  return instr;
}

Instruction* IGenX86::mov_vf_vf(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());

  if (src.hw_id() >= 8 && dst.hw_id() < 8) {
    // in this case, we can use the 0x29 encoding, which swaps src and dst, in order to use the
    // 2 byte VEX prefix, where the 0x28 encoding would require an extra byte.
    // compilers/assemblers seem to prefer 0x28, unless 0x29 would save you a byte.
    auto instr = new InstructionX86(0x29);
    instr->set_vex_modrm_and_rex(src.hw_id(), dst.hw_id(), 3, VEX3::LeadingBytes::P_0F, false);
    return instr;
  } else {
    auto instr = new InstructionX86(0x28);
    instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, VEX3::LeadingBytes::P_0F, false);
    return instr;
  }
}

Instruction* IGenX86::loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x28);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_addr(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x28);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_plus_s8(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                        offset, VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x28);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_plus_s32(dst.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                         offset, VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) {
  ASSERT(value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  auto instr = new InstructionX86(0x29);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_addr(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                     VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) {
  ASSERT(value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT8_MIN && offset <= INT8_MAX);
  auto instr = new InstructionX86(0x29);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_plus_s8(value.hw_id(), addr1.hw_id(), addr2.hw_id(),
                                                        offset, VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                                        Register addr1,
                                                        Register addr2,
                                                        s64 offset) {
  ASSERT(value.is_128bit_simd());
  ASSERT(addr1.is_gpr());
  ASSERT(addr2.is_gpr());
  ASSERT(addr1 != addr2);
  ASSERT(addr1 != SP);
  ASSERT(addr2 != SP);
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);
  auto instr = new InstructionX86(0x29);
  instr->set_vex_modrm_and_rex_for_reg_plus_reg_plus_s32(
      value.hw_id(), addr1.hw_id(), addr2.hw_id(), offset, VEX3::LeadingBytes::P_0F, false);
  return instr;
}

Instruction* IGenX86::loadvf_rip_plus_s32(Register dest, s64 offset) {
  ASSERT(dest.is_128bit_simd());
  ASSERT(offset >= INT32_MIN);
  ASSERT(offset <= INT32_MAX);
  auto instr = new InstructionX86(0x28);
  instr->set_vex_modrm_and_rex_for_rip_plus_s32(dest.hw_id(), offset);
  return instr;
}

// TODO - rip relative loads and stores.

Instruction* IGenX86::blend_vf(Register dst, Register src1, Register src2, u8 mask) {
  ASSERT(!(mask & 0b11110000));
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x0c);  // VBLENDPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F_3A, src1.hw_id(),
                               false, VexPrefix::P_66);
  instr->set(Imm(1, mask));
  return instr;
}

Instruction* IGenX86::shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  ASSERT(dx < 4);
  ASSERT(dy < 4);
  ASSERT(dz < 4);
  ASSERT(dw < 4);
  u8 imm = dx + (dy << 2) + (dz << 4) + (dw << 6);
  return swizzle_vf(dst, src, imm);

  // SSE encoding version:
  //    InstructionX86 *instr = new InstructionX86(0x0f);
  //    instr->set_op2(0xc6);
  //    instr->set_modrm_and_rex(dst.hw_id(), src.hw_id(), 3, false);
  //    instr->set(Imm(1, imm));
  //    return instr;
}

/*
  Generic Swizzle (re-arrangment of packed FPs) operation, the control bytes are quite involved.
  Here's a brief run-down:
  - 8-bits / 4 groups of 2 bits
  - Right-to-left, each group is used to determine which element in `src` gets copied into
  `dst`'s element (W->X).
  - GROUP OPTIONS
  - 00b - Copy the least-significant element (X)
  - 01b - Copy the second element (from the right) (Y)
  - 10b - Copy the third element (from the right) (Z)
  - 11b - Copy the most significant element (W)
  Examples
  ; xmm1 = (1.5, 2.5, 3.5, 4.5) (W,Z,Y,X in x86 land)
  SHUFPS xmm1, xmm1, 0xff ; Copy the most significant element to all positions
  > (1.5, 1.5, 1.5, 1.5)
  SHUFPS xmm1, xmm1, 0x39 ; Rotate right
  > (4.5, 1.5, 2.5, 3.5)
  */
Instruction* IGenX86::swizzle_vf(Register dst, Register src, u8 controlBytes) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0xC6);  // VSHUFPS

  // we use the AVX "VEX" encoding here. This is a three-operand form,
  // but we just set both source
  // to the same register. It seems like this is one byte longer but is faster maybe?
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, src.hw_id());
  instr->set(Imm(1, controlBytes));
  return instr;
}

/*
  Splats a single element in 'src' to all elements in 'dst'
  For example (pseudocode):
  xmm1 = (1.5, 2.5, 3.5, 4.5)
  xmm2 = (1, 2, 3, 4)
  splat_vf(xmm1, xmm2, XMM_ELEMENT::X);
  xmm1 = (4, 4, 4, 4)
  */
Instruction* IGenX86::splat_vf(Register dst, Register src, Register::VF_ELEMENT element) {
  switch (element) {
    case Register::VF_ELEMENT::X:  // Least significant element
      return swizzle_vf(dst, src, 0b00000000);
      break;
    case Register::VF_ELEMENT::Y:
      return swizzle_vf(dst, src, 0b01010101);
      break;
    case Register::VF_ELEMENT::Z:
      return swizzle_vf(dst, src, 0b10101010);
      break;
    case Register::VF_ELEMENT::W:  // Most significant element
      return swizzle_vf(dst, src, 0b11111111);
      break;
    default:
      ASSERT(false);
      return new InstructionX86(0b0);
  }
}

Instruction* IGenX86::xor_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x57);  // VXORPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::sub_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x5c);  // VSUBPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::add_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x58);  // VADDPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::mul_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x59);  // VMULPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::max_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x5F);  // VMAXPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::min_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x5D);  // VMINPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::div_vf(Register dst, Register src1, Register src2) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  ASSERT(src2.is_128bit_simd());
  auto instr = new InstructionX86(0x5E);  // VDIVPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src2.hw_id(), VEX3::LeadingBytes::P_0F, src1.hw_id());
  return instr;
}

Instruction* IGenX86::sqrt_vf(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0x51);  // VSQRTPS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, 0b0);
  return instr;
}

Instruction* IGenX86::itof_vf(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  auto instr = new InstructionX86(0x5b);  // VCVTDQ2PS
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, 0);
  return instr;
}

Instruction* IGenX86::ftoi_vf(Register dst, Register src) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.F3.0F.WIG 5B /r VCVTTPS2DQ xmm1, xmm2/m128
  auto instr = new InstructionX86(0x5b);  // VCVTTPS2DQ
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, 0, false,
                               VexPrefix::P_F3);
  return instr;
}

Instruction* IGenX86::pw_sra(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 72 /4 ib VPSRAD xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x72);
  instr->set_vex_modrm_and_rex(4, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::pw_srl(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 72 /2 ib VPSRLD xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x72);
  instr->set_vex_modrm_and_rex(2, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::ph_srl(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 71 /2 ib VPSRLW
  auto instr = new InstructionX86(0x71);
  instr->set_vex_modrm_and_rex(2, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::pw_sll(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 72 /6 ib VPSLLD xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x72);
  instr->set_vex_modrm_and_rex(6, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}
Instruction* IGenX86::ph_sll(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 71 /6 ib VPSLLW xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x71);
  instr->set_vex_modrm_and_rex(6, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::parallel_add_byte(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG FC /r VPADDB xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0xFC);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::parallel_bitwise_or(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG EB /r VPOR xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0xEB);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::parallel_bitwise_xor(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG EF /r VPXOR xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0xEF);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::parallel_bitwise_and(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG DB /r VPAND xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0xDB);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Reminder - a word in MIPS = 32bits = a DWORD in x86
//     MIPS   ||   x86
// -----------------------
// byte       || byte
// halfword   || word
// word       || dword
// doubleword || quadword

// -- Unpack High Data Instructions
Instruction* IGenX86::pextub_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 68/r VPUNPCKHBW xmm1,xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x68);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::pextuh_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 69/r VPUNPCKHWD xmm1,xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x69);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::pextuw_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 6A/r VPUNPCKHDQ xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x6a);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// -- Unpack Low Data Instructions
Instruction* IGenX86::pextlb_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 60/r VPUNPCKLBW xmm1,xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x60);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::pextlh_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 61/r VPUNPCKLWD xmm1,xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x61);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::pextlw_swapped(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 62/r VPUNPCKLDQ xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x62);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Equal to than comparison as 16 bytes (8 bits)
Instruction* IGenX86::parallel_compare_e_b(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 74 /r VPCMPEQB xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x74);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Equal to than comparison as 8 halfwords (16 bits)
Instruction* IGenX86::parallel_compare_e_h(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 75 /r VPCMPEQW xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x75);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Equal to than comparison as 4 words (32 bits)
Instruction* IGenX86::parallel_compare_e_w(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 76 /r VPCMPEQD xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x76);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Greater than comparison as 16 bytes (8 bits)
Instruction* IGenX86::parallel_compare_gt_b(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 64 /r VPCMPGTB xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x64);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Greater than comparison as 8 halfwords (16 bits)
Instruction* IGenX86::parallel_compare_gt_h(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 65 /r VPCMPGTW xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x65);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

// Greater than comparison as 4 words (32 bits)
Instruction* IGenX86::parallel_compare_gt_w(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 66 /r VPCMPGTD xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x66);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::vpunpcklqdq(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 6C/r VPUNPCKLQDQ xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x6c);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::pcpyld_swapped(Register dst, Register src0, Register src1) {
  return vpunpcklqdq(dst, src0, src1);
}

Instruction* IGenX86::pcpyud(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 6D/r VPUNPCKHQDQ xmm1, xmm2, xmm3/m128
  // reg, vex, r/m
  auto instr = new InstructionX86(0x6d);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::vpsubd(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG FA /r VPSUBD xmm1, xmm2, xmm3/m128
  // reg, vec, r/m
  auto instr = new InstructionX86(0xfa);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}

Instruction* IGenX86::vpsrldq(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 73 /3 ib VPSRLDQ xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x73);
  instr->set_vex_modrm_and_rex(3, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::vpslldq(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1, xmm2, imm8
  auto instr = new InstructionX86(0x73);
  instr->set_vex_modrm_and_rex(7, src.hw_id(), VEX3::LeadingBytes::P_0F, dst.hw_id(), false,
                               VexPrefix::P_66);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::vpshuflw(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1, xmm2/m128, imm8
  auto instr = new InstructionX86(0x70);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, 0, false,
                               VexPrefix::P_F2);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::vpshufhw(Register dst, Register src, u8 imm) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src.is_128bit_simd());
  // VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1, xmm2/m128, imm8
  auto instr = new InstructionX86(0x70);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src.hw_id(), VEX3::LeadingBytes::P_0F, 0, false,
                               VexPrefix::P_F3);
  instr->set(Imm(1, imm));
  return instr;
}

Instruction* IGenX86::vpackuswb(Register dst, Register src0, Register src1) {
  ASSERT(dst.is_128bit_simd());
  ASSERT(src0.is_128bit_simd());
  ASSERT(src1.is_128bit_simd());
  // VEX.128.66.0F.WIG 67 /r VPACKUSWB xmm1, xmm2, xmm3/m128
  // reg, vex, r/m

  auto instr = new InstructionX86(0x67);
  instr->set_vex_modrm_and_rex(dst.hw_id(), src1.hw_id(), VEX3::LeadingBytes::P_0F, src0.hw_id(),
                               false, VexPrefix::P_66);
  return instr;
}
}  // namespace emitter
