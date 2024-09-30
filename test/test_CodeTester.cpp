/*!
 * @file test_CodeTester.cpp
 * Tests for the CodeTester, a tool for testing the emitter by emitting code and running it
 * from within the test application.
 *
 * These tests should just make sure the basic functionality of CodeTester works, and that it
 * can generate prologues/epilogues, and execute them without crashing.
 */

#include "goalc/emitter/CodeTester.h"
#include "goalc/emitter/IGen.h"
#include "gtest/gtest.h"

using namespace emitter;

TEST(CodeTester, prologue) {
  CodeTester tester;
  tester.init_code_buffer(256);
  tester.emit_push_all_gprs();
  // check we generate the right code for pushing all gpr's
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(),
            "50 51 52 53 54 55 56 57 41 50 41 51 41 52 41 53 41 54 41 55 41 56 41 57");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(),
            "e8 0f 1f f8 e0 0f 1f f8 e1 0f 1f f8 e2 0f 1f f8 e3 0f 1f f8 e4 0f 1f f8 e5 0f 1f f8 "
            "e6 0f 1f f8 e7 0f 1f f8 f7 0f 1f f8 f8 0f 1f f8 f3 0f 1f f8 f4 0f 1f f8 f5 0f 1f f8 "
            "f6 0f 1f f8 ff 0f 1f f8");
#endif
}

TEST(CodeTester, epilogue) {
  CodeTester tester;
  tester.init_code_buffer(256);
  tester.emit_pop_all_gprs();
  // check we generate the right code for popping all gpr's
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(),
            "41 5f 41 5e 41 5d 41 5c 41 5b 41 5a 41 59 41 58 5f 5e 5d 5c 5b 5a 59 58");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(),
            "ff 07 41 f8 f6 07 41 f8 f5 07 41 f8 f4 07 41 f8 f3 07 41 f8 f8 07 41 f8 f7 07 41 f8 "
            "e7 07 41 f8 e6 07 41 f8 e5 07 41 f8 e4 07 41 f8 e3 07 41 f8 e2 07 41 f8 e1 07 41 f8 "
            "e0 07 41 f8 e8 07 41 f8");
#endif
}

TEST(CodeTester, execute_return) {
  CodeTester tester;
  tester.init_code_buffer(256);
  // test creating a function which simply returns
  tester.emit_return();
  // and execute it!
  tester.execute();
}

TEST(CodeTester, execute_push_pop_gprs) {
  CodeTester tester;
  tester.init_code_buffer(256);
  // test we can push/pop gprs without crashing.
  tester.emit_push_all_gprs();
  tester.emit_pop_all_gprs();
  tester.emit_return();
  tester.execute();
}

TEST(CodeTester, simd_store_128) {
  CodeTester tester;
  tester.init_code_buffer(256);
  //  movdqa [rbx], xmm3
  //  movdqa [r14], xmm3
  //  movdqa [rbx], xmm14
  //  movdqa [r14], xmm13
  tester.emit(gIGen->store128_gpr64_xmm128(R9, XMM3));
  tester.emit(gIGen->store128_gpr64_xmm128(ST, XMM3));
  tester.emit(gIGen->store128_gpr64_xmm128(R9, XMM14));
  tester.emit(gIGen->store128_gpr64_xmm128(ST, XMM13));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(),
            "66 0f 7f 1b 66 41 0f 7f 1e 66 44 0f 7f 33 66 45 0f 7f 2e");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "e3 0e 9f 3c a3 0e 9f 3c ee 0e 9f 3c ad 0e 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(SP, XMM1));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 0f 7f 0c 24");  // requires SIB byte.
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "e1 0f 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(R11, XMM13));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 45 0f 7f 2c 24");  // requires SIB byte and REX byte
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "6d 0e 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(R10, XMM1));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 0f 7f 4d 00");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "01 0f 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(R10, XMM11));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 44 0f 7f 5d 00");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "0b 0f 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(PP, XMM2));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 41 0f 7f 55 00");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "82 0e 9f 3c");
#endif

  tester.clear();
  tester.emit(gIGen->store128_gpr64_xmm128(PP, XMM12));
#if defined __x86_64__ || defined _M_X64
  EXPECT_EQ(tester.dump_to_hex_string(), "66 45 0f 7f 65 00");
#elif defined __aarch64__
  EXPECT_EQ(tester.dump_to_hex_string(), "8c 0e 9f 3c");
