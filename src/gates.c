#include "../include/get_bit.h"

int gate_nand(int a, int b) {
  return ~(a & b) & 1;
  // mask with &1 to get least significant bit
  // should probably just mask at outputs
}

int gate_not(int a) { return gate_nand(a, a); }

int gate_and(int a, int b) { return gate_not(gate_nand(a, b)); }

int gate_or(int a, int b) {
  // not(not(a) and not(b))
  return gate_nand(gate_not(a), gate_not(b));
}

int gate_xor(int a, int b) {
  // a or b and not (a and b)
  return (
      gate_nand(gate_nand(a, gate_nand(a, b)), gate_nand(b, gate_nand(a, b))));
}

int gate_mux(int a, int b, int sel) {
  return (gate_or(gate_and(a, gate_not(sel)), gate_and(b, sel)));
}

int gate_demux(int in, int sel) {
  // DemuxResult result = {
  //     out1: and(in, not(sel)),
  //     out2: and(in, sel)
  // };

  int out1 = gate_and(in, gate_not(sel));
  int out2 = gate_and(in, sel);
  return (out1 + (out2 << 1));
}

int gate_not16(int in) {
  int out = 0;
  for (int i = 0; i < 16; i++) {
    int bit = gate_not(get_bit(in, i));
    out |= (bit << i);
  }
  return out;
}

int gate_or16(int a, int b) {
  int out = 0;
  for (int i = 0; i < 16; i++) {
    int bit = gate_or((get_bit(a, i)), get_bit(b, i));
    out |= (bit << i);
  }
  return out;
}

int gate_and16(int a, int b) {
  int out = 0;
  for (int i = 0; i < 16; i++) {
    int bit = gate_and((get_bit(a, i)), get_bit(b, i));
    out |= (bit << i);
  }
  return out;
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
int gate_mux16(int a, int b, int sel) {
  // //not doing the full implementation to keep my marbles safe
  // if (sel) {
  //   return b;
  // }
  // return a;

  int out = 0;
  for (int i = 0; i < 16; i++) {
    int bit_a = get_bit(a, i);
    int bit_b = get_bit(b, i);

    int selected_bit = gate_mux(bit_a, bit_b, sel);

    out |= (selected_bit << i);
  }
  return out;
}

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
      a7,gate_or(
      a6, gate_or(a5, gate_or(a4, gate_or(a3, gate_or(a2, gate_or(a1, a0))))))
      );
}