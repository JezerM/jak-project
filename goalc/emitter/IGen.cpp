
#include "IGen.h"

#include "common/util/os.h"

#include "IGenArm64.h"
#include "IGenX86.h"
#include "goalc/emitter/Instruction.h"

// https://armconverter.com/?code=ret
// https://developer.arm.com/documentation/ddi0487/latest

namespace emitter {
template <typename T>
T igen_cross(T x86, T arm64) {
#if defined CROSS_ARCH_COMPILER
  auto target_arch = get_cpu_info().target_arch;
  switch (target_arch) {
    case cpu_arch_arm64:
      return arm64;
    case cpu_arch_x86_64:
      return x86;
    default:
      break;
  }
  return 0;
#else
#if defined __x86_64__
  return x86;
#elif defined __aarch64__
  return arm64;
#endif
#endif
}

namespace IGen {
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   MOVES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* mov_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_gpr64_gpr64, IGenArm64::mov_gpr64_gpr64);
  return func(dst, src);
}

Instruction* mov_gpr64_u64(Register dst, uint64_t val) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_gpr64_u64, IGenArm64::mov_gpr64_u64);
  return func(dst, val);
}

Instruction* mov_gpr64_u32(Register dst, uint64_t val) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_gpr64_u32, IGenArm64::mov_gpr64_u32);
  return func(dst, val);
}

Instruction* mov_gpr64_s32(Register dst, int64_t val) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_gpr64_s32, IGenArm64::mov_gpr64_s32);
  return func(dst, val);
}

Instruction* movd_gpr32_xmm32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::movd_gpr32_xmm32, IGenArm64::movd_gpr32_xmm32);
  return func(dst, src);
}

Instruction* movd_xmm32_gpr32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::movd_xmm32_gpr32, IGenArm64::movd_xmm32_gpr32);
  return func(dst, src);
}

Instruction* movq_gpr64_xmm64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::movq_gpr64_xmm64, IGenArm64::movq_gpr64_xmm64);
  return func(dst, src);
}

Instruction* movq_xmm64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::movq_xmm64_gpr64, IGenArm64::movq_xmm64_gpr64);
  return func(dst, src);
}

Instruction* mov_xmm32_xmm32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_xmm32_xmm32, IGenArm64::mov_xmm32_xmm32);
  return func(dst, src);
}

// todo - GPR64 -> XMM64 (zext)
// todo - XMM -> GPR64

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   GOAL Loads and Stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* load8s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load8s_gpr64_gpr64_plus_gpr64, IGenArm64::load8s_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* store8_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::store8_gpr64_gpr64_plus_gpr64, IGenArm64::store8_gpr64_gpr64_plus_gpr64);
  return func(addr1, addr2, value);
}

Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8s_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load8s_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                   Register addr2,
                                                   Register value,
                                                   s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store8_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::store8_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(addr1, addr2, value, offset);
}

Instruction* load8s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8s_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load8s_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* store8_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store8_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::store8_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(addr1, addr2, value, offset);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load8u_gpr64_gpr64_plus_gpr64, IGenArm64::load8u_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8u_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load8u_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* load8u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8u_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load8u_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16s_gpr64_gpr64_plus_gpr64,
                         IGenArm64::load16s_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* store16_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store16_gpr64_gpr64_plus_gpr64,
                         IGenArm64::store16_gpr64_gpr64_plus_gpr64);
  return func(addr1, addr2, value);
}

Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store16_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::store16_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(addr1, addr2, value, offset);
}

Instruction* store16_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store16_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::store16_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(addr1, addr2, value, offset);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16s_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load16s_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* load16s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16s_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load16s_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16u_gpr64_gpr64_plus_gpr64,
                         IGenArm64::load16u_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16u_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load16u_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* load16u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16u_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load16u_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32s_gpr64_gpr64_plus_gpr64,
                         IGenArm64::load32s_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* store32_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_gpr64_gpr64_plus_gpr64,
                         IGenArm64::store32_gpr64_gpr64_plus_gpr64);
  return func(addr1, addr2, value);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32s_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load32s_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::store32_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(addr1, addr2, value, offset);
}

