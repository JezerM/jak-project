#pragma once

#include <stdexcept>

#include "Instruction.h"
#include "Register.h"

#include "common/util/Assert.h"

#include "goalc/emitter/IGen.h"

namespace emitter {
class IGenX86 final : public IGen {
 public:
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   MOVES
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  /*!
   * Move data from src to dst. Moves all 64-bits of the GPR.
   */
  Instruction* mov_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * Move a 64-bit constant into a register.
   */
  Instruction* mov_gpr64_u64(Register dst, uint64_t val) override;

  /*!
   * Move a 32-bit constant into a register. Zeros the upper 32 bits.
   */
  Instruction* mov_gpr64_u32(Register dst, uint64_t val) override;

  /*!
   * Move a signed 32-bit constant into a register. Sign extends for the upper 32 bits.
   * When possible prefer mov_gpr64_u32. (use this only for negative values...)
   * This is always bigger than mov_gpr64_u32, but smaller than a mov_gpr_u64.
   */
  Instruction* mov_gpr64_s32(Register dst, int64_t val) override;

  /*!
   * Move 32-bits of xmm to 32 bits of gpr (no sign extension).
   */
  Instruction* movd_gpr32_xmm32(Register dst, Register src) override;

  /*!
   * Move 32-bits of gpr to 32-bits of xmm (no sign extension)
   */
  Instruction* movd_xmm32_gpr32(Register dst, Register src) override;

  /*!
   * Move 64-bits of xmm to 64 bits of gpr (no sign extension).
   */
  Instruction* movq_gpr64_xmm64(Register dst, Register src) override;

  /*!
   * Move 64-bits of gpr to 64-bits of xmm (no sign extension)
   */
  Instruction* movq_xmm64_gpr64(Register dst, Register src) override;

  /*!
   * Move 32-bits between xmm's
   */
  Instruction* mov_xmm32_xmm32(Register dst, Register src) override;

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
  Instruction* load8s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) override;

