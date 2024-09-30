#include "IGenArm64.h"

#include "goalc/emitter/Instruction.h"

// https://armconverter.com/?code=ret
// https://developer.arm.com/documentation/ddi0487/latest

namespace emitter {
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   MOVES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::mov_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mov_gpr64_u64(Register dst, uint64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mov_gpr64_u32(Register dst, uint64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mov_gpr64_s32(Register dst, int64_t val) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::movd_gpr32_xmm32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::movd_xmm32_gpr32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::movq_gpr64_xmm64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::movq_xmm64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mov_xmm32_xmm32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

// todo - GPR64 -> XMM64 (zext)
// todo - XMM -> GPR64

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   GOAL Loads and Stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::load8s_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store8_gpr64_gpr64_plus_gpr64(Register addr1,
                                                      Register addr2,
                                                      Register value) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                              Register addr2,
                                                              Register value,
                                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8u_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16s_gpr64_gpr64_plus_gpr64(Register dst,
                                                       Register addr1,
                                                       Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store16_gpr64_gpr64_plus_gpr64(Register addr1,
                                                       Register addr2,
                                                       Register value) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                                Register addr2,
                                                                Register value,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                                Register addr1,
                                                                Register addr2,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16u_gpr64_gpr64_plus_gpr64(Register dst,
                                                       Register addr1,
                                                       Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                                Register addr1,
                                                                Register addr2,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32s_gpr64_gpr64_plus_gpr64(Register dst,
                                                       Register addr1,
                                                       Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_gpr64_gpr64_plus_gpr64(Register addr1,
                                                       Register addr2,
                                                       Register value) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                                Register addr1,
                                                                Register addr2,
                                                                s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.hw_id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.hw_id() << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                                Register addr2,
                                                                Register value,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32u_gpr64_gpr64_plus_gpr64(Register dst,
                                                       Register addr1,
                                                       Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.hw_id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.hw_id() << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                                Register addr1,
                                                                Register addr2,
                                                                s64 offset) {
  // ldr x1, [x2, x3]
  // 11111000011 00011 0110 10 00010 00001
  u32 instruction = 0b11111000011 << 21;
  instruction |= addr2.hw_id() << 16;
  instruction |= 0b011010 << 10;
  instruction |= addr1.hw_id() << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::load64_gpr64_gpr64_plus_gpr64(Register dst,
                                                      Register addr1,
                                                      Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store64_gpr64_gpr64_plus_gpr64(Register addr1,
                                                       Register addr2,
                                                       Register value) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                               Register addr2,
                                                               Register value,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                                Register addr2,
                                                                Register value,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store_goal_vf(Register addr, Register value, Register off, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store_goal_gpr(Register addr,
                                       Register value,
                                       Register off,
                                       int offset,
                                       int size) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load_goal_xmm128(Register dst, Register addr, Register off, int offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load_goal_gpr(Register dst,
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
Instruction* IGenArm64::store32_xmm32_gpr64_plus_gpr64(Register addr1,
                                                       Register addr2,
                                                       Register xmm_value) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32_xmm32_gpr64_plus_gpr64(Register xmm_dest,
                                                      Register addr1,
                                                      Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                               Register addr2,
                                                               Register xmm_value,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                              Register addr1,
                                                              Register addr2,
                                                              s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                                Register addr2,
                                                                Register xmm_value,
                                                                s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::lea_reg_plus_off32(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::lea_reg_plus_off8(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::lea_reg_plus_off(Register dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_xmm32_gpr64_plus_s32(Register base,
                                                     Register xmm_value,
                                                     s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_xmm32_gpr64_plus_s8(Register base, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                               Register addr1,
                                                               Register addr2,
                                                               s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32_xmm32_gpr64_plus_s32(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load_goal_xmm32(Register xmm_dest,
                                        Register addr,
                                        Register off,
                                        s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store_goal_xmm32(Register addr,
                                         Register xmm_value,
                                         Register off,
                                         s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - SIMD (128-bit, QWORDS)
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) {
  // str q0, [x0, #-0x10]!
  // Offset: -16
  return store128_xmm128_reg_offset(gpr_addr, xmm_value, 0b111110000);
}

Instruction* IGenArm64::store128_gpr64_xmm128_s32(Register gpr_addr,
                                                  Register xmm_value,
                                                  s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store128_gpr64_xmm128_s8(Register gpr_addr,
                                                 Register xmm_value,
                                                 s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) {
  // ldr q0, [x0], #0x10
  // Offset: 16
  return load128_xmm128_reg_offset(xmm_dest, gpr_addr, 0b10000);
}

Instruction* IGenArm64::load128_xmm128_gpr64_s32(Register xmm_dest, Register gpr_addr, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load128_xmm128_gpr64_s8(Register xmm_dest, Register gpr_addr, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) {
  // ldr q0, [x0], #0x10
  // 00 1111 00 110 000010000 01 00001 00001
  ASSERT(xmm_dest.is_128bit_simd());
  ASSERT(base.is_gpr());
  u32 instruction = 0b001111 << 26;
  instruction |= 0b11 << 22;
  instruction |= offset << 12;
  instruction |= 0b01 << 10;
  instruction |= base.hw_id() << 5;
  instruction |= xmm_dest.hw_id();

  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) {
  // str q0, [x0, #-0x10]!
  // 00 1111 00 100 111110000 01 00001 00001
  ASSERT(base.is_gpr());
  ASSERT(xmm_val.is_128bit_simd());
  u32 instruction = 0b001111 << 26;
  instruction |= 0b1 << 23;
  instruction |= 0b11111 << 16;
  instruction |= 0b11 << 10;
  instruction |= base.hw_id() << 5;
  instruction |= xmm_val.hw_id();

  return new InstructionARM64(instruction);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   RIP loads and stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::load64_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load32u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load16s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8u_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::load8s_rip_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::static_load(Register dest, s64 offset, int size, bool sign_extend) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store64_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store32_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store16_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store8_rip_s32(Register src, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::static_store(Register value, s64 offset, int size) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::static_addr(Register dst, s64 offset) {
  // ldr x1, #0x100
  // 01011 000 0000000000001000000 00001
  // 01011 000 0000000000000000000 00111
  ASSERT(dst.is_gpr());
  ASSERT(offset >= INT32_MIN && offset <= INT32_MAX);

  u32 instruction = 0b01011 << 27;
  instruction |= offset << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::static_load_xmm32(Register xmm_dest, s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::static_store_xmm32(Register xmm_value, s64 offset) {
  return new InstructionARM64(0b0);
}

// TODO, special load/stores of 128 bit values.

// TODO, consider specialized stack loads and stores?
Instruction* IGenArm64::load64_gpr64_plus_s32(Register dst_reg, int32_t offset, Register src_reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FUNCTION STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::ret() {
  return new InstructionARM64(0xD65F03C0);
}

Instruction* IGenArm64::push_gpr64(Register reg) {
  // pg. 1998
  // str x1, [sp, #-0x10]!
  // 11111 000000 111110000 11 11111 00001
  // 11111 000000 111110000 11 11111 00011
  ASSERT(reg.is_gpr());
  u32 instruction = 0b11111 << 27;
  instruction |= 0b11111 << 16;
  instruction |= 0b11 << 10;
  instruction |= 31 << 5;
  instruction |= reg.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::pop_gpr64(Register reg) {
  // pg. 1998
  // ldr x0, [sp], #0x10
  // 11111 000010 000010000 01 11111 00000
  ASSERT(reg.is_gpr());
  u32 instruction = 0b11111 << 27;
  instruction |= 0b1 << 22;
  instruction |= 0b1 << 16;
  instruction |= 0b1 << 10;
  instruction |= 31 << 5;
  instruction |= reg.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::call_r64(Register reg_) {
  // blr x1
  // 11010110001 11111 0000 00 00001 00000
  ASSERT(reg_.is_gpr());
  u32 instruction = 0b1101011000111111 << 16;
  instruction |= reg_.hw_id() << 5;
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::jmp_r64(Register reg_) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   INTEGER MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* IGenArm64::sub_gpr64_imm8s(Register reg, int64_t imm) {
  // sub sp, sp, #8
  // 110 1000100 000000001000 11111 11111
  if (imm < 0) {
    return add_gpr64_imm8s(reg, -imm);
  }
  ASSERT(reg.is_gpr());
  ASSERT(imm <= UINT8_MAX);
  u32 instruction = 0b1101000100 << 22;
  instruction |= imm << 10;
  instruction |= reg.hw_id() << 5;
  instruction |= reg.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::sub_gpr64_imm32s(Register reg, int64_t imm) {
  return sub_gpr64_imm8s(reg, imm);
}

Instruction* IGenArm64::add_gpr64_imm8s(Register reg, int64_t v) {
  // add sp, sp, #8
  // 100 1000100 000000001000 11111 11111
  if (v < 0) {
    return sub_gpr64_imm8s(reg, -v);
  }
  ASSERT(reg.is_gpr());
  ASSERT(v <= UINT8_MAX);
  u32 instruction = 0b1001000100 << 22;
  instruction |= v << 10;
  instruction |= reg.hw_id() << 5;
  instruction |= reg.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::add_gpr64_imm32s(Register reg, int64_t v) {
  return add_gpr64_imm8s(reg, v);
}

Instruction* IGenArm64::add_gpr64_imm(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sub_gpr64_imm(Register reg, int64_t imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::add_gpr64_gpr64(Register dst, Register src) {
  // add x1, x1, x2
  // 10001011 000 00010 000000 00001 00001
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  u32 instruction = 0b10001011 << 24;
  instruction |= src.hw_id() << 16;
  instruction |= dst.hw_id() << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::sub_gpr64_gpr64(Register dst, Register src) {
  // sub x1, x1, x2
  // 11001011 000 00010 000000 00001 00001
  ASSERT(dst.is_gpr());
  ASSERT(src.is_gpr());
  u32 instruction = 0b11001011000 << 21;
  instruction |= src.hw_id() << 16;
  instruction |= dst.hw_id() << 5;
  instruction |= dst.hw_id();
  return new InstructionARM64(instruction);
}

Instruction* IGenArm64::imul_gpr32_gpr32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::imul_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::idiv_gpr32(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::unsigned_div_gpr32(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::cdq() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::movsx_r64_r32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::cmp_gpr64_gpr64(Register a, Register b) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   BIT STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::or_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::and_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::xor_gpr64_gpr64(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::not_gpr64(Register reg) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   SHIFTS
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::shl_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::shr_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sar_gpr64_cl(Register reg) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::shl_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::shr_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sar_gpr64_u8(Register reg, uint8_t sa) {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   CONTROL FLOW
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::jmp_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::je_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jne_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jle_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jge_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jl_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jg_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jbe_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jae_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::jb_32() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::ja_32() {
  return new InstructionARM64(0b0);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FLOAT MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::cmp_flt_flt(Register a, Register b) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sqrts_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mulss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::divss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::subss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::addss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::minss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::maxss_xmm_xmm(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::int32_to_float(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::float_to_int32(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::nop() {
  return new InstructionARM64(0b0);
}

// TODO - rsqrt / abs / sqrt

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   UTILITIES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* IGenArm64::null() {
  return new InstructionARM64(0b0);
}

/////////////////////////////
// AVX (VF - Vector Float) //
/////////////////////////////

Instruction* IGenArm64::nop_vf() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::wait_vf() {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mov_vf_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                                        Register addr1,
                                                        Register addr2,
                                                        s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                                         Register addr1,
                                                         Register addr2,
                                                         s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                                         Register addr1,
                                                         Register addr2,
                                                         s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                                          Register addr1,
                                                          Register addr2,
                                                          s64 offset) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::loadvf_rip_plus_s32(Register dest, s64 offset) {
  return new InstructionARM64(0b0);
}

// TODO - rip relative loads and stores.

Instruction* IGenArm64::blend_vf(Register dst, Register src1, Register src2, u8 mask) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::swizzle_vf(Register dst, Register src, u8 controlBytes) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::splat_vf(Register dst, Register src, Register::VF_ELEMENT element) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::xor_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sub_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::add_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::mul_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::max_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::min_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::div_vf(Register dst, Register src1, Register src2) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::sqrt_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::itof_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::ftoi_vf(Register dst, Register src) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pw_sra(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pw_srl(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::ph_srl(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pw_sll(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}
Instruction* IGenArm64::ph_sll(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_add_byte(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_bitwise_or(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_bitwise_xor(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_bitwise_and(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextub_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextuh_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextuw_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextlb_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextlh_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pextlw_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_e_b(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_e_h(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_e_w(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_gt_b(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_gt_h(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::parallel_compare_gt_w(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpunpcklqdq(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pcpyld_swapped(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::pcpyud(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpsubd(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpsrldq(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpslldq(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpshuflw(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpshufhw(Register dst, Register src, u8 imm) {
  return new InstructionARM64(0b0);
}

Instruction* IGenArm64::vpackuswb(Register dst, Register src0, Register src1) {
  return new InstructionARM64(0b0);
}
}  // namespace emitter