Instruction* load32s_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32s_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load32s_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* store32_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::store32_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(addr1, addr2, value, offset);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32u_gpr64_gpr64_plus_gpr64,
                         IGenArm64::load32u_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32u_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load32u_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* load32u_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                     Register addr1,
                                                     Register addr2,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32u_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load32u_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* load64_gpr64_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load64_gpr64_gpr64_plus_gpr64, IGenArm64::load64_gpr64_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* store64_gpr64_gpr64_plus_gpr64(Register addr1, Register addr2, Register value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store64_gpr64_gpr64_plus_gpr64,
                         IGenArm64::store64_gpr64_gpr64_plus_gpr64);
  return func(addr1, addr2, value);
}

Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s8(Register dst,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load64_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load64_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register value,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store64_gpr64_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::store64_gpr64_gpr64_plus_gpr64_plus_s8);
  return func(addr1, addr2, value, offset);
}

Instruction* load64_gpr64_gpr64_plus_gpr64_plus_s32(Register dst,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load64_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load64_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* store64_gpr64_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register value,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store64_gpr64_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::store64_gpr64_gpr64_plus_gpr64_plus_s32);
  return func(addr1, addr2, value, offset);
}

Instruction* store_goal_vf(Register addr, Register value, Register off, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store_goal_vf, IGenArm64::store_goal_vf);
  return func(addr, value, off, offset);
}

Instruction* store_goal_gpr(Register addr, Register value, Register off, int offset, int size) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store_goal_gpr, IGenArm64::store_goal_gpr);
  return func(addr, value, off, offset, size);
}

Instruction* load_goal_xmm128(Register dst, Register addr, Register off, int offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load_goal_xmm128, IGenArm64::load_goal_xmm128);
  return func(dst, addr, off, offset);
}

Instruction* load_goal_gpr(Register dst,
                           Register addr,
                           Register off,
                           int offset,
                           int size,
                           bool sign_extend) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load_goal_gpr, IGenArm64::load_goal_gpr);
  return func(dst, addr, off, offset, size, sign_extend);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - XMM32
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* store32_xmm32_gpr64_plus_gpr64(Register addr1, Register addr2, Register xmm_value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_xmm32_gpr64_plus_gpr64,
                         IGenArm64::store32_xmm32_gpr64_plus_gpr64);
  return func(addr1, addr2, xmm_value);
}

Instruction* load32_xmm32_gpr64_plus_gpr64(Register xmm_dest, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load32_xmm32_gpr64_plus_gpr64, IGenArm64::load32_xmm32_gpr64_plus_gpr64);
  return func(xmm_dest, addr1, addr2);
}

Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s8(Register addr1,
                                                    Register addr2,
                                                    Register xmm_value,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_xmm32_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::store32_xmm32_gpr64_plus_gpr64_plus_s8);
  return func(addr1, addr2, xmm_value, offset);
}

Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s8(Register xmm_dest,
                                                   Register addr1,
                                                   Register addr2,
                                                   s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32_xmm32_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::load32_xmm32_gpr64_plus_gpr64_plus_s8);
  return func(xmm_dest, addr1, addr2, offset);
}

Instruction* store32_xmm32_gpr64_plus_gpr64_plus_s32(Register addr1,
                                                     Register addr2,
                                                     Register xmm_value,
                                                     s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_xmm32_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::store32_xmm32_gpr64_plus_gpr64_plus_s32);
  return func(addr1, addr2, xmm_value, offset);
}

Instruction* lea_reg_plus_off32(Register dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::lea_reg_plus_off32, IGenArm64::lea_reg_plus_off32);
  return func(dest, base, offset);
}

Instruction* lea_reg_plus_off8(Register dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::lea_reg_plus_off8, IGenArm64::lea_reg_plus_off8);
  return func(dest, base, offset);
}

Instruction* lea_reg_plus_off(Register dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::lea_reg_plus_off, IGenArm64::lea_reg_plus_off);
  return func(dest, base, offset);
}

Instruction* store32_xmm32_gpr64_plus_s32(Register base, Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::store32_xmm32_gpr64_plus_s32, IGenArm64::store32_xmm32_gpr64_plus_s32);
  return func(base, xmm_value, offset);
}

Instruction* store32_xmm32_gpr64_plus_s8(Register base, Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::store32_xmm32_gpr64_plus_s8, IGenArm64::store32_xmm32_gpr64_plus_s8);
  return func(base, xmm_value, offset);
}