  Instruction* store8_gpr64_gpr64_plus_gpr64(Register addr1,
                                             Register addr2,
                                             Register value) override;

  Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) override;

  Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) override;

  Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                      Register addr2,
                                                      Register value,
                                                      s64 offset) override;

  /*!
   * movzx dst, BYTE PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load8u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) override;

  Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) override;

  Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  /*!
   * movsx dst, WORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load16s_gpr64_gpr64_plus_gpr64(Register dst,
                                              Register addr1,
                                              Register addr2) override;

  Instruction* store16_gpr64_gpr64_plus_gpr64(Register addr1,
                                              Register addr2,
                                              Register value) override;

  Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                      Register addr2,
                                                      Register value,
                                                      s64 offset) override;

  Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                       Register addr2,
                                                       Register value,
                                                       s64 offset) override;

  Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) override;

  /*!
   * movzx dst, WORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load16u_gpr64_gpr64_plus_gpr64(Register dst,
                                              Register addr1,
                                              Register addr2) override;

  Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) override;

  /*!
   * movsxd dst, DWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load32s_gpr64_gpr64_plus_gpr64(Register dst,
                                              Register addr1,
                                              Register addr2) override;

  Instruction* store32_gpr64_gpr64_plus_gpr64(Register addr1,
                                              Register addr2,
                                              Register value) override;

  Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                      Register addr2,
                                                      Register value,
                                                      s64 offset) override;

  Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) override;

  Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                       Register addr2,
                                                       Register value,
                                                       s64 offset) override;

  /*!
   * movzxd dst, DWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load32u_gpr64_gpr64_plus_gpr64(Register dst,
                                              Register addr1,
                                              Register addr2) override;

  Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                       Register addr1,
                                                       Register addr2,
                                                       s64 offset) override;

  /*!
   * mov dst, QWORD PTR [addr1 + addr2]
   * addr1 and addr2 have to be different registers.
   * Cannot use rsp.
   */
  Instruction* load64_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) override;

  Instruction* store64_gpr64_gpr64_plus_gpr64(Register addr1,
                                              Register addr2,
                                              Register value) override;

  Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) override;

  Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                      Register addr2,
                                                      Register value,
                                                      s64 offset) override;

  Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                       Register addr2,
                                                       Register value,
                                                       s64 offset) override;

  Instruction* store_goal_vf(Register addr, Register value, Register off, s64 offset) override;

  Instruction* store_goal_gpr(Register addr,
                              Register value,
                              Register off,
                              int offset,
                              int size) override;

  Instruction* load_goal_xmm128(Register dst, Register addr, Register off, int offset) override;

  /*!
   * Load memory at addr + offset, where addr is a GOAL pointer and off is the offset register.
   * This will pick the appropriate fancy addressing mode instruction.
   */
  Instruction* load_goal_gpr(Register dst,
                             Register addr,
                             Register off,
                             int offset,
                             int size,
                             bool sign_extend) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   LOADS n' STORES - XMM32
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  Instruction* store32_xmm32_gpr64_plus_gpr64(Register addr1,
                                              Register addr2,
                                              Register xmm_value) override;

  Instruction* load32_xmm32_gpr64_plus_gpr64(Register xmm_dest,
                                             Register addr1,
                                             Register addr2) override;

  Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                      Register addr2,
                                                      Register xmm_value,
                                                      s64 offset) override;

  Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) override;

  Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                       Register addr2,
                                                       Register xmm_value,
                                                       s64 offset) override;

  Instruction* lea_reg_plus_off32(Register dest, Register base, s64 offset) override;

  Instruction* lea_reg_plus_off8(Register dest, Register base, s64 offset) override;

  Instruction* lea_reg_plus_off(Register dest, Register base, s64 offset) override;

  Instruction* store32_xmm32_gpr64_plus_s32(Register base, Register xmm_value, s64 offset) override;

  Instruction* store32_xmm32_gpr64_plus_s8(Register base, Register xmm_value, s64 offset) override;

  Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                      Register addr1,
                                                      Register addr2,
                                                      s64 offset) override;

  Instruction* load32_xmm32_gpr64_plus_s32(Register xmm_dest, Register base, s64 offset) override;

  Instruction* load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) override;

  Instruction* load_goal_xmm32(Register xmm_dest, Register addr, Register off, s64 offset) override;

  Instruction* store_goal_xmm32(Register addr,
                                Register xmm_value,
                                Register off,
                                s64 offset) override;

  Instruction* store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) override;

  Instruction* load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   LOADS n' STORES - XMM128
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Store a 128-bit xmm into an address stored in a register, no offset
   */
  Instruction* store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) override;

  Instruction* store128_gpr64_xmm128_s32(Register gpr_addr,
                                         Register xmm_value,
                                         s64 offset) override;

  Instruction* store128_gpr64_xmm128_s8(Register gpr_addr, Register xmm_value, s64 offset) override;

  Instruction* load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) override;

  Instruction* load128_xmm128_gpr64_s32(Register xmm_dest, Register gpr_addr, s64 offset) override;

  Instruction* load128_xmm128_gpr64_s8(Register xmm_dest, Register gpr_addr, s64 offset) override;

  Instruction* load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) override;

  Instruction* store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   RIP loads and stores
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  Instruction* load64_rip_s32(Register dest, s64 offset) override;

  Instruction* load32s_rip_s32(Register dest, s64 offset) override;

  Instruction* load32u_rip_s32(Register dest, s64 offset) override;

  Instruction* load16u_rip_s32(Register dest, s64 offset) override;

  Instruction* load16s_rip_s32(Register dest, s64 offset) override;

  Instruction* load8u_rip_s32(Register dest, s64 offset) override;

  Instruction* load8s_rip_s32(Register dest, s64 offset) override;

  Instruction* static_load(Register dest, s64 offset, int size, bool sign_extend) override;

  Instruction* store64_rip_s32(Register src, s64 offset) override;

  Instruction* store32_rip_s32(Register src, s64 offset) override;

  Instruction* store16_rip_s32(Register src, s64 offset) override;

  Instruction* store8_rip_s32(Register src, s64 offset) override;

  Instruction* static_store(Register value, s64 offset, int size) override;

  Instruction* static_addr(Register dst, s64 offset) override;

  Instruction* static_load_xmm32(Register xmm_dest, s64 offset) override;

  Instruction* static_store_xmm32(Register xmm_value, s64 offset) override;

  // TODO, special load/stores of 128 bit values.

  // TODO, consider specialized stack loads and stores?
  Instruction* load64_gpr64_plus_s32(Register dst_reg, int32_t offset, Register src_reg) override;

  /*!
   * Store 64-bits from gpr into memory located at 64-bit reg + 32-bit signed offset.
   */
  Instruction* store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   FUNCTION STUFF
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  /*!
   * Function return. Pops the 64-bit return address (real) off the stack and jumps to it.
   */
  Instruction* ret() override;

  /*!
   * Instruction* to push gpr (64-bits) onto the stack
   */
  Instruction* push_gpr64(Register reg) override;

  /*!
   * Instruction* to pop 64 bit gpr from the stack
   */
  Instruction* pop_gpr64(Register reg) override;

  /*!
   * Call a function stored in a 64-bit gpr
   */
  Instruction* call_r64(Register reg_) override;

  /*!
   * Jump to an x86-64 address stored in a 64-bit gpr.
   */
  Instruction* jmp_r64(Register reg_) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   INTEGER MATH
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  Instruction* sub_gpr64_imm8s(Register reg, int64_t imm) override;

  Instruction* sub_gpr64_imm32s(Register reg, int64_t imm) override;

  Instruction* add_gpr64_imm8s(Register reg, int64_t v) override;

  Instruction* add_gpr64_imm32s(Register reg, int64_t v) override;

  Instruction* add_gpr64_imm(Register reg, int64_t imm) override;

  Instruction* sub_gpr64_imm(Register reg, int64_t imm) override;

  Instruction* add_gpr64_gpr64(Register dst, Register src) override;

  Instruction* sub_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * Multiply gprs (32-bit, signed).
   * (Note - probably worth doing imul on gpr64's to implement the EE's unsigned multiply)
   */
  Instruction* imul_gpr32_gpr32(Register dst, Register src) override;

  /*!
   * Multiply gprs (64-bit, signed).
   * DANGER - this treats all operands as 64-bit. This is not like the EE.
   */
  Instruction* imul_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * Divide (idiv, 32 bit)
   */
  Instruction* idiv_gpr32(Register reg) override;

  Instruction* unsigned_div_gpr32(Register reg) override;

  /*!
   * Convert doubleword to quadword for division.
   */
  Instruction* cdq() override;

  /*!
   * Move from gpr32 to gpr64, with sign extension.
   * Needed for multiplication/divsion madness.
   */
  Instruction* movsx_r64_r32(Register dst, Register src) override;

  /*!
   * Compare gpr64.  This sets the flags for the jumps.
   * todo UNTESTED
   */
  Instruction* cmp_gpr64_gpr64(Register a, Register b) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   BIT STUFF
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Or of two gprs
   */
  Instruction* or_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * And of two gprs
   */
  Instruction* and_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * Xor of two gprs
   */
  Instruction* xor_gpr64_gpr64(Register dst, Register src) override;

  /*!
   * Bitwise not a gpr
   */
  Instruction* not_gpr64(Register reg) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   SHIFTS
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Shift 64-bit gpr left by CL register
   */
  Instruction* shl_gpr64_cl(Register reg) override;

  /*!
   * Shift 64-bit gpr right (logical) by CL register
   */
  Instruction* shr_gpr64_cl(Register reg) override;

  /*!
   * Shift 64-bit gpr right (arithmetic) by CL register
   */
  Instruction* sar_gpr64_cl(Register reg) override;

  /*!
   * Shift 64-ptr left (logical) by the constant shift amount "sa".
   */
  Instruction* shl_gpr64_u8(Register reg, uint8_t sa) override;

  /*!
   * Shift 64-ptr right (logical) by the constant shift amount "sa".
   */
  Instruction* shr_gpr64_u8(Register reg, uint8_t sa) override;

  /*!
   * Shift 64-ptr right (arithmetic) by the constant shift amount "sa".
   */
  Instruction* sar_gpr64_u8(Register reg, uint8_t sa) override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   CONTROL FLOW
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Jump, 32-bit constant offset.  The offset is by default 0 and must be patched later.
   */
  Instruction* jmp_32() override;

  /*!
   * Jump if equal.
   */
  Instruction* je_32() override;

  /*!
   * Jump not equal.
   */
  Instruction* jne_32() override;

  /*!
   * Jump less than or equal.
   */
  Instruction* jle_32() override;

  /*!
   * Jump greater than or equal.
   */
  Instruction* jge_32() override;

  /*!
   * Jump less than
   */
  Instruction* jl_32() override;

  /*!
   * Jump greater than
   */
  Instruction* jg_32() override;

  /*!
   * Jump below or equal
   */
  Instruction* jbe_32() override;

  /*!
   * Jump above or equal
   */
  Instruction* jae_32() override;

  /*!
   * Jump below
   */
  Instruction* jb_32() override;

  /*!
   * Jump above
   */
  Instruction* ja_32() override;

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   FLOAT MATH
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * Compare two floats and set flag register for jump (ucomiss)
   */
  Instruction* cmp_flt_flt(Register a, Register b) override;

  Instruction* sqrts_xmm(Register dst, Register src) override;

  /*!
   * Multiply two floats in xmm's
   */
  Instruction* mulss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Divide two floats in xmm's
   */
  Instruction* divss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Subtract two floats in xmm's
   */
  Instruction* subss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Add two floats in xmm's
   */
  Instruction* addss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Floating point minimum.
   */
  Instruction* minss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Floating point maximum.
   */
  Instruction* maxss_xmm_xmm(Register dst, Register src) override;

  /*!
   * Convert GPR int32 to XMM float (single precision)
   */
  Instruction* int32_to_float(Register dst, Register src) override;

  /*!
   * Convert XMM float to GPR int32(single precision) (truncate)
   */
  Instruction* float_to_int32(Register dst, Register src) override;

  Instruction* nop() override;

  // TODO - rsqrt / abs / sqrt

  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  //   UTILITIES
  //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  /*!
   * A "null" instruction.  This instruction does not generate any bytes
   * but can be referred to by a label.  Useful to insert in place of a real instruction
   * if the real instruction has been optimized out.
   */
  Instruction* null() override;

  /////////////////////////////
  // AVX (VF - Vector Float) //
  /////////////////////////////

  Instruction* nop_vf() override;

  Instruction* wait_vf() override;

  Instruction* mov_vf_vf(Register dst, Register src) override;

  Instruction* loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) override;

  Instruction* loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                               Register addr1,
                                               Register addr2,
                                               s64 offset) override;

  Instruction* loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                                Register addr1,
                                                Register addr2,
                                                s64 offset) override;

  Instruction* storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) override;

  Instruction* storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                                Register addr1,
                                                Register addr2,
                                                s64 offset) override;

  Instruction* storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                                 Register addr1,
                                                 Register addr2,
                                                 s64 offset) override;

  Instruction* loadvf_rip_plus_s32(Register dest, s64 offset) override;

  // TODO - rip relative loads and stores.

  Instruction* blend_vf(Register dst, Register src1, Register src2, u8 mask) override;

  Instruction* shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) override;

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
  Instruction* swizzle_vf(Register dst, Register src, u8 controlBytes) override;

  /*
    Splats a single element in 'src' to all elements in 'dst'
    For example (pseudocode):
    xmm1 = (1.5, 2.5, 3.5, 4.5)
    xmm2 = (1, 2, 3, 4)
    splat_vf(xmm1, xmm2, XMM_ELEMENT::X) override;
    xmm1 = (4, 4, 4, 4)
    */
  Instruction* splat_vf(Register dst, Register src, Register::VF_ELEMENT element) override;

  Instruction* xor_vf(Register dst, Register src1, Register src2) override;

  Instruction* sub_vf(Register dst, Register src1, Register src2) override;

  Instruction* add_vf(Register dst, Register src1, Register src2) override;

  Instruction* mul_vf(Register dst, Register src1, Register src2) override;

  Instruction* max_vf(Register dst, Register src1, Register src2) override;

  Instruction* min_vf(Register dst, Register src1, Register src2) override;

  Instruction* div_vf(Register dst, Register src1, Register src2) override;

  Instruction* sqrt_vf(Register dst, Register src) override;

  Instruction* itof_vf(Register dst, Register src) override;

  Instruction* ftoi_vf(Register dst, Register src) override;

  Instruction* pw_sra(Register dst, Register src, u8 imm) override;

  Instruction* pw_srl(Register dst, Register src, u8 imm) override;

  Instruction* ph_srl(Register dst, Register src, u8 imm) override;

  Instruction* pw_sll(Register dst, Register src, u8 imm) override;

  Instruction* ph_sll(Register dst, Register src, u8 imm) override;

  Instruction* parallel_add_byte(Register dst, Register src0, Register src1) override;

  Instruction* parallel_bitwise_or(Register dst, Register src0, Register src1) override;

  Instruction* parallel_bitwise_xor(Register dst, Register src0, Register src1) override;

  Instruction* parallel_bitwise_and(Register dst, Register src0, Register src1) override;

  // Reminder - a word in MIPS = 32bits = a DWORD in x86
  //     MIPS   ||   x86
  // -----------------------
  // byte       || byte
  // halfword   || word
  // word       || dword
  // doubleword || quadword

  // -- Unpack High Data Instructions
  Instruction* pextub_swapped(Register dst, Register src0, Register src1) override;

  Instruction* pextuh_swapped(Register dst, Register src0, Register src1) override;

  Instruction* pextuw_swapped(Register dst, Register src0, Register src1) override;

  // -- Unpack Low Data Instructions
  Instruction* pextlb_swapped(Register dst, Register src0, Register src1) override;

  Instruction* pextlh_swapped(Register dst, Register src0, Register src1) override;

  Instruction* pextlw_swapped(Register dst, Register src0, Register src1) override;

  // Equal to than comparison as 16 bytes (8 bits)
  Instruction* parallel_compare_e_b(Register dst, Register src0, Register src1) override;

  // Equal to than comparison as 8 halfwords (16 bits)
  Instruction* parallel_compare_e_h(Register dst, Register src0, Register src1) override;

  // Equal to than comparison as 4 words (32 bits)
  Instruction* parallel_compare_e_w(Register dst, Register src0, Register src1) override;

  // Greater than comparison as 16 bytes (8 bits)
  Instruction* parallel_compare_gt_b(Register dst, Register src0, Register src1) override;

  // Greater than comparison as 8 halfwords (16 bits)
  Instruction* parallel_compare_gt_h(Register dst, Register src0, Register src1) override;

  // Greater than comparison as 4 words (32 bits)
  Instruction* parallel_compare_gt_w(Register dst, Register src0, Register src1) override;

  Instruction* vpunpcklqdq(Register dst, Register src0, Register src1) override;

  Instruction* pcpyld_swapped(Register dst, Register src0, Register src1) override;

  Instruction* pcpyud(Register dst, Register src0, Register src1) override;

  Instruction* vpsubd(Register dst, Register src0, Register src1) override;

  Instruction* vpsrldq(Register dst, Register src, u8 imm) override;

  Instruction* vpslldq(Register dst, Register src, u8 imm) override;

  Instruction* vpshuflw(Register dst, Register src, u8 imm) override;

  Instruction* vpshufhw(Register dst, Register src, u8 imm) override;

  Instruction* vpackuswb(Register dst, Register src0, Register src1) override;
};  // namespace IGenX86
}  // namespace emitter
