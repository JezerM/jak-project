#include "Register.h"

namespace emitter {
RegisterInfo* RegisterInfoArm64::make_register_info() {
  auto info = new RegisterInfoArm64();

  info->m_info[X0] = {false, false, "x0"};
  info->m_info[X1] = {false, false, "x1"};
  info->m_info[X2] = {false, false, "x2"};
  info->m_info[X3] = {true, false, "x3"};
  info->m_info[X4] = {false, true, "x4"};
  info->m_info[X5] = {true, false, "x5"};
  info->m_info[X6] = {false, false, "x6"};
  info->m_info[X7] = {false, false, "x7"};

  info->m_info[X8] = {false, false, "x8"};
  info->m_info[X9] = {false, false, "x9"};
  info->m_info[X10] = {true, false, "x10"};
  info->m_info[X11] = {true, false, "x11"};
  info->m_info[X12] = {true, false, "x12"};
  info->m_info[X13] = {false, true, "x13"};
  info->m_info[X14] = {false, true, "x14"};
  info->m_info[X15] = {false, true, "x15"};

  info->m_info[XMM0] = {false, false, "xmm0"};
  info->m_info[XMM1] = {false, false, "xmm1"};
  info->m_info[XMM2] = {false, false, "xmm2"};
  info->m_info[XMM3] = {false, false, "xmm3"};
  info->m_info[XMM4] = {false, false, "xmm4"};
  info->m_info[XMM5] = {false, false, "xmm5"};
  info->m_info[XMM6] = {false, false, "xmm6"};
  info->m_info[XMM7] = {false, false, "xmm7"};
  info->m_info[XMM8] = {true, false, "xmm8"};
  info->m_info[XMM9] = {true, false, "xmm9"};
  info->m_info[XMM10] = {true, false, "xmm10"};
  info->m_info[XMM11] = {true, false, "xmm11"};
  info->m_info[XMM12] = {true, false, "xmm12"};
  info->m_info[XMM13] = {true, false, "xmm13"};
  info->m_info[XMM14] = {true, false, "xmm14"};
  info->m_info[XMM15] = {true, false, "xmm15"};

  info->m_gpr_arg_regs = std::array<Register, N_ARGS>({X0, X1, X2, X3, X4, X5, X6, X7});
  // skip q0 so it can be used for return.
  info->m_xmm_arg_regs = std::array<Register, N_ARGS>({Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8});
  info->m_saved_gprs = std::array<Register, N_SAVED_GPRS>({X19, X20, X21, X22, X23});
  info->m_saved_xmms = std::array<Register, N_SAVED_XMMS>({Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16});

  for (size_t i = 0; i < N_SAVED_GPRS; i++) {
    info->m_saved_all[i] = info->m_saved_gprs[i];
  }
  for (size_t i = 0; i < N_SAVED_XMMS; i++) {
    info->m_saved_all[i + N_SAVED_GPRS] = info->m_saved_xmms[i];
  }

  info->m_gpr_alloc_order = {X0, X1, X2, X3, X4, X5, X6, X7};  // arbitrary
  info->m_xmm_alloc_order = {Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13};

  // these should only be temp registers!
  info->m_gpr_temp_only_alloc_order = {X9, X10, X11, X12, X13, X14, X15};
  info->m_xmm_temp_only_alloc_order = {Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7};

  info->m_gpr_spill_temp_alloc_order = {X0, X1, X2, X3,  X4,  X5,
                                        X6, X7, X9, X10, X11, X12};  // arbitrary
  info->m_xmm_spill_temp_alloc_order = {Q0, Q1, Q2,  Q3,  Q4,  Q5,  Q6,  Q7,
                                        Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15};
  return info;
}
}  // namespace emitter