Instruction* load32_xmm32_gpr64_plus_gpr64_plus_s32(Register xmm_dest,
                                                    Register addr1,
                                                    Register addr2,
                                                    s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32_xmm32_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::load32_xmm32_gpr64_plus_gpr64_plus_s32);
  return func(xmm_dest, addr1, addr2, offset);
}

Instruction* load32_xmm32_gpr64_plus_s32(Register xmm_dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load32_xmm32_gpr64_plus_s32, IGenArm64::load32_xmm32_gpr64_plus_s32);
  return func(xmm_dest, base, offset);
}

Instruction* load32_xmm32_gpr64_plus_s8(Register xmm_dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::load32_xmm32_gpr64_plus_s8, IGenArm64::load32_xmm32_gpr64_plus_s8);
  return func(xmm_dest, base, offset);
}

Instruction* load_goal_xmm32(Register xmm_dest, Register addr, Register off, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load_goal_xmm32, IGenArm64::load_goal_xmm32);
  return func(xmm_dest, addr, off, offset);
}

Instruction* store_goal_xmm32(Register addr, Register xmm_value, Register off, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store_goal_xmm32, IGenArm64::store_goal_xmm32);
  return func(addr, xmm_value, off, offset);
}

Instruction* store_reg_offset_xmm32(Register base, Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store_reg_offset_xmm32, IGenArm64::store_reg_offset_xmm32);
  return func(base, xmm_value, offset);
}

Instruction* load_reg_offset_xmm32(Register xmm_dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load_reg_offset_xmm32, IGenArm64::load_reg_offset_xmm32);
  return func(xmm_dest, base, offset);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   LOADS n' STORES - SIMD (128-bit, QWORDS)
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* store128_gpr64_xmm128(Register gpr_addr, Register xmm_value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store128_gpr64_xmm128, IGenArm64::store128_gpr64_xmm128);
  return func(gpr_addr, xmm_value);
}

Instruction* store128_gpr64_xmm128_s32(Register gpr_addr, Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store128_gpr64_xmm128_s32, IGenArm64::store128_gpr64_xmm128_s32);
  return func(gpr_addr, xmm_value, offset);
}

Instruction* store128_gpr64_xmm128_s8(Register gpr_addr, Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store128_gpr64_xmm128_s8, IGenArm64::store128_gpr64_xmm128_s8);
  return func(gpr_addr, xmm_value, offset);
}

Instruction* load128_xmm128_gpr64(Register xmm_dest, Register gpr_addr) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load128_xmm128_gpr64, IGenArm64::load128_xmm128_gpr64);
  return func(xmm_dest, gpr_addr);
}

Instruction* load128_xmm128_gpr64_s32(Register xmm_dest, Register gpr_addr, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load128_xmm128_gpr64_s32, IGenArm64::load128_xmm128_gpr64_s32);
  return func(xmm_dest, gpr_addr, offset);
}

Instruction* load128_xmm128_gpr64_s8(Register xmm_dest, Register gpr_addr, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load128_xmm128_gpr64_s8, IGenArm64::load128_xmm128_gpr64_s8);
  return func(xmm_dest, gpr_addr, offset);
}

Instruction* load128_xmm128_reg_offset(Register xmm_dest, Register base, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load128_xmm128_reg_offset, IGenArm64::load128_xmm128_reg_offset);
  return func(xmm_dest, base, offset);
}

Instruction* store128_xmm128_reg_offset(Register base, Register xmm_val, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func =
      igen_cross(IGenX86::store128_xmm128_reg_offset, IGenArm64::store128_xmm128_reg_offset);
  return func(base, xmm_val, offset);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   RIP loads and stores
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* load64_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load64_rip_s32, IGenArm64::load64_rip_s32);
  return func(dest, offset);
}

Instruction* load32s_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32s_rip_s32, IGenArm64::load32s_rip_s32);
  return func(dest, offset);
}

Instruction* load32u_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load32u_rip_s32, IGenArm64::load32u_rip_s32);
  return func(dest, offset);
}

Instruction* load16u_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16u_rip_s32, IGenArm64::load16u_rip_s32);
  return func(dest, offset);
}

Instruction* load16s_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load16s_rip_s32, IGenArm64::load16s_rip_s32);
  return func(dest, offset);
}

Instruction* load8u_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8u_rip_s32, IGenArm64::load8u_rip_s32);
  return func(dest, offset);
}

Instruction* load8s_rip_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load8s_rip_s32, IGenArm64::load8s_rip_s32);
  return func(dest, offset);
}

