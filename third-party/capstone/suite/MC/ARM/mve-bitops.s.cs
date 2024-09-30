# CS_ARCH_ARM, CS_MODE_THUMB+CS_MODE_V8+CS_MODE_MCLASS, None
0x81,0xef,0x52,0x09 = vorr.i16 q0, #0x12
0x81,0xef,0x52,0x03 = vorr.i32 q0, #0x1200
0x86,0xff,0x5d,0x09 = vorr.i16 q0, #0xed
0x86,0xff,0x5d,0x03 = vorr.i32 q0, #0xed00
0x86,0xff,0x5d,0x05 = vorr.i32 q0, #0xed0000
0x86,0xff,0x5d,0x07 = vorr.i32 q0, #0xed000000
0x82,0xef,0x72,0x09 = vbic.i16 q0, #0x22
0x81,0xef,0x71,0x03 = vbic.i32 q0, #0x1100
0x85,0xff,0x7d,0x09 = vbic.i16 q0, #0xdd
0x85,0xff,0x7d,0x0b = vbic.i16 q0, #0xdd00
0x86,0xff,0x7e,0x01 = vbic.i32 q0, #0xee
0x86,0xff,0x7e,0x03 = vbic.i32 q0, #0xee00
0x86,0xff,0x7e,0x05 = vbic.i32 q0, #0xee0000
0x86,0xff,0x7e,0x07 = vbic.i32 q0, #0xee000000
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0x12,0xef,0x5e,0x01 = vbic q0, q1, q7
0xb0,0xff,0x48,0x00 = vrev64.8 q0, q4
0xb4,0xff,0x46,0x20 = vrev64.16 q1, q3
0xb8,0xff,0x44,0x00 = vrev64.32 q0, q2
0xb0,0xff,0xc2,0x00 = vrev32.8 q0, q1
0xb4,0xff,0xca,0x00 = vrev32.16 q0, q5
0xb0,0xff,0x44,0x01 = vrev16.8 q0, q2
0xb0,0xff,0xc4,0x05 = vmvn q0, q2
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x02,0xff,0x5e,0x41 = veor q2, q1, q7
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x36,0xef,0x54,0x01 = vorn q0, q3, q2
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x24,0xef,0x52,0x21 = vorr q1, q2, q1
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x04,0xef,0x50,0x01 = vand q0, q2, q0
0x40,0xee,0x30,0x8b = vmov.8 q0[1], r8
0x20,0xee,0x30,0x5b = vmov.16 q0[2], r5
0x2d,0xee,0x10,0xbb = vmov.32 q6[3], r11
0x12,0xee,0x10,0x0b = vmov.32 r0, q1[0]
0x35,0xee,0x70,0x1b = vmov.s16 r1, q2[7]
0x79,0xee,0x30,0x0b = vmov.s8 r0, q4[13]
0x93,0xee,0x30,0x0b = vmov.u16 r0, q1[4]
0xfa,0xee,0x70,0x0b = vmov.u8 r0, q5[7]
0x71,0xfe,0x4d,0x8f = vpste
0xb0,0xff,0xc2,0x05 = vmvnt q0, q1
0xb0,0xff,0xc2,0x05 = vmvne q0, q1
0x71,0xfe,0x4d,0x8f = vpste
0x32,0xef,0x54,0x01 = vornt q0, q1, q2
0x32,0xef,0x54,0x01 = vorne q0, q1, q2
