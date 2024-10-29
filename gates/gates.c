#include "../utils/get_bit.h"

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
