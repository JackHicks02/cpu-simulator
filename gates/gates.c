#include "../utils/get_bit.h"

int nand(int a, int b) {
  return ~(a & b) & 1;
  // mask with &1 to get least significant bit
  // should probably just mask at outputs
}

int not(int a) { return nand(a, a); }

int and (int a, int b) { return not(nand(a, b)); }

int or (int a, int b) {
  // not(not(a) and not(b))
  return nand(not(a), not(b));
}

int xor
    (int a, int b) {
      // a or b and not (a and b)
      return (nand(nand(a, nand(a, b)), nand(b, nand(a, b))));
    }

    int mux(int a, int b, int sel) {
  return (or (and(a, not(sel)), and(b, sel)));
}

int demux(int in, int sel) {
  // DemuxResult result = {
  //     out1: and(in, not(sel)),
  //     out2: and(in, sel)
  // };

  int out1 = and(in, not(sel));
  int out2 = and(in, sel);
  return (out1 + (out2 << 1));
}

int not16(int in) {
  int out = 0;
  for (int i = 0; i < 16; i++) {
    int bit = not(get_bit(in, i));
    out |= (bit << i);
  }
  return out;
}