Instruction* static_load(Register dest, s64 offset, int size, bool sign_extend) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::static_load, IGenArm64::static_load);
  return func(dest, offset, size, sign_extend);
}

Instruction* store64_rip_s32(Register src, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store64_rip_s32, IGenArm64::store64_rip_s32);
  return func(src, offset);
}

Instruction* store32_rip_s32(Register src, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store32_rip_s32, IGenArm64::store32_rip_s32);
  return func(src, offset);
}

Instruction* store16_rip_s32(Register src, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store16_rip_s32, IGenArm64::store16_rip_s32);
  return func(src, offset);
}

Instruction* store8_rip_s32(Register src, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store8_rip_s32, IGenArm64::store8_rip_s32);
  return func(src, offset);
}

Instruction* static_store(Register value, s64 offset, int size) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::static_store, IGenArm64::static_store);
  return func(value, offset, size);
}

Instruction* static_addr(Register dst, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::static_addr, IGenArm64::static_addr);
  return func(dst, offset);
}

Instruction* static_load_xmm32(Register xmm_dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::static_load_xmm32, IGenArm64::static_load_xmm32);
  return func(xmm_dest, offset);
}

Instruction* static_store_xmm32(Register xmm_value, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::static_store_xmm32, IGenArm64::static_store_xmm32);
  return func(xmm_value, offset);
}

// TODO, special load/stores of 128 bit values.

// TODO, consider specialized stack loads and stores?
Instruction* load64_gpr64_plus_s32(Register dst_reg, int32_t offset, Register src_reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::load64_gpr64_plus_s32, IGenArm64::load64_gpr64_plus_s32);
  return func(dst_reg, offset, src_reg);
}

Instruction* store64_gpr64_plus_s32(Register addr, int32_t offset, Register value) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::store64_gpr64_plus_s32, IGenArm64::store64_gpr64_plus_s32);
  return func(addr, offset, value);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FUNCTION STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* ret() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::ret, IGenArm64::ret);
  return func();
}

Instruction* push_gpr64(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::push_gpr64, IGenArm64::push_gpr64);
  return func(reg);
}

Instruction* pop_gpr64(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pop_gpr64, IGenArm64::pop_gpr64);
  return func(reg);
}

Instruction* call_r64(Register reg_) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::call_r64, IGenArm64::call_r64);
  return func(reg_);
}

Instruction* jmp_r64(Register reg_) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jmp_r64, IGenArm64::jmp_r64);
  return func(reg_);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   INTEGER MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Instruction* sub_gpr64_imm8s(Register reg, int64_t imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sub_gpr64_imm8s, IGenArm64::sub_gpr64_imm8s);
  return func(reg, imm);
}

Instruction* sub_gpr64_imm32s(Register reg, int64_t imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sub_gpr64_imm32s, IGenArm64::sub_gpr64_imm32s);
  return func(reg, imm);
}

Instruction* add_gpr64_imm8s(Register reg, int64_t v) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::add_gpr64_imm8s, IGenArm64::add_gpr64_imm8s);
  return func(reg, v);
}

Instruction* add_gpr64_imm32s(Register reg, int64_t v) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::add_gpr64_imm32s, IGenArm64::add_gpr64_imm32s);
  return func(reg, v);
}

Instruction* add_gpr64_imm(Register reg, int64_t imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::add_gpr64_imm, IGenArm64::add_gpr64_imm);
  return func(reg, imm);
}

Instruction* sub_gpr64_imm(Register reg, int64_t imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sub_gpr64_imm, IGenArm64::sub_gpr64_imm);
  return func(reg, imm);
}

Instruction* add_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::add_gpr64_gpr64, IGenArm64::add_gpr64_gpr64);
  return func(dst, src);
}

Instruction* sub_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sub_gpr64_gpr64, IGenArm64::sub_gpr64_gpr64);
  return func(dst, src);
}

Instruction* imul_gpr32_gpr32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::imul_gpr32_gpr32, IGenArm64::imul_gpr32_gpr32);
  return func(dst, src);
}

Instruction* imul_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::imul_gpr64_gpr64, IGenArm64::imul_gpr64_gpr64);
  return func(dst, src);
}

Instruction* idiv_gpr32(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::idiv_gpr32, IGenArm64::idiv_gpr32);
  return func(reg);
}

