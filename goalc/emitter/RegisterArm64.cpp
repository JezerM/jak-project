#include "Register.h"

namespace emitter {
RegisterInfoArm64* RegisterInfoArm64::make_register_info() {
  auto info = new RegisterInfoArm64();

  /*                  saved, special, name */
  info->m_info[ARM_X0] = {false, false, "x0"};
  info->m_info[ARM_X1] = {false, false, "x1"};
  info->m_info[ARM_X2] = {false, false, "x2"};
  info->m_info[ARM_X3] = {false, false, "x3"};
  info->m_info[ARM_X4] = {false, false, "x4"};
  info->m_info[ARM_X5] = {false, false, "x5"};
  info->m_info[ARM_X6] = {false, false, "x6"};
  info->m_info[ARM_X7] = {false, false, "x7"};

  info->m_info[ARM_X8] = {false, false, "x8"};

  info->m_info[ARM_X9] = {false, false, "x9"};
  info->m_info[ARM_X10] = {false, false, "x10"};
  info->m_info[ARM_X11] = {false, false, "x11"};
  info->m_info[ARM_X12] = {false, false, "x12"};
  info->m_info[ARM_X13] = {false, false, "x13"};
  info->m_info[ARM_X14] = {false, false, "x14"};
  info->m_info[ARM_X15] = {false, false, "x15"};

  info->m_info[ARM_X16] = {false, false, "x16"};
  info->m_info[ARM_X17] = {false, false, "x17"};
  info->m_info[ARM_X18] = {false, false, "x18"};

  info->m_info[ARM_X19] = {true, true, "x19"};
  info->m_info[ARM_X20] = {true, true, "x20"};
  info->m_info[ARM_X21] = {true, true, "x21"};
  info->m_info[ARM_X22] = {true, true, "x22"};
  info->m_info[ARM_X23] = {true, false, "x23"};
  info->m_info[ARM_X24] = {true, false, "x24"};
  info->m_info[ARM_X25] = {true, false, "x25"};
  info->m_info[ARM_X26] = {true, false, "x26"};
  info->m_info[ARM_X27] = {true, false, "x27"};
  info->m_info[ARM_X28] = {true, false, "x28"};

  info->m_info[ARM_X29] = {true, false, "x29"};
  info->m_info[ARM_X30] = {false, false, "x30"};

  info->m_info[ARM_SP] = {false, false, "SP"};

  info->m_info[ARM_Q0] = {false, false, "q0"};
  info->m_info[ARM_Q1] = {false, false, "q1"};
  info->m_info[ARM_Q2] = {false, false, "q2"};
  info->m_info[ARM_Q3] = {false, false, "q3"};
  info->m_info[ARM_Q4] = {false, false, "q4"};
  info->m_info[ARM_Q5] = {false, false, "q5"};
  info->m_info[ARM_Q6] = {false, false, "q6"};
  info->m_info[ARM_Q7] = {false, false, "q7"};

  info->m_info[ARM_Q8] = {true, false, "q8"};
  info->m_info[ARM_Q9] = {true, false, "q9"};
  info->m_info[ARM_Q10] = {true, false, "q10"};
  info->m_info[ARM_Q11] = {true, false, "q11"};
  info->m_info[ARM_Q12] = {true, false, "q12"};
  info->m_info[ARM_Q13] = {true, false, "q13"};
  info->m_info[ARM_Q14] = {true, false, "q14"};
  info->m_info[ARM_Q15] = {true, false, "q15"};

  info->m_info[ARM_Q16] = {false, false, "q16"};
  info->m_info[ARM_Q17] = {false, false, "q17"};
  info->m_info[ARM_Q18] = {false, false, "q18"};
  info->m_info[ARM_Q19] = {false, false, "q19"};
  info->m_info[ARM_Q20] = {false, false, "q20"};
  info->m_info[ARM_Q21] = {false, false, "q21"};
  info->m_info[ARM_Q22] = {false, false, "q22"};
  info->m_info[ARM_Q23] = {false, false, "q23"};
  info->m_info[ARM_Q24] = {false, false, "q24"};
  info->m_info[ARM_Q25] = {false, false, "q25"};
  info->m_info[ARM_Q26] = {false, false, "q26"};
  info->m_info[ARM_Q27] = {false, false, "q27"};
  info->m_info[ARM_Q28] = {false, false, "q28"};
  info->m_info[ARM_Q29] = {false, false, "q29"};
  info->m_info[ARM_Q30] = {false, false, "q30"};
  info->m_info[ARM_Q31] = {false, false, "q31"};

  return info;
}
}  // namespace emitter
