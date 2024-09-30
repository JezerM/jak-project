#pragma once

#include <memory>
#include <stdexcept>

#include "Instruction.h"
#include "Register.h"

#include "common/util/Assert.h"

namespace emitter {
class IGen {
 public:
  virtual ~IGen() = default;

  static std::unique_ptr<IGen> make_igen();

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   MOVES
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  /*!
   * Move data from src to dst. Moves all 64-bits of the GPR.
   */
  virtual Instruction* mov_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * Move a 64-bit constant into a register.
   */
  virtual Instruction* mov_gpr64_u64(Register dst, uint64_t val) = 0;

  /*!
   * Move a 32-bit constant into a register. Zeros the upper 32 bits.
   */
  virtual Instruction* mov_gpr64_u32(Register dst, uint64_t val) = 0;

  /*!
   * Move a signed 32-bit constant into a register. Sign extends for the upper 32 bits.
   * When possible prefer mov_gpr64_u32. (use this only for negative values...)
   * This is always bigger than mov_gpr64_u32, but smaller than a mov_gpr_u64.
   */
  virtual Instruction* mov_gpr64_s32(Register dst, int64_t val) = 0;

  /*!
   * Move 32-bits of xmm to 32 bits of gpr (no sign extension).
   */
  virtual Instruction* movd_gpr32_xmm32(Register dst, Register src) = 0;

  /*!
   * Move 32-bits of gpr to 32-bits of xmm (no sign extension)
   */
  virtual Instruction* movd_xmm32_gpr32(Register dst, Register src) = 0;

  /*!
   * Move 64-bits of xmm to 64 bits of gpr (no sign extension).
   */
  virtual Instruction* movq_gpr64_xmm64(Register dst, Register src) = 0;

  /*!
   * Move 64-bits of gpr to 64-bits of xmm (no sign extension)
   */
  virtual Instruction* movq_xmm64_gpr64(Register dst, Register src) = 0;

  /*!
   * Move 32-bits between xmm's
   */
  virtual Instruction* mov_xmm32_xmm32(Register dst, Register src) = 0;

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
  virtual Instruction* load8s_gpr64_gpr64_plus_gpr64(Register dst,
                                                     Register addr1,
                                                     Register addr2) = 0;

  virtual Instruction* store8_gpr64_gpr64_plus_gpr64(Register addr1,
                                                     Register addr2,
                                                     Register value) = 0;

  virtual Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) = 0;