Instruction* unsigned_div_gpr32(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::unsigned_div_gpr32, IGenArm64::unsigned_div_gpr32);
  return func(reg);
}

Instruction* cdq() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::cdq, IGenArm64::cdq);
  return func();
}

Instruction* movsx_r64_r32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::movsx_r64_r32, IGenArm64::movsx_r64_r32);
  return func(dst, src);
}

Instruction* cmp_gpr64_gpr64(Register a, Register b) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::cmp_gpr64_gpr64, IGenArm64::cmp_gpr64_gpr64);
  return func(a, b);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   BIT STUFF
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* or_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::or_gpr64_gpr64, IGenArm64::or_gpr64_gpr64);
  return func(dst, src);
}

Instruction* and_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::and_gpr64_gpr64, IGenArm64::and_gpr64_gpr64);
  return func(dst, src);
}

Instruction* xor_gpr64_gpr64(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::xor_gpr64_gpr64, IGenArm64::xor_gpr64_gpr64);
  return func(dst, src);
}

Instruction* not_gpr64(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::not_gpr64, IGenArm64::not_gpr64);
  return func(reg);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   SHIFTS
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* shl_gpr64_cl(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::shl_gpr64_cl, IGenArm64::shl_gpr64_cl);
  return func(reg);
}

Instruction* shr_gpr64_cl(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::shr_gpr64_cl, IGenArm64::shr_gpr64_cl);
  return func(reg);
}

Instruction* sar_gpr64_cl(Register reg) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sar_gpr64_cl, IGenArm64::sar_gpr64_cl);
  return func(reg);
}

Instruction* shl_gpr64_u8(Register reg, uint8_t sa) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::shl_gpr64_u8, IGenArm64::shl_gpr64_u8);
  return func(reg, sa);
}

Instruction* shr_gpr64_u8(Register reg, uint8_t sa) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::shr_gpr64_u8, IGenArm64::shr_gpr64_u8);
  return func(reg, sa);
}

Instruction* sar_gpr64_u8(Register reg, uint8_t sa) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sar_gpr64_u8, IGenArm64::sar_gpr64_u8);
  return func(reg, sa);
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   CONTROL FLOW
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* jmp_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jmp_32, IGenArm64::jmp_32);
  return func();
}

Instruction* je_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::je_32, IGenArm64::je_32);
  return func();
}

Instruction* jne_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jne_32, IGenArm64::jne_32);
  return func();
}

Instruction* jle_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jle_32, IGenArm64::jle_32);
  return func();
}

Instruction* jge_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jge_32, IGenArm64::jge_32);
  return func();
}

Instruction* jl_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jl_32, IGenArm64::jl_32);
  return func();
}

Instruction* jg_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jg_32, IGenArm64::jg_32);
  return func();
}

Instruction* jbe_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jbe_32, IGenArm64::jbe_32);
  return func();
}

Instruction* jae_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jae_32, IGenArm64::jae_32);
  return func();
}

Instruction* jb_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::jb_32, IGenArm64::jb_32);
  return func();
}

Instruction* ja_32() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::ja_32, IGenArm64::ja_32);
  return func();
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   FLOAT MATH
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* cmp_flt_flt(Register a, Register b) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::cmp_flt_flt, IGenArm64::cmp_flt_flt);
  return func(a, b);
}

Instruction* sqrts_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sqrts_xmm, IGenArm64::sqrts_xmm);
  return func(dst, src);
}

Instruction* mulss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mulss_xmm_xmm, IGenArm64::mulss_xmm_xmm);
  return func(dst, src);
}

Instruction* divss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::divss_xmm_xmm, IGenArm64::divss_xmm_xmm);
  return func(dst, src);
}

Instruction* subss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::subss_xmm_xmm, IGenArm64::subss_xmm_xmm);
  return func(dst, src);
}

Instruction* addss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::addss_xmm_xmm, IGenArm64::addss_xmm_xmm);
  return func(dst, src);
}

Instruction* minss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::minss_xmm_xmm, IGenArm64::minss_xmm_xmm);
  return func(dst, src);
}

Instruction* maxss_xmm_xmm(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::maxss_xmm_xmm, IGenArm64::maxss_xmm_xmm);
  return func(dst, src);
}

Instruction* int32_to_float(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::int32_to_float, IGenArm64::int32_to_float);
  return func(dst, src);
}

