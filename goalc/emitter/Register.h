#pragma once

/*!
 * @file Register.h
 * Representation of an x86-64 Register.
 */

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "common/common_types.h"
#include "common/goal_constants.h"
#include "common/util/Assert.h"
#include "common/util/os.h"

namespace emitter {

enum class HWRegKind : u8 { GPR, XMM, INVALID };
HWRegKind reg_class_to_hw(RegClass reg_class);
std::string to_string(HWRegKind kind);

constexpr int GPR_SIZE = 8;
constexpr int XMM_SIZE = 16;

enum REG : s8 {
  R0,  // Return
  R1,  // arg 0
  R2,  // arg 1
  R3,  // arg 2
  R4,  // arg 3
  R5,  // arg 4
  R6,  // arg 5
  R7,  // arg 6
  R8,  // arg 7

  R9,   // RBX, saved
  R10,  // RBP, saved
  R11,  // R12, saved

  PP,  // special
  ST,  // special
  OF,  // special

  SP,  // stack pointer (special)

  XMM0,
  XMM1,
  XMM2,
  XMM3,
  XMM4,
  XMM5,
  XMM6,
  XMM7,

  XMM8,
  XMM9,
  XMM10,
  XMM11,
  XMM12,
  XMM13,
  XMM14,
  XMM15
};

// registers by name
enum X86_REG : s8 {
  X86_RAX,  // return, temp                     (R0)
  X86_RCX,  // arg 3, temp                      (R4)
  X86_RDX,  // arg 2, temp                      (R3)
  X86_RBX,  // saved                            (R9)

  X86_RSP,  // stack pointer (special)          (SP)
  X86_RBP,  // saved                            (R10)
  X86_RSI,  // arg 1, temp                      (R2)
  X86_RDI,  // arg 0, temp                      (R1)

  X86_R8,   // arg 4, temp                      (R5)
  X86_R9,   // arg 5, temp                      (R6)
  X86_R10,  // arg 6, saved (arg in GOAL only)  (R7)
  X86_R11,  // arg 7, saved (arg in GOAL only)  (R8)
  X86_R12,  // saved                            (R11)
  X86_R13,  // pp (special!)                    (PP)
  X86_R14,  // st (special!)                    (ST)
  X86_R15,  // offset (special!)                (OF)

  X86_XMM0,
  X86_XMM1,
  X86_XMM2,
  X86_XMM3,
  X86_XMM4,
  X86_XMM5,
  X86_XMM6,
  X86_XMM7,
  X86_XMM8,   // saved
  X86_XMM9,   // saved
  X86_XMM10,  // saved
  X86_XMM11,  // saved
  X86_XMM12,  // saved
  X86_XMM13,  // saved
  X86_XMM14,  // saved
  X86_XMM15,  // saved
};

// TODO - i think it'll be better to make some sort of abstraction
// mapping between x86 and arm, but just using this enum as a place to prototype
// the registers to use.
enum ARM64_REG : s8 {
  ARM_X0,  // arg 0, caller-saved RDI
  ARM_X1,  // arg 1, caller-saved RSI
  ARM_X2,  // arg 2, caller-saved RDX
  ARM_X3,  // arg 3, caller-saved RCX
  ARM_X4,  // arg 4, caller-saved R8
  ARM_X5,  // arg 5, caller-saved R9
  ARM_X6,  // arg 6, caller-saved R10
  ARM_X7,  // arg 7, caller-saved R11

  ARM_X8,  // return, temp, not saved (RAX)

  ARM_X9,   // temp, not-saved
  ARM_X10,  // temp, not-saved
  ARM_X11,  // temp, not-saved
  ARM_X12,  // temp, not-saved
  ARM_X13,  // temp, not-saved
  ARM_X14,  // temp, not-saved
  ARM_X15,  // temp, not-saved

  ARM_X16,  // temp, not-saved, don't use it
  ARM_X17,  // temp, not-saved, don't use it
  ARM_X18,  // temp, not-saved, don't use it

  ARM_X19,  // saved TODO purpose?, R12
  ARM_X20,  // pp, R13
  ARM_X21,  // st, R14
  ARM_X22,  // offset, TODO purpose?, R15
  ARM_X23,  // unused, callee saved
  ARM_X24,  // unused, callee saved
  ARM_X25,  // unused, callee saved
  ARM_X26,  // unused, callee saved
  ARM_X27,  // unused, callee saved
  ARM_X28,  // unused, callee saved

  ARM_X29,  // callee saved, FP - don't use it
  ARM_X30,  // LR - don't use it

  ARM_SP,  // stack pointer

  // quadword registers, equivalent to XMMs
  // the convention in arm64 is the callee preserves all Q values
  // at the same time though, the caller should not depend on this convention!
  ARM_Q0,
  ARM_Q1,
  ARM_Q2,
  ARM_Q3,
  ARM_Q4,
  ARM_Q5,
  ARM_Q6,
  ARM_Q7,
  ARM_Q8,
  ARM_Q9,
  ARM_Q10,
  ARM_Q11,
  ARM_Q12,
  ARM_Q13,
  ARM_Q14,
  ARM_Q15,
  ARM_Q16,
  ARM_Q17,
  ARM_Q18,
  ARM_Q19,
  ARM_Q20,
  ARM_Q21,
  ARM_Q22,
  ARM_Q23,
  ARM_Q24,
  ARM_Q25,
  ARM_Q26,
  ARM_Q27,
  ARM_Q28,
  ARM_Q29,
  ARM_Q30,
  ARM_Q31
};

class Register {
 public:
  Register() = default;

