#include "../include/gates.h"
#include "../include/get_bit.h"

void gate_nand(u8 *a, u8 *b, u8 *out) {
  *out = ~(*a & *b) & 1;
  // mask with &1 to get least significant bit
  // should probably just mask at outputs
}

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
  gate_and(a, b, &BxSel);

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
int gate_or8way(int a) {
  // return a != 0

  int a0 = get_bit(a, 0);
  int a1 = get_bit(a, 1);
  int a2 = get_bit(a, 2);
  int a3 = get_bit(a, 3);
  int a4 = get_bit(a, 4);
  int a5 = get_bit(a, 5);
  int a6 = get_bit(a, 6);
  int a7 = get_bit(a, 7);

  return gate_or(
      a7,
      gate_or(
          a6,
          gate_or(a5, gate_or(a4, gate_or(a3, gate_or(a2, gate_or(a1, a0)))))));
}

int gate_mux4way16(int a, int b, int c, int d, int s) {
  int s0 = get_bit(s, 0);
  int s1 = get_bit(s, 1);

  // if s00 a, s01 b, s10 c, s11 d
  int ab = gate_mux16(a, b, s0);
  int cd = gate_mux16(c, d, s0);

  return gate_mux16(ab, cd, s1);
}

// 3bit s, s <= 7
int gate_mux8way16(int a, int b, int c, int d, int e, int f, int g, int h,
                   int s) {
  int s0 = get_bit(s, 0);
  int s1 = get_bit(s, 1);
  int s2 = get_bit(s, 2);

  int abcd = gate_mux4way16(a, b, c, d, s0 | (s1 << 1));
  int efgh = gate_mux4way16(e, f, g, h, s0 | (s1 << 1));

  return gate_mux16(abcd, efgh, s2);
}

// this is probably bit, really should use custom types to make this not
// misleading 2bit s, 1bit in pls
int gate_demux4way(int in, int sel) {
  int s0 = get_bit(sel, 0);
  int s1 = get_bit(sel, 1);

  int abcd = gate_demux(in, s1);

  int a_or_b = (abcd)&1;
  int c_or_d = (abcd >> 1) & 1;

  int ab = gate_demux(a_or_b, s0);
  int cd = gate_demux(c_or_d, s0);

  int a = ab & 1;
  int b = (ab >> 1) & 1;
  int c = cd & 1;
  int d = (cd >> 1) & 1;

  int result = a | (b << 1) | (c << 2) | (d << 3);
  return result;
}

// 1bit in or gg
int gate_demux8way(int in, int sel) {
  int s3 = (sel >> 2) & 1;

  // this is so pointless lmao
  int abcdefgh = gate_demux4way(in, s3);

  int abcd = abcdefgh & 1;
  int efgh = (abcdefgh >> 1) & 1;

  int a_b_c_d = gate_demux4way(abcd, (sel)&0b11);
  int e_f_g_h = gate_demux4way(efgh, (sel)&0b11);

  int result = a_b_c_d | (e_f_g_h << 4);
  return result;
}