Instruction* float_to_int32(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::float_to_int32, IGenArm64::float_to_int32);
  return func(dst, src);
}

Instruction* nop() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::nop, IGenArm64::nop);
  return func();
}

// TODO - rsqrt / abs / sqrt

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//   UTILITIES
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Instruction* null() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::null, IGenArm64::null);
  return func();
}

/////////////////////////////
// AVX (VF - Vector Float) //
/////////////////////////////

Instruction* nop_vf() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::nop_vf, IGenArm64::nop_vf);
  return func();
}

Instruction* wait_vf() {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::wait_vf, IGenArm64::wait_vf);
  return func();
}

Instruction* mov_vf_vf(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mov_vf_vf, IGenArm64::mov_vf_vf);
  return func(dst, src);
}

Instruction* loadvf_gpr64_plus_gpr64(Register dst, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::loadvf_gpr64_plus_gpr64, IGenArm64::loadvf_gpr64_plus_gpr64);
  return func(dst, addr1, addr2);
}

Instruction* loadvf_gpr64_plus_gpr64_plus_s8(Register dst,
                                             Register addr1,
                                             Register addr2,
                                             s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::loadvf_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::loadvf_gpr64_plus_gpr64_plus_s8);
  return func(dst, addr1, addr2, offset);
}

Instruction* loadvf_gpr64_plus_gpr64_plus_s32(Register dst,
                                              Register addr1,
                                              Register addr2,
                                              s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::loadvf_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::loadvf_gpr64_plus_gpr64_plus_s32);
  return func(dst, addr1, addr2, offset);
}

Instruction* storevf_gpr64_plus_gpr64(Register value, Register addr1, Register addr2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::storevf_gpr64_plus_gpr64, IGenArm64::storevf_gpr64_plus_gpr64);
  return func(value, addr1, addr2);
}

Instruction* storevf_gpr64_plus_gpr64_plus_s8(Register value,
                                              Register addr1,
                                              Register addr2,
                                              s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::storevf_gpr64_plus_gpr64_plus_s8,
                         IGenArm64::storevf_gpr64_plus_gpr64_plus_s8);
  return func(value, addr1, addr2, offset);
}

Instruction* storevf_gpr64_plus_gpr64_plus_s32(Register value,
                                               Register addr1,
                                               Register addr2,
                                               s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::storevf_gpr64_plus_gpr64_plus_s32,
                         IGenArm64::storevf_gpr64_plus_gpr64_plus_s32);
  return func(value, addr1, addr2, offset);
}

Instruction* loadvf_rip_plus_s32(Register dest, s64 offset) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::loadvf_rip_plus_s32, IGenArm64::loadvf_rip_plus_s32);
  return func(dest, offset);
}

// TODO - rip relative loads and stores.

Instruction* blend_vf(Register dst, Register src1, Register src2, u8 mask) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::blend_vf, IGenArm64::blend_vf);
  return func(dst, src1, src2, mask);
}

Instruction* shuffle_vf(Register dst, Register src, u8 dx, u8 dy, u8 dz, u8 dw) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::shuffle_vf, IGenArm64::shuffle_vf);
  return func(dst, src, dx, dy, dz, dw);
}

Instruction* swizzle_vf(Register dst, Register src, u8 controlBytes) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::swizzle_vf, IGenArm64::swizzle_vf);
  return func(dst, src, controlBytes);
}

Instruction* splat_vf(Register dst, Register src, Register::VF_ELEMENT element) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::splat_vf, IGenArm64::splat_vf);
  return func(dst, src, element);
}

Instruction* xor_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::xor_vf, IGenArm64::xor_vf);
  return func(dst, src1, src2);
}

Instruction* sub_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sub_vf, IGenArm64::sub_vf);
  return func(dst, src1, src2);
}

Instruction* add_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::add_vf, IGenArm64::add_vf);
  return func(dst, src1, src2);
}

Instruction* mul_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::mul_vf, IGenArm64::mul_vf);
  return func(dst, src1, src2);
}

Instruction* max_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::max_vf, IGenArm64::max_vf);
  return func(dst, src1, src2);
}

Instruction* min_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::min_vf, IGenArm64::min_vf);
  return func(dst, src1, src2);
}

Instruction* div_vf(Register dst, Register src1, Register src2) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::div_vf, IGenArm64::div_vf);
  return func(dst, src1, src2);
}