  // intentionally not explicit so we can use X86_REGs in place of Registers
  Register(int id) : m_id(id) {}

  bool is_128bit_simd() const;

  bool is_gpr() const;

  int hw_id() const;

  int real_id() const;

  int id() const { return m_id; }

  struct hash {
    auto operator()(const Register& x) const { return std::hash<u8>()(x.m_id); }
  };

  bool operator==(const Register& x) const { return m_id == x.m_id; }

  bool operator!=(const Register& x) const { return m_id != x.m_id; }

  std::string print() const;

  /*
    Our XMM Registers are 4 packed single-precision floating points
    In the order (from left->right a.k.a most significant to least significant):
    W | Z | Y | X
  */
  enum class VF_ELEMENT { X, Y, Z, W, NONE };

 private:
  // this should be always a generic REG
  s8 m_id = -1;
};

class RegisterInfo {
 public:
  static constexpr int N_ARGS = 8;
  static constexpr int N_REGS = 32;
  static constexpr int N_SAVED_GPRS = 5;
  static constexpr int N_SAVED_XMMS = 8;
  static constexpr int N_TEMP_GPRS = 5;
  static constexpr int N_TEMP_XMMS = 8;

  struct Info {
    bool saved = false;    // does the callee save it?
    bool special = false;  // is it a special GOAL register?
    std::string name;

    bool temp() const { return !saved && !special; }
  };

  static std::unique_ptr<RegisterInfo> make_register_info();

  virtual const Info& get_info(Register r) const = 0;
  Register get_gpr_arg_reg(int id) const { return m_gpr_arg_regs.at(id); }
  Register get_xmm_arg_reg(int id) const { return m_xmm_arg_regs.at(id); }
  Register get_saved_gpr(int id) const { return m_saved_gprs.at(id); }
  Register get_saved_xmm(int id) const { return m_saved_xmms.at(id); }
  virtual Register get_process_reg() const { return 90; }
  virtual Register get_st_reg() const { return 90; }
  virtual Register get_offset_reg() const { return 90; }
  virtual Register get_gpr_ret_reg() const { return 90; }
  virtual Register get_xmm_ret_reg() const { return 90; }
  const std::vector<Register>& get_gpr_alloc_order() { return m_gpr_alloc_order; }
  const std::vector<Register>& get_xmm_alloc_order() { return m_xmm_alloc_order; }
  const std::vector<Register>& get_gpr_temp_alloc_order() { return m_gpr_temp_only_alloc_order; }
  const std::vector<Register>& get_xmm_temp_alloc_order() { return m_xmm_temp_only_alloc_order; }
  const std::vector<Register>& get_gpr_spill_alloc_order() { return m_gpr_spill_temp_alloc_order; }
  const std::vector<Register>& get_xmm_spill_alloc_order() { return m_xmm_spill_temp_alloc_order; }
  const std::array<Register, N_SAVED_XMMS + N_SAVED_GPRS>& get_all_saved() { return m_saved_all; }

 protected:
  std::array<Register, N_ARGS> m_gpr_arg_regs;
  std::array<Register, N_ARGS> m_xmm_arg_regs;
  std::array<Register, N_SAVED_GPRS> m_saved_gprs;
  std::array<Register, N_SAVED_XMMS> m_saved_xmms;
  std::array<Register, N_SAVED_XMMS + N_SAVED_GPRS> m_saved_all;
  std::vector<Register> m_gpr_alloc_order;
  std::vector<Register> m_xmm_alloc_order;
  std::vector<Register> m_gpr_temp_only_alloc_order;
  std::vector<Register> m_xmm_temp_only_alloc_order;
  std::vector<Register> m_gpr_spill_temp_alloc_order;
  std::vector<Register> m_xmm_spill_temp_alloc_order;
};

class RegisterInfoX86 : public RegisterInfo {
 public:
  static std::unique_ptr<RegisterInfoX86> make_register_info();

  static_assert(N_REGS - 1 == X86_XMM15, "bad register count");

  const Info& get_info(Register r) const override { return m_info.at(r.real_id()); }

  Register get_process_reg() const override { return PP; }
  Register get_st_reg() const override { return ST; }
  Register get_offset_reg() const override { return OF; }
  Register get_gpr_ret_reg() const override { return R0; }
  Register get_xmm_ret_reg() const override { return XMM0; }

 protected:
  std::array<Info, N_REGS> m_info;
};

class RegisterInfoArm64 : public RegisterInfo {
 public:
  static constexpr int N_REGS = 64;
  static std::unique_ptr<RegisterInfoArm64> make_register_info();

  const Info& get_info(Register r) const override { return m_info.at(r.real_id()); }

  static_assert(N_REGS - 1 == ARM_Q31, "bad register count");

  // TODO: Change these
  Register get_process_reg() const override { return PP; }
  Register get_st_reg() const override { return ST; }
  Register get_offset_reg() const override { return OF; }
  Register get_gpr_ret_reg() const override { return R0; }
  Register get_xmm_ret_reg() const override { return XMM0; }

 protected:
  std::array<Info, N_REGS> m_info;
};

extern std::unique_ptr<RegisterInfo> gRegInfo;
}  // namespace emitter