  virtual Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                             Register addr2,
                                                             Register value,
                                                             s64 offset) = 0;

  virtual Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) = 0;

  /*!
   * movzx dst, BYTE PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load8u_gpr64_gpr64_plus_gpr64(Register dst,
                                                     Register addr1,
                                                     Register addr2) = 0;

  virtual Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) = 0;

  virtual Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  /*!
   * movsx dst, WORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load16s_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) = 0;

  virtual Instruction* store16_gpr64_gpr64_plus_gpr64(Register addr1,
                                                      Register addr2,
                                                      Register value) = 0;

  virtual Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) = 0;

  virtual Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) = 0;

  virtual Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) = 0;

  /*!
   * movzx dst, WORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load16u_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) = 0;

  virtual Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) = 0;

  /*!
   * movsxd dst, DWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load32s_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) = 0;

  virtual Instruction* store32_gpr64_gpr64_plus_gpr64(Register addr1,
                                                      Register addr2,
                                                      Register value) = 0;

  virtual Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) = 0;

  virtual Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) = 0;

  virtual Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) = 0;

  /*!
   * movzxd dst, DWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load32u_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) = 0;

  virtual Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) = 0;

  /*!
   * mov dst, QWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  virtual Instruction* load64_gpr64_gpr64_plus_gpr64(Register dst,
                                                     Register addr1,
                                                     Register addr2) = 0;

  virtual Instruction* store64_gpr64_gpr64_plus_gpr64(Register addr1,
                                                      Register addr2,
                                                      Register value) = 0;

  virtual Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) = 0;

  virtual Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) = 0;

  virtual Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) = 0;

  virtual Instruction* store_goal_vf(Register addr, Register value, Register off, s64 offset) = 0;

  virtual Instruction* store_goal_gpr(Register addr,
                                      Register value,
                                      Register off,
                                      int offset,
                                      int size) = 0;

  virtual Instruction* load_goal_xmm128(Register dst, Register addr, Register off, int offset) = 0;

  /*!
   * Load memory at addr + offset, where addr is a GOAL pointer and off is the offset register.
   * This will pick the appropriate fancy addressing mode instruction.
   */
  virtual Instruction* load_goal_gpr(Register dst,
                                     Register addr,
                                     Register off,
                                     int offset,
                                     int size,
                                     bool sign_extend) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   LOADS n' STORES - XMM32
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  virtual Instruction* store32_xmm32_gpr64_plus_gpr64(Register addr1,
                                                      Register addr2,
                                                      Register xmm_value) = 0;

  virtual Instruction* load32_xmm32_gpr64_plus_gpr64(Register xmm_dest,
                                                     Register addr1,
                                                     Register addr2) = 0;

  virtual Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                              Register addr2,
                                                              Register xmm_value,
                                                              s64 offset) = 0;

  virtual Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                             Register addr1,
                                                             Register addr2,
                                                             s64 offset) = 0;

  virtual Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                               Register addr2,
                                                               Register xmm_value,
                                                               s64 offset) = 0;

  virtual Instruction* lea_reg_plus_off32(Register dest, Register base, s64 offset) = 0;

  virtual Instruction* lea_reg_plus_off8(Register dest, Register base, s64 offset) = 0;

  virtual Instruction* lea_reg_plus_off(Register dest, Register base, s64 offset) = 0;

  virtual Instruction* store32_xmm32_gpr64_plus_s32(Register base,
                                                    Register xmm_value,
                                                    s64 offset) = 0;

  virtual Instruction* store32_xmm32_gpr64_plus_s8(Register base,
                                                   Register xmm_value,
                                                   s64 offset) = 0;

  virtual Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) = 0;

  virtual Instruction* load32_xmm32_gpr64_plus_s32(Register xmm_dest,
                                                   Register base,
                                                   s64 offset) = 0;

  virtual Instruction* load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) = 0;

  virtual Instruction* load_goal_xmm32(Register xmm_dest,
                                       Register addr,
                                       Register off,
                                       s64 offset) = 0;

  virtual Instruction* store_goal_xmm32(Register addr,
                                        Register xmm_value,
                                        Register off,
                                        s64 offset) = 0;

  virtual Instruction* store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) = 0;

  virtual Instruction* load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   LOADS n' STORES - XMM128
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Store a 128-bit xmm into an address stored in a register, no offset
   */
  virtual Instruction* store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) = 0;

  virtual Instruction* store128_gpr64_xmm128_s32(Register gpr_addr,
                                                 Register xmm_value,
                                                 s64 offset) = 0;

  virtual Instruction* store128_gpr64_xmm128_s8(Register gpr_addr,
                                                Register xmm_value,
                                                s64 offset) = 0;

  virtual Instruction* load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) = 0;

  virtual Instruction* load128_xmm128_gpr64_s32(Register xmm_dest,
                                                Register gpr_addr,
                                                s64 offset) = 0;

  virtual Instruction* load128_xmm128_gpr64_s8(Register xmm_dest,
                                               Register gpr_addr,
                                               s64 offset) = 0;

  virtual Instruction* load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) = 0;

  virtual Instruction* store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   RIP loads and stores
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  virtual Instruction* load64_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load32s_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load32u_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load16u_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load16s_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load8u_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* load8s_rip_s32(Register dest, s64 offset) = 0;

  virtual Instruction* static_load(Register dest, s64 offset, int size, bool sign_extend) = 0;

  virtual Instruction* store64_rip_s32(Register src, s64 offset) = 0;

  virtual Instruction* store32_rip_s32(Register src, s64 offset) = 0;

  virtual Instruction* store16_rip_s32(Register src, s64 offset) = 0;

  virtual Instruction* store8_rip_s32(Register src, s64 offset) = 0;

  virtual Instruction* static_store(Register value, s64 offset, int size) = 0;

  virtual Instruction* static_addr(Register dst, s64 offset) = 0;

  virtual Instruction* static_load_xmm32(Register xmm_dest, s64 offset) = 0;

  virtual Instruction* static_store_xmm32(Register xmm_value, s64 offset) = 0;

  // TODO, special load/stores of 128 bit values.

  // TODO, consider specialized stack loads and stores?
  virtual Instruction* load64_gpr64_plus_s32(Register dst_reg,
                                             int32_t offset,
                                             Register src_reg) = 0;

  /*!
   * Store 64-bits from gpr into memory located at 64-bit reg + 32-bit signed offset.
   */
  virtual Instruction* store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   FUNCTION STUFF
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  /*!
   * Function return. Pops the 64-bit return address (real) off the stack and jumps to it.
   */
  virtual Instruction* ret() = 0;

  /*!
   * Instruction* to push gpr (64-bits) onto the stack
   */
  virtual Instruction* push_gpr64(Register reg) = 0;

  /*!
   * Instruction* to pop 64 bit gpr from the stack
   */
  virtual Instruction* pop_gpr64(Register reg) = 0;

  /*!
   * Call a function stored in a 64-bit gpr
   */
  virtual Instruction* call_r64(Register reg_) = 0;

  /*!
   * Jump to an x86-64 address stored in a 64-bit gpr.
   */
  virtual Instruction* jmp_r64(Register reg_) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   INTEGER MATH
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  virtual Instruction* sub_gpr64_imm8s(Register reg, int64_t imm) = 0;

  virtual Instruction* sub_gpr64_imm32s(Register reg, int64_t imm) = 0;

  virtual Instruction* add_gpr64_imm8s(Register reg, int64_t v) = 0;

  virtual Instruction* add_gpr64_imm32s(Register reg, int64_t v) = 0;

  virtual Instruction* add_gpr64_imm(Register reg, int64_t imm) = 0;

  virtual Instruction* sub_gpr64_imm(Register reg, int64_t imm) = 0;

  virtual Instruction* add_gpr64_gpr64(Register dst, Register src) = 0;

  virtual Instruction* sub_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * Multiply gprs (32-bit, signed).
   * (Note - probably worth doing imul on gpr64's to implement the EE's unsigned multiply)
   */
  virtual Instruction* imul_gpr32_gpr32(Register dst, Register src) = 0;

  /*!
   * Multiply gprs (64-bit, signed).
   * DANGER - this treats all operands as 64-bit. This is not like the EE.
   */
  virtual Instruction* imul_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * Divide (idiv, 32 bit)
   */
  virtual Instruction* idiv_gpr32(Register reg) = 0;

  virtual Instruction* unsigned_div_gpr32(Register reg) = 0;

  /*!
   * Convert doubleword to quadword for division.
   */
  virtual Instruction* cdq() = 0;

  /*!
   * Move from gpr32 to gpr64, with sign extension.
   * Needed for multiplication/divsion madness.
   */
  virtual Instruction* movsx_r64_r32(Register dst, Register src) = 0;

  /*!
   * Compare gpr64.  This sets the flags for the jumps.
   * todo UNTESTED
   */
  virtual Instruction* cmp_gpr64_gpr64(Register a, Register b) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   BIT STUFF
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Or of two gprs
   */
  virtual Instruction* or_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * And of two gprs
   */
  virtual Instruction* and_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * Xor of two gprs
   */
  virtual Instruction* xor_gpr64_gpr64(Register dst, Register src) = 0;

  /*!
   * Bitwise not a gpr
   */
  virtual Instruction* not_gpr64(Register reg) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   SHIFTS
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Shift 64-bit gpr left by CL register
   */
  virtual Instruction* shl_gpr64_cl(Register reg) = 0;

  /*!
   * Shift 64-bit gpr right (logical) by CL register
   */
  virtual Instruction* shr_gpr64_cl(Register reg) = 0;

  /*!
   * Shift 64-bit gpr right (arithmetic) by CL register
   */
  virtual Instruction* sar_gpr64_cl(Register reg) = 0;

  /*!
   * Shift 64-ptr left (logical) by the constant shift amount "sa".
   */
  virtual Instruction* shl_gpr64_u8(Register reg, uint8_t sa) = 0;

  /*!
   * Shift 64-ptr right (logical) by the constant shift amount "sa".
   */
  virtual Instruction* shr_gpr64_u8(Register reg, uint8_t sa) = 0;

  /*!
   * Shift 64-ptr right (arithmetic) by the constant shift amount "sa".
   */
  virtual Instruction* sar_gpr64_u8(Register reg, uint8_t sa) = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   CONTROL FLOW
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Jump, 32-bit constant offset.  The offset is by default 0 and must be patched later.
   */
  virtual Instruction* jmp_32() = 0;

  /*!
   * Jump if equal.
   */
  virtual Instruction* je_32() = 0;

  /*!
   * Jump not equal.
   */
  virtual Instruction* jne_32() = 0;

  /*!
   * Jump less than or equal.
   */
  virtual Instruction* jle_32() = 0;

  /*!
   * Jump greater than or equal.
   */
  virtual Instruction* jge_32() = 0;

  /*!
   * Jump less than
   */
  virtual Instruction* jl_32() = 0;

  /*!
   * Jump greater than
   */
  virtual Instruction* jg_32() = 0;

  /*!
   * Jump below or equal
   */
  virtual Instruction* jbe_32() = 0;

  /*!
   * Jump above or equal
   */
  virtual Instruction* jae_32() = 0;

  /*!
   * Jump below
   */
  virtual Instruction* jb_32() = 0;

  /*!
   * Jump above
   */
  virtual Instruction* ja_32() = 0;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   FLOAT MATH
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Compare two floats and set flag register for jump (ucomiss)
   */
  virtual Instruction* cmp_flt_flt(Register a, Register b) = 0;

  virtual Instruction* sqrts_xmm(Register dst, Register src) = 0;

  /*!
   * Multiply two floats in xmm's
   */
  virtual Instruction* mulss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Divide two floats in xmm's
   */
  virtual Instruction* divss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Subtract two floats in xmm's
   */
  virtual Instruction* subss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Add two floats in xmm's
   */
  virtual Instruction* addss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Floating point minimum.
   */
  virtual Instruction* minss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Floating point maximum.
   */
  virtual Instruction* maxss_xmm_xmm(Register dst, Register src) = 0;

  /*!
   * Convert GPR int32 to XMM float (single precision)
   */
  virtual Instruction* int32_to_float(Register dst, Register src) = 0;

  /*!
   * Convert XMM float to GPR int32(single precision) (truncate)
   */
  virtual Instruction* float_to_int32(Register dst, Register src) = 0;

  virtual Instruction* nop() = 0;

  // TODO - rsqrt / abs / sqrt

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   UTILITIES
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * A "null" instruction.  This instruction does not generate any bytes
   * but can be referred to by a label.  Useful to insert in place of a real instruction
   * if the real instruction has been optimized out.
   */
  virtual Instruction* null() = 0;

  /////////////////////////////
  // AVX (VF - Vector Float) //
  /////////////////////////////

  virtual Instruction* nop_vf() = 0;

  virtual Instruction* wait_vf() = 0;

  virtual Instruction* mov_vf_vf(Register dst, Register src) = 0;

  virtual Instruction* loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) = 0;

  virtual Instruction* loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) = 0;

  virtual Instruction* loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                                        Register addr1,
                                                        Register addr2,
                                                        s64 offset) = 0;

  virtual Instruction* storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) = 0;

  virtual Instruction* storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                                        Register addr1,
                                                        Register addr2,
                                                        s64 offset) = 0;

  virtual Instruction* storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                                         Register addr1,
                                                         Register addr2,
                                                         s64 offset) = 0;

  virtual Instruction* loadvf_rip_plus_s32(Register dest, s64 offset) = 0;

  // TODO - rip relative loads and stores.

  virtual Instruction* blend_vf(Register dst, Register src1, Register src2, u8 mask) = 0;

  virtual Instruction* shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) = 0;

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
  virtual Instruction* swizzle_vf(Register dst, Register src, u8 controlBytes) = 0;

  /*
    Splats a single element in 'src' to all elements in 'dst'
    For example (pseudocode):
    xmm1 = (1.5, 2.5, 3.5, 4.5)
    xmm2 = (1, 2, 3, 4)
    splat_vf(xmm1, xmm2, XMM_ELEMENT::X) = 0;
    xmm1 = (4, 4, 4, 4)
    */
  virtual Instruction* splat_vf(Register dst, Register src, Register::VF_ELEMENT element) = 0;

  virtual Instruction* xor_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* sub_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* add_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* mul_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* max_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* min_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* div_vf(Register dst, Register src1, Register src2) = 0;

  virtual Instruction* sqrt_vf(Register dst, Register src) = 0;

  virtual Instruction* itof_vf(Register dst, Register src) = 0;

  virtual Instruction* ftoi_vf(Register dst, Register src) = 0;

  virtual Instruction* pw_sra(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* pw_srl(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* ph_srl(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* pw_sll(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* ph_sll(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* parallel_add_byte(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* parallel_bitwise_or(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* parallel_bitwise_xor(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* parallel_bitwise_and(Register dst, Register src0, Register src1) = 0;

  // Reminder - a word in MIPS = 32bits = a DWORD in x86
  //     MIPS   ||   x86
  // -----------------------
  // byte       || byte
  // halfword   || word
  // word       || dword
  // doubleword || quadword

  // -- Unpack High Data Instructions
  virtual Instruction* pextub_swapped(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pextuh_swapped(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pextuw_swapped(Register dst, Register src0, Register src1) = 0;

  // -- Unpack Low Data Instructions
  virtual Instruction* pextlb_swapped(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pextlh_swapped(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pextlw_swapped(Register dst, Register src0, Register src1) = 0;

  // Equal to than comparison as 16 bytes (8 bits)
  virtual Instruction* parallel_compare_e_b(Register dst, Register src0, Register src1) = 0;

  // Equal to than comparison as 8 halfwords (16 bits)
  virtual Instruction* parallel_compare_e_h(Register dst, Register src0, Register src1) = 0;

  // Equal to than comparison as 4 words (32 bits)
  virtual Instruction* parallel_compare_e_w(Register dst, Register src0, Register src1) = 0;

  // Greater than comparison as 16 bytes (8 bits)
  virtual Instruction* parallel_compare_gt_b(Register dst, Register src0, Register src1) = 0;

  // Greater than comparison as 8 halfwords (16 bits)
  virtual Instruction* parallel_compare_gt_h(Register dst, Register src0, Register src1) = 0;

  // Greater than comparison as 4 words (32 bits)
  virtual Instruction* parallel_compare_gt_w(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* vpunpcklqdq(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pcpyld_swapped(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* pcpyud(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* vpsubd(Register dst, Register src0, Register src1) = 0;

  virtual Instruction* vpsrldq(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* vpslldq(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* vpshuflw(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* vpshufhw(Register dst, Register src, u8 imm) = 0;

  virtual Instruction* vpackuswb(Register dst, Register src0, Register src1) = 0;
};  // namespace IGen

extern std::unique_ptr<IGen> gIGen;
}  // namespace emitter