Instruction* sqrt_vf(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::sqrt_vf, IGenArm64::sqrt_vf);
  return func(dst, src);
}

Instruction* itof_vf(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::itof_vf, IGenArm64::itof_vf);
  return func(dst, src);
}

Instruction* ftoi_vf(Register dst, Register src) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::ftoi_vf, IGenArm64::ftoi_vf);
  return func(dst, src);
}

Instruction* pw_sra(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pw_sra, IGenArm64::pw_sra);
  return func(dst, src, imm);
}

Instruction* pw_srl(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pw_srl, IGenArm64::pw_srl);
  return func(dst, src, imm);
}

Instruction* ph_srl(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::ph_srl, IGenArm64::ph_srl);
  return func(dst, src, imm);
}

Instruction* pw_sll(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pw_sll, IGenArm64::pw_sll);
  return func(dst, src, imm);
}
Instruction* ph_sll(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::ph_sll, IGenArm64::ph_sll);
  return func(dst, src, imm);
}

Instruction* parallel_add_byte(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_add_byte, IGenArm64::parallel_add_byte);
  return func(dst, src0, src1);
}

Instruction* parallel_bitwise_or(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_bitwise_or, IGenArm64::parallel_bitwise_or);
  return func(dst, src0, src1);
}

Instruction* parallel_bitwise_xor(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_bitwise_xor, IGenArm64::parallel_bitwise_xor);
  return func(dst, src0, src1);
}

Instruction* parallel_bitwise_and(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_bitwise_and, IGenArm64::parallel_bitwise_and);
  return func(dst, src0, src1);
}

Instruction* pextub_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextub_swapped, IGenArm64::pextub_swapped);
  return func(dst, src0, src1);
}

Instruction* pextuh_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextuh_swapped, IGenArm64::pextuh_swapped);
  return func(dst, src0, src1);
}

Instruction* pextuw_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextuw_swapped, IGenArm64::pextuw_swapped);
  return func(dst, src0, src1);
}

Instruction* pextlb_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextlb_swapped, IGenArm64::pextlb_swapped);
  return func(dst, src0, src1);
}

Instruction* pextlh_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextlh_swapped, IGenArm64::pextlh_swapped);
  return func(dst, src0, src1);
}

Instruction* pextlw_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pextlw_swapped, IGenArm64::pextlw_swapped);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_e_b(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_e_b, IGenArm64::parallel_compare_e_b);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_e_h(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_e_h, IGenArm64::parallel_compare_e_h);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_e_w(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_e_w, IGenArm64::parallel_compare_e_w);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_gt_b(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_gt_b, IGenArm64::parallel_compare_gt_b);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_gt_h(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_gt_h, IGenArm64::parallel_compare_gt_h);
  return func(dst, src0, src1);
}

Instruction* parallel_compare_gt_w(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::parallel_compare_gt_w, IGenArm64::parallel_compare_gt_w);
  return func(dst, src0, src1);
}

Instruction* vpunpcklqdq(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpunpcklqdq, IGenArm64::vpunpcklqdq);
  return func(dst, src0, src1);
}

Instruction* pcpyld_swapped(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pcpyld_swapped, IGenArm64::pcpyld_swapped);
  return func(dst, src0, src1);
}

Instruction* pcpyud(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::pcpyud, IGenArm64::pcpyud);
  return func(dst, src0, src1);
}

Instruction* vpsubd(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpsubd, IGenArm64::vpsubd);
  return func(dst, src0, src1);
}

Instruction* vpsrldq(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpsrldq, IGenArm64::vpsrldq);
  return func(dst, src, imm);
}

Instruction* vpslldq(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpslldq, IGenArm64::vpslldq);
  return func(dst, src, imm);
}

Instruction* vpshuflw(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpshuflw, IGenArm64::vpshuflw);
  return func(dst, src, imm);
}

Instruction* vpshufhw(Register dst, Register src, u8 imm) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpshufhw, IGenArm64::vpshufhw);
  return func(dst, src, imm);
}

Instruction* vpackuswb(Register dst, Register src0, Register src1) {
  printf("Deciding with: %s\n", __func__);
  auto func = igen_cross(IGenX86::vpackuswb, IGenArm64::vpackuswb);
  return func(dst, src0, src1);
}
}  // namespace IGen
}  // namespace emitter
