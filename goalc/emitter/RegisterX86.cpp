#include "Register.h"

namespace emitter {
RegisterInfoX86* RegisterInfoX86::make_register_info() {
  auto info = new RegisterInfoX86();

  info->m_info[X86_RAX] = {false, false, "rax"};  // return, temp
  info->m_info[X86_RCX] = {false, false, "rcx"};  // gpr arg 3, temp
  info->m_info[X86_RDX] = {false, false, "rdx"};  // gpr arg 2, temp
  info->m_info[X86_RBX] = {true, false, "rbx"};   // saved
  info->m_info[X86_RSP] = {false, true, "rsp"};   // stack pointer
  info->m_info[X86_RBP] = {true, false, "rbp"};   // saved
  info->m_info[X86_RSI] = {false, false, "rsi"};  // gpr arg 1, temp
  info->m_info[X86_RDI] = {false, false, "rdi"};  // gpr arg 0, temp

  info->m_info[X86_R8] = {false, false, "r8"};   // gpr arg 4, temp
  info->m_info[X86_R9] = {false, false, "r9"};   // gpr arg 5, temp
  info->m_info[X86_R10] = {true, false, "r10"};  // gpr arg 6, saved
  info->m_info[X86_R11] = {true, false, "r11"};  // gpr arg 7, saved
  info->m_info[X86_R12] = {true, false, "r12"};  // saved
  info->m_info[X86_R13] = {false, true, "r13"};  // pp
  info->m_info[X86_R14] = {false, true, "r14"};  // st
  info->m_info[X86_R15] = {false, true, "r15"};  // offset.

  info->m_info[X86_XMM0] = {false, false, "xmm0"};
  info->m_info[X86_XMM1] = {false, false, "xmm1"};
  info->m_info[X86_XMM2] = {false, false, "xmm2"};
  info->m_info[X86_XMM3] = {false, false, "xmm3"};
  info->m_info[X86_XMM4] = {false, false, "xmm4"};
  info->m_info[X86_XMM5] = {false, false, "xmm5"};
  info->m_info[X86_XMM6] = {false, false, "xmm6"};
  info->m_info[X86_XMM7] = {false, false, "xmm7"};
  info->m_info[X86_XMM8] = {true, false, "xmm8"};
  info->m_info[X86_XMM9] = {true, false, "xmm9"};
  info->m_info[X86_XMM10] = {true, false, "xmm10"};
  info->m_info[X86_XMM11] = {true, false, "xmm11"};
  info->m_info[X86_XMM12] = {true, false, "xmm12"};
  info->m_info[X86_XMM13] = {true, false, "xmm13"};
  info->m_info[X86_XMM14] = {true, false, "xmm14"};
  info->m_info[X86_XMM15] = {true, false, "xmm15"};

  return info;
}
}  // namespace emitter
