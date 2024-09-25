#include "Register.h"

#include <stdexcept>

#include "common/util/os.h"

namespace emitter {

bool Register::is_128bit_simd() const {
  // printf("ID 128: %d - %d - %d\n", m_id, XMM0, Q0);
  return m_id >= XMM0 && m_id <= XMM15;
}

bool Register::is_gpr() const {
  // printf("ID GPR: %d - %d - %d\n", m_id, R15, X30);
  return m_id >= R0 && m_id <= SP;
}

int real_id_x86(int m_id) {
  switch (m_id) {
    case R0:
      return X86_RAX;
    case R1:
      return X86_RDI;
    case R2:
      return X86_RSI;
    case R3:
      return X86_RDX;
    case R4:
      return X86_RCX;
    case R5:
      return X86_R8;
    case R6:
      return X86_R9;
    case R7:
      return X86_R10;
    case R8:
      return X86_R11;

    case R9:
      return X86_RBX;
    case R10:
      return X86_RBP;
    case R11:
      return X86_R12;
    case PP:
      return X86_R13;
    case ST:
      return X86_R14;
    case OF:
      return X86_R15;
    case SP:
      return X86_RSP;
  }
  return m_id;
}
int real_id_arm64(int m_id) {
  switch (m_id) {
    case R0:
      return ARM_X8;
    case R1:
      return ARM_X0;
    case R2:
      return ARM_X1;
    case R3:
      return ARM_X2;
    case R4:
      return ARM_X3;
    case R5:
      return ARM_X4;
    case R6:
      return ARM_X5;
    case R7:
      return ARM_X6;
    case R8:
      return ARM_X7;

    case R9:
      return ARM_X23;
    case R10:
      return ARM_X24;
    case R11:
      return ARM_X19;
    case PP:
      return ARM_X20;
    case ST:
      return ARM_X21;
    case OF:
      return ARM_X22;
    case SP:
      return ARM_SP;
  }
  if (m_id > SP) {
    return m_id - SP + ARM_SP;
  }
  return m_id;
}

int Register::real_id() const {
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      return real_id_arm64(m_id);
    case cpu_arch_x86_64:
      return real_id_x86(m_id);
    default:
      return m_id;
  }
}

int Register::hw_id() const {
  int real_id = Register::real_id();
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      if (is_128bit_simd()) {
        return real_id - ARM_Q0;
      } else if (is_gpr()) {
        return real_id - ARM_X0;
      } else {
        ASSERT(false);
      }
    case cpu_arch_x86_64:
      if (is_128bit_simd()) {
        return real_id - X86_XMM0;
      } else if (is_gpr()) {
        return real_id - X86_RAX;
      } else {
        ASSERT(false);
      }
    default:
      break;
  }
  return 0xff;
}

std::unique_ptr<RegisterInfo> RegisterInfo::make_register_info() {
  std::unique_ptr<RegisterInfo> info = NULL;
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      info = RegisterInfoArm64::make_register_info();
      break;
    case cpu_arch_x86_64:
      info = RegisterInfoX86::make_register_info();
      break;
    default:
      return NULL;
  }

  // skip R0 and XMM0 so they can be used for return.
  info->m_gpr_arg_regs = std::array<Register, N_ARGS>({R1, R2, R3, R4, R5, R6, R7, R8});
  info->m_xmm_arg_regs =
      std::array<Register, N_ARGS>({XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8});

  info->m_saved_gprs = std::array<Register, N_SAVED_GPRS>({R9, R10, R11});
  info->m_saved_xmms =
      std::array<Register, N_SAVED_XMMS>({XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15});

  for (size_t i = 0; i < N_SAVED_GPRS; i++) {
    info->m_saved_all[i] = info->m_saved_gprs[i];
  }
  for (size_t i = 0; i < N_SAVED_XMMS; i++) {
    info->m_saved_all[i + N_SAVED_GPRS] = info->m_saved_xmms[i];
  }

  info->m_gpr_alloc_order = {R0, R1, R2, R3, R4, R5, R6, R7};  // arbitrary
  info->m_xmm_alloc_order = {XMM0, XMM1, XMM2, XMM3,  XMM4,  XMM5,  XMM6,
                             XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13};

  // these should only be temp registers!
  info->m_gpr_temp_only_alloc_order = {R0, R1, R2, R3, R4, R5, R6, R7, R8};
  info->m_xmm_temp_only_alloc_order = {XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7};

  info->m_gpr_spill_temp_alloc_order = {R0, R1, R2, R3, R4,  R5,
                                        R6, R7, R8, R9, R10, R11};  // arbitrary
  info->m_xmm_spill_temp_alloc_order = {XMM0, XMM1, XMM2,  XMM3,  XMM4,  XMM5,  XMM6,  XMM7,
                                        XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15};

  return info;
}

std::unique_ptr<RegisterInfo> gRegInfo;

std::string to_string(HWRegKind kind) {
  switch (kind) {
    case HWRegKind::GPR:
      return "gpr";
    case HWRegKind::XMM:
      return "xmm";
    default:
      throw std::runtime_error("Unsupported HWRegKind");
  }
}

HWRegKind reg_class_to_hw(RegClass reg_class) {
  switch (reg_class) {
    case RegClass::VECTOR_FLOAT:
    case RegClass::FLOAT:
    case RegClass::INT_128:
      return HWRegKind::XMM;
    case RegClass::GPR_64:
      return HWRegKind::GPR;
    default:
      ASSERT(false);
      return HWRegKind::INVALID;
  }
}

std::string Register::print() const {
  return gRegInfo->get_info(*this).name;
}

}  // namespace emitter
