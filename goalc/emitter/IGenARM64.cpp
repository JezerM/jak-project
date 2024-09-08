#include "IGenArm64.h"

#include "goalc/emitter/Instruction.h"

// https://armconverter.com/?code=ret
// https://developer.arm.com/documentation/ddi0487/latest

namespace emitter {
namespace IGenArm64 {
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   MOVES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* mov_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* mov_gpr64_u64(Register dst, uint64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* mov_gpr64_u32(Register dst, uint64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* mov_gpr64_s32(Register dst, int64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* movd_gpr32_xmm32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* movd_xmm32_gpr32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* movq_gpr64_xmm64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* movq_xmm64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* mov_xmm32_xmm32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

// todo - GPR64 -> XMM64 (zext)
// todo - XMM -> GPR64

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   GOAL Loads and Stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* load8s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* store8_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  return new InstructionARM64(0b0);
}

Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                   Register addr2,
                                                   Register value,
                                                   s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* store16_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  return new InstructionARM64(0b0);
}

Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* store32_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  return new InstructionARM64(0b0);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.id() << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
  return new InstructionARM64(0b0);
}

Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.id() << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.id() << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
}

Instruction* load64_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* store64_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  return new InstructionARM64(0b0);
}

Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store_goal_vf(Register addr, Register value, Register off, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store_goal_gpr(Register addr, Register value, Register off, int offset, int size) {
  return new InstructionARM64(0b0);
}

Instruction* load_goal_xmm128(Register dst, Register addr, Register off, int offset) {
  return new InstructionARM64(0b0);
}

Instruction* load_goal_gpr(Register dst,
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
      return new InstructionARM64(0b0);
  }
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - XMM32
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* store32_xmm32_gpr64_plus_gpr64(Register addr1, Register addr2, Register xmm_value) {
  return new InstructionARM64(0b0);
}

Instruction* load32_xmm32_gpr64_plus_gpr64(Register xmm_dest, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register xmm_value,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register xmm_value,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* lea_reg_plus_off32(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* lea_reg_plus_off8(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* lea_reg_plus_off(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store32_xmm32_gpr64_plus_s32(Register base, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store32_xmm32_gpr64_plus_s8(Register base, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32_xmm32_gpr64_plus_s32(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load_goal_xmm32(Register xmm_dest, Register addr, Register off, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store_goal_xmm32(Register addr, Register xmm_value, Register off, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - SIMD (128-bit, QWORDS)
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) {
  return new InstructionARM64(0b0);
}

Instruction* store128_gpr64_xmm128_s32(Register gpr_addr, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store128_gpr64_xmm128_s8(Register gpr_addr, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) {
  return new InstructionARM64(0b0);
}

Instruction* load128_xmm128_gpr64_s32(Register xmm_dest, Register gpr_addr, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load128_xmm128_gpr64_s8(Register xmm_dest, Register gpr_addr, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   RIP loads and stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* load64_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load32u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load16s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load8u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* load8s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* static_load(Register dest, s64 offset, int size, bool sign_extend) {
  return new InstructionARM64(0b0);
}

Instruction* store64_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store32_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store16_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* store8_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* static_store(Register value, s64 offset, int size) {
  return new InstructionARM64(0b0);
}

Instruction* static_addr(Register dst, s64 offset) {
  // 01011 000 0000000000001000000 00001
  // 01011 000 0000000000000000000 00111
  ASSERT(dst.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  u32 instruction = 0b01011 << 27;
  instruction |= offset << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
}

Instruction* static_load_xmm32(Register xmm_dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* static_store_xmm32(Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

// TODO, special load/stores of 128 bit values.

// TODO, consider specialized stack loads and stores?
Instruction* load64_gpr64_plus_s32(Register dst_reg, int32_t offset, Register src_reg) {
  return new InstructionARM64(0b0);
}

Instruction* store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FUNCTION STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* ret() {
  return new InstructionARM64(0xD65F03C0);
}

Instruction* push_gpr64(Register reg) {
  // pg. 1998
  // 11111 000000 111110000 11 11111 00001
  // 11111 000000 111110000 11 11111 00011
  ASSERT(reg.is_gpr());
  u32 instruction = 0b11111 << 27;
  instruction |= 0b11111 << 16;
  instruction |= 0b11 << 10;
  instruction |= 31 << 5;
  instruction |= reg.id();
  return new InstructionARM64(instruction);
}

Instruction* pop_gpr64(Register reg) {
  // pg. 1998
  // 11111 000010 111110000 11 11111 00001
  // 11111 000010 111110000 11 11111 00011
  ASSERT(reg.is_gpr());
  u32 instruction = 0b11111 << 27;
  instruction |= 0b1 << 22;
  instruction |= 0b11111 << 16;
  instruction |= 0b11 << 10;
  instruction |= 31 << 5;
  instruction |= reg.id();
  return new InstructionARM64(instruction);
}

Instruction* call_r64(Register reg_) {
  // 11010110001 11111 0000 00 00001 00000
  ASSERT(reg_.is_gpr());
  u32 instruction = 0b1101011000111111 << 16;
  instruction |= reg_.id() << 5;
  return new InstructionARM64(instruction);
}

Instruction* jmp_r64(Register reg_) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   INTEGER MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* sub_gpr64_imm8s(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* sub_gpr64_imm32s(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* add_gpr64_imm8s(Register reg, int64_t v) {
  return new InstructionARM64(0b0);
}

Instruction* add_gpr64_imm32s(Register reg, int64_t v) {
  return new InstructionARM64(0b0);
}

Instruction* add_gpr64_imm(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* sub_gpr64_imm(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* add_gpr64_gpr64(Register dst, Register src) {
  // 10001011 000 00010 000000 00001 00001
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  u32 instruction = 0b10001011 << 24;
  instruction |= src.id() << 16;
  instruction |= dst.id() << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
}

Instruction* sub_gpr64_gpr64(Register dst, Register src) {
  // 11001011 000 00010 000000 00001 00001
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  u32 instruction = 0b11001011000 << 21;
  instruction |= src.id() << 16;
  instruction |= dst.id() << 5;
  instruction |= dst.id();
  return new InstructionARM64(instruction);
}

Instruction* imul_gpr32_gpr32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* imul_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* idiv_gpr32(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* unsigned_div_gpr32(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* cdq() {
  return new InstructionARM64(0b0);
}

Instruction* movsx_r64_r32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* cmp_gpr64_gpr64(Register a, Register b) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   BIT STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* or_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* and_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* xor_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* not_gpr64(Register reg) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   SHIFTS
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* shl_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* shr_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* sar_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* shl_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

Instruction* shr_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

Instruction* sar_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   CONTROL FLOW
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* jmp_32() {
  return new InstructionARM64(0b0);
}

Instruction* je_32() {
  return new InstructionARM64(0b0);
}

Instruction* jne_32() {
  return new InstructionARM64(0b0);
}

Instruction* jle_32() {
  return new InstructionARM64(0b0);
}

Instruction* jge_32() {
  return new InstructionARM64(0b0);
}

Instruction* jl_32() {
  return new InstructionARM64(0b0);
}

Instruction* jg_32() {
  return new InstructionARM64(0b0);
}

Instruction* jbe_32() {
  return new InstructionARM64(0b0);
}

Instruction* jae_32() {
  return new InstructionARM64(0b0);
}

Instruction* jb_32() {
  return new InstructionARM64(0b0);
}

Instruction* ja_32() {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FLOAT MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* cmp_flt_flt(Register a, Register b) {
  return new InstructionARM64(0b0);
}

Instruction* sqrts_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* mulss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* divss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* subss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* addss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* minss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* maxss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* int32_to_float(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* float_to_int32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* nop() {
  return new InstructionARM64(0b0);
}

// TODO - rsqrt / abs / sqrt

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   UTILITIES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* null() {
  return new InstructionARM64(0b0);
}

/////////////////////////////
// AVX (VF - Vector Float) //
/////////////////////////////

Instruction* nop_vf() {
  return new InstructionARM64(0b0);
}

Instruction* wait_vf() {
  return new InstructionARM64(0b0);
}

Instruction* mov_vf_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                             Register addr1,
                                             Register addr2,
                                             s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                              Register addr1,
                                              Register addr2,
                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                              Register addr1,
                                              Register addr2,
                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                               Register addr1,
                                               Register addr2,
                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* loadvf_rip_plus_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

// TODO - rip relative loads and stores.

Instruction* blend_vf(Register dst, Register src1, Register src2, u8 mask) {
  return new InstructionARM64(0b0);
}

Instruction* shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) {
  return new InstructionARM64(0b0);
}

Instruction* swizzle_vf(Register dst, Register src, u8 controlBytes) {
  return new InstructionARM64(0b0);
}

Instruction* splat_vf(Register dst, Register src, Register::VF_ELEMENT element) {
  return new InstructionARM64(0b0);
}

Instruction* xor_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* sub_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* add_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* mul_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* max_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* min_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* div_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* sqrt_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* itof_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* ftoi_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* pw_sra(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* pw_srl(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* ph_srl(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* pw_sll(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}
Instruction* ph_sll(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_add_byte(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_bitwise_or(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_bitwise_xor(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_bitwise_and(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextub_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextuh_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextuw_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextlb_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextlh_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pextlw_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_e_b(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_e_h(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_e_w(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_gt_b(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_gt_h(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* parallel_compare_gt_w(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* vpunpcklqdq(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pcpyld_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* pcpyud(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* vpsubd(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* vpsrldq(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* vpslldq(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* vpshuflw(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* vpshufhw(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* vpackuswb(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}
}  // namespace IGenArm64
}  // namespace emitter
