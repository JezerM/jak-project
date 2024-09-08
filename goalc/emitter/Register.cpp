#include "Register.h"

#include <stdexcept>

#include "common/util/os.h"

namespace emitter {

bool Register::is_128bit_simd() const {
  // printf("ID 128: %d - %d - %d\n", m_id, XMM0, Q0);
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      return m_id >= Q0 && m_id <= Q31;
    case cpu_arch_x86_64:
      return m_id >= XMM0 && m_id <= XMM15;
    default:
      return false;
  }
}

bool Register::is_gpr() const {
  // printf("ID GPR: %d - %d - %d\n", m_id, R15, X30);
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      return m_id >= X0 && m_id <= X30;
    case cpu_arch_x86_64:
      return m_id >= RAX && m_id <= R15;
    default:
      return false;
  }
}

int Register::hw_id() const {
  // TODO - ARM64, even needed?
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      if (is_128bit_simd()) {
        return m_id - Q0;
      } else if (is_gpr()) {
        return m_id - X0;
      } else {
        ASSERT(false);
      }
    case cpu_arch_x86_64:
      if (is_128bit_simd()) {
        return m_id - XMM0;
      } else if (is_gpr()) {
        return m_id - RAX;
      } else {
        ASSERT(false);
      }
    default:
      break;
  }
  return 0xff;
}

RegisterInfo* RegisterInfo::make_register_info() {
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      return RegisterInfoArm64::make_register_info();
    case cpu_arch_x86_64:
      return RegisterInfoX86::make_register_info();
    default:
      break;
  }
  return new RegisterInfo();
}

RegisterInfo* gRegInfo;

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