#endif

  //  tester.emit(gIGen->store128_gpr64_xmm128(R9, XMM3));
  //  tester.emit(gIGen->store128_gpr64_xmm128(ST, XMM3));
  //  tester.emit(gIGen->store128_gpr64_xmm128(R9, XMM14));
  //  tester.emit(gIGen->store128_gpr64_xmm128(ST, XMM13));
  //  EXPECT_EQ(tester.dump_to_hex_string(),
  //            "f3 0f 7f 1b f3 41 0f 7f 1e f3 44 0f 7f 33 f3 45 0f 7f 2e");
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(SP, XMM1));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 0f 7f 0c 24");  // requires SIB byte.
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(R11, XMM13));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 45 0f 7f 2c 24");  // requires SIB byte and REX
  //  byte
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(R10, XMM1));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 0f 7f 4d 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(R10, XMM11));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 44 0f 7f 5d 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(PP, XMM2));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 41 0f 7f 55 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->store128_gpr64_xmm128(PP, XMM12));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 45 0f 7f 65 00");
}

TEST(CodeTester, sub_gpr64_imm8) {
  CodeTester tester;
  tester.init_code_buffer(256);
  for (u32 i = 0; i < alloc_order.size(); i++) {
    auto reg = alloc_order[i];
    tester.emit(gIGen->sub_gpr64_imm8s(reg, -1));
  }
  EXPECT_EQ(tester.dump_to_hex_string(true),
            "4883E8FF4883E9FF4883EAFF4883EBFF4883ECFF4883EDFF4883EEFF4883EFFF4983E8FF4983E9FF4983EA"
            "FF4983EBFF4983ECFF4983EDFF4983EEFF4983EFFF");
}

TEST(CodeTester, add_gpr64_imm8) {
  CodeTester tester;
  tester.init_code_buffer(256);
  for (u32 i = 0; i < alloc_order.size(); i++) {
    auto reg = alloc_order[i];
    tester.emit(gIGen->add_gpr64_imm8s(reg, -1));
  }
  EXPECT_EQ(tester.dump_to_hex_string(true),
            "4883C0FF4883C1FF4883C2FF4883C3FF4883C4FF4883C5FF4883C6FF4883C7FF4983C0FF4983C1FF4983C2"
            "FF4983C3FF4983C4FF4983C5FF4983C6FF4983C7FF");
}

TEST(CodeTester, xmm_load_128) {
  CodeTester tester;
  tester.init_code_buffer(256);

  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM3, R9));
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM3, ST));
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM14, R9));
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM13, ST));
  //  EXPECT_EQ(tester.dump_to_hex_string(),
  //            "f3 0f 6f 1b f3 41 0f 6f 1e f3 44 0f 6f 33 f3 45 0f 6f 2e");
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM1, SP));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 0f 6f 0c 24");  // requires SIB byte.
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM13, R11));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 45 0f 6f 2c 24");  // requires SIB byte and REX
  //  byte
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM1, R10));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 0f 6f 4d 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM11, R10));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 44 0f 6f 5d 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM2, PP));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 41 0f 6f 55 00");
  //
  //  tester.clear();
  //  tester.emit(gIGen->load128_xmm128_gpr64(XMM12, PP));
  //  EXPECT_EQ(tester.dump_to_hex_string(), "f3 45 0f 6f 65 00");
  tester.emit(gIGen->load128_xmm128_gpr64(XMM3, R9));
  tester.emit(gIGen->load128_xmm128_gpr64(XMM3, ST));
  tester.emit(gIGen->load128_xmm128_gpr64(XMM14, R9));
  tester.emit(gIGen->load128_xmm128_gpr64(XMM13, ST));
  EXPECT_EQ(tester.dump_to_hex_string(),
            "66 0f 6f 1b 66 41 0f 6f 1e 66 44 0f 6f 33 66 45 0f 6f 2e");

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM1, SP));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 0f 6f 0c 24");  // requires SIB byte.

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM13, R11));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 45 0f 6f 2c 24");  // requires SIB byte and REX byte

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM1, R10));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 0f 6f 4d 00");

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM11, R10));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 44 0f 6f 5d 00");

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM2, PP));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 41 0f 6f 55 00");

  tester.clear();
  tester.emit(gIGen->load128_xmm128_gpr64(XMM12, PP));
  EXPECT_EQ(tester.dump_to_hex_string(), "66 45 0f 6f 65 00");
}

TEST(CodeTester, push_pop_xmms) {
  CodeTester tester;
  tester.init_code_buffer(512);
  tester.emit_push_all_xmms();
  tester.emit_pop_all_xmms();
  tester.emit_return();
  tester.execute();
}

TEST(CodeTester, push_pop_all_the_things) {
  CodeTester tester;
  tester.init_code_buffer(512);
  tester.emit_push_all_xmms();
  tester.emit_push_all_gprs();

  // ...
  tester.emit_pop_all_gprs();
  tester.emit_pop_all_xmms();
  tester.emit_return();
  tester.execute();
}
