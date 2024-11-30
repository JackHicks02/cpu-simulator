#include "../include/gates.h"
#include "../include/get_bit.h"

void gate_nand(u8 *a, u8 *b, u8 *out) {
  *out = ~(*a & *b) & 1;
  // mask with &1 to get least significant bit
  // should probably just mask at outputs
}

// Combinational circuits, whose outputs don't depend on the clock signal
// and what has happened previously, unlike sequential circuits,
// could have stayed functionally pure, as this concept of state would not be
// required e.g. the ALU

void gate_not(u8 *a, u8 *out) { gate_nand(a, a, out); }

void gate_and(u8 *a, u8 *b, u8 *out) {
  // having functionaly pure internals for this sort of thing would be
  // preferable when fast gates are used instead this will solve it, but for
  // NAND only it would be useful
  u8 nandResult;
  gate_nand(a, b, &nandResult);

  gate_not(&nandResult, out);
}

void gate_or(u8 *a, u8 *b, u8 *out) {
  // not(not(a) and not(b))
  u8 notA;
  u8 notB;
  gate_not(a, &notA);
  gate_not(b, &notB);

  gate_nand(&notA, &notB, out);
}

void gate_xor(u8 *a, u8 *b, u8 *out) {
  // a or b and not (a and b)

  // even for slow gates this could potentially be packed
  // but would require gates for each gate to pull off?
  u8 AxB;
  gate_and(a, b, &AxB);

  u8 notAxB;
  gate_not(&AxB, &notAxB);

  u8 AvB;
  gate_or(a, b, &AvB);

  gate_and(&AvB, &notAxB, out);

  // return (gate_nand(gate_nand(a, gate_nand(a, b)),
  //                   gate_nand(b, gate_nand(a, b))));
}

void gate_mux(u8 *a, u8 *b, u8 *sel, u8 *out) {
  u8 notSel;
  gate_not(sel, &notSel);

  u8 AxNotSel;
  gate_and(a, &notSel, &AxNotSel);

  u8 BxSel;
  gate_and(b, sel, &BxSel);

  gate_or(&AxNotSel, &BxSel, out);
}

void gate_demux(u8 *in, u8 *sel, u8 *out0, u8 *out1) {
  // DemuxResult result = {
  //     out1: and(in, not(sel)),
  //     out2: and(in, sel)
  // };

  // out 1
  u8 notSel;
  gate_not(sel, &notSel);

  gate_and(in, &notSel, out0);

  // out 2
  gate_and(in, sel, out1);

  // int out1 = gate_and(in, gate_not(sel));
  // int out2 = gate_and(in, sel);
  // return (out1 + (out2 << 1));
}

// could be multiple outputs
void gate_not16(u16 *in, u16 *out) {
  // int out = 0;
  u16 inVal = *in;

  for (int i = 0; i < 16; i++) {
    u8 bit = get_bit(inVal, i);
    u8 notBit;
    gate_not(&bit, &notBit);

    *out |= (notBit << i);
  }
}

void gate_or16(u16 *a, u16 *b, u16 *out) {
  u16 aVal = *a;
  u16 bVal = *b;

  for (int i = 0; i < 16; i++) {
    u8 aBit = get_bit(aVal, i);
    u8 bBit = get_bit(bVal, i);

    u8 AvB;
    gate_or(&aBit, &bBit, &AvB);

    *out |= (AvB << i);
  }
}

void gate_and16(u16 *a, u16 *b, u16 *out) {
  u16 aVal = *a;
  u16 bVal = *b;

  for (int i = 0; i < 16; i++) {
    u8 aBit = get_bit(aVal, i);
    u8 bBit = get_bit(bVal, i);

    u8 AxB;
    gate_and(&aBit, &bBit, &AxB);

    *out |= (AxB << i);
  }
}

// I think this could in theory be the same size as a 16bit number and
//  therefore not any slower, but there might be quirks, revisit this if
// I go insane bit shifting
// Shout out C Dudd
// struct bit16 {
//     unsigned int a : 1;
//     unsigned int b : 1;
//     unsigned int c : 1;
//     unsigned int d : 1;
//     unsigned int e : 1;
//     unsigned int f : 1;
//     unsigned int g : 1;
//     unsigned int h : 1;
//     unsigned int i : 1;
//     unsigned int j : 1;
//     unsigned int k : 1;
//     unsigned int l : 1;
//     unsigned int m : 1;
//     unsigned int n : 1;
//     unsigned int o : 1;
//     unsigned int p : 1;
// };

// remember this is actually returning a 16 bit number or gg
void gate_mux16(u16 *a, u16 *b, u8 *sel, u16 *out) {
  // //not doing the full implementation to keep my marbles safe
  // if (sel) {
  //   return b;
  // }
  // return a;

  u16 aVal = *a;
  u16 bVal = *b;

  for (int i = 0; i < 16; i++) {
    u8 bit_a = get_bit(aVal, i);
    u8 bit_b = get_bit(bVal, i);

    u8 selected_bit;
    gate_mux(&bit_a, &bit_b, sel, &selected_bit);

    // bits never overlap so addition can be used if it turns out that's faster,
    // which it probably isn't ever
    *out |= (selected_bit << i);
  }
}

/**
  8bit
 */
void gate_or8way(u8 *a, u8 *out) {
  // return a != 0

  u8 aVal = *a;

  u8 a0 = get_bit(aVal, 0);
  u8 a1 = get_bit(aVal, 1);
  u8 a2 = get_bit(aVal, 2);
  u8 a3 = get_bit(aVal, 3);
  u8 a4 = get_bit(aVal, 4);
  u8 a5 = get_bit(aVal, 5);
  u8 a6 = get_bit(aVal, 6);
  u8 a7 = get_bit(aVal, 7);

  u8 A0vA1;
  gate_or(&a0, &a1, &A0vA1);

  u8 A0vA1vA2;
  gate_or(&a2, &A0vA1, &A0vA1vA2);

  u8 A0vA1vA2vA3;
  gate_or(&a3, &A0vA1vA2, &A0vA1vA2vA3);

  u8 A0vA1vA2vA3vA4;
  gate_or(&a4, &A0vA1vA2vA3, &A0vA1vA2vA3vA4);

  u8 A0vA1vA2vA3vA4vA5;
  gate_or(&a5, &A0vA1vA2vA3vA4, &A0vA1vA2vA3vA4vA5);

  u8 A0vA1vA2vA3vA4vA5vA6;
  gate_or(&a6, &A0vA1vA2vA3vA4vA5, &A0vA1vA2vA3vA4vA5vA6);

  gate_or(&a7, &A0vA1vA2vA3vA4vA5vA6, out);
}

void gate_mux4way16(u16 *a, u16 *b, u16 *c, u16 *d, u8 *s, u16 *out) {
  u8 sVal = *s;

  u8 s0 = get_bit(sVal, 0), *pS0 = &s0;
  u8 s1 = get_bit(sVal, 1), *pS1 = &s1;

  // if s00 a, s01 b, s10 c, s11 d
  u16 ab, *pAb = &ab;
  gate_mux16(a, b, pS0, pAb);

  u16 cd, *pCd = &cd;
  gate_mux16(c, d, pS0, pCd);

  gate_mux16(pAb, pCd, pS1, out);
}

// 3bit s, s <= 7
void gate_mux8way16(u16 *a, u16 *b, u16 *c, u16 *d, u16 *e, u16 *f, u16 *g,
                    u16 *h, u8 *s, u16 *out) {

  u8 sVal = *s;
  u8 s0 = get_bit(sVal, 0);
  u8 s1 = get_bit(sVal, 1);
  u8 s2 = get_bit(sVal, 2);

  u8 s0vs1 = s0 | (s1 << 1);

  u16 abcd;
  gate_mux4way16(a, b, c, d, &s0vs1, &abcd);

  u16 efgh;
  gate_mux4way16(e, f, g, h, &s0vs1, &efgh);

  gate_mux16(&abcd, &efgh, &s2, out);
}

void gate_demux4way(u8 *in, u8 *sel, u8 *out0, u8 *out1, u8 *out2, u8 *out3) {
  u8 selVal = *sel;
  u8 s0 = get_bit(selVal, 0);
  u8 s1 = get_bit(selVal, 1);

  u8 ab;
  u8 cd;

  gate_demux(in, &s1, &ab, &cd);

  gate_demux(&ab, &s0, out0, out1);
  gate_demux(&cd, &s0, out2, out3);
  // int ab = gate_demux(a_or_b, s0);
  // int cd = gate_demux(c_or_d, s0);

  // int a = ab & 1;
  // int b = (ab >> 1) & 1;
  // int c = cd & 1;
  // int d = (cd >> 1) & 1;

  // int result = a | (b << 1) | (c << 2) | (d << 3);
  // return result;
}

// 1bit in or gg
void gate_demux8way(u8 *in, u8 *sel, u8 *out0, u8 *out1, u8 *out2, u8 *out3,
                    u8 *out4, u8 *out5, u8 *out6, u8 *out7) {
  u8 selVal = *sel;

  u8 s3 = (selVal >> 2) & 1;
  u8 s2 = selVal & 0b11;
  u8 abcd;
  u8 efgh;

  gate_demux(in, &s3, &abcd, &efgh);

  gate_demux4way(&abcd, &s2, out0, out1, out2, out3);

  gate_demux4way(&efgh, &s2, out4, out5, out6, out7);
}