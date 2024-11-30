#include "../include/gates.h"
#include "../include/print_binary.h"
#include <stdio.h>

int test_gate_nand() {
  u8 a, b, out;

  a = 1;
  b = 1;
  gate_nand(&a, &b, &out);
  if (out != 0)
    return 0;

  a = 1;
  b = 0;
  gate_nand(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 1;
  gate_nand(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 0;
  gate_nand(&a, &b, &out);
  if (out != 1)
    return 0;

  return 1; // All tests passed
}

int test_gate_not() {
  u8 a, out;

  a = 1;
  gate_not(&a, &out);
  if (out != 0)
    return 0;

  a = 0;
  gate_not(&a, &out);
  if (out != 1)
    return 0;

  return 1; // All tests passed
}

int test_gate_and() {
  u8 a, b, out;

  a = 1;
  b = 1;
  gate_and(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 1;
  b = 0;
  gate_and(&a, &b, &out);
  if (out != 0)
    return 0;

  a = 0;
  b = 1;
  gate_and(&a, &b, &out);
  if (out != 0)
    return 0;

  a = 0;
  b = 0;
  gate_and(&a, &b, &out);
  if (out != 0)
    return 0;

  return 1; // All tests passed
}

int test_gate_or() {
  u8 a, b, out;

  a = 1;
  b = 1;
  gate_or(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 1;
  b = 0;
  gate_or(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 1;
  gate_or(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 0;
  gate_or(&a, &b, &out);
  if (out != 0)
    return 0;

  return 1; // All tests passed
}

int test_gate_xor() {
  u8 a, b, out;

  a = 1;
  b = 1;
  gate_xor(&a, &b, &out);
  if (out != 0)
    return 0;

  a = 1;
  b = 0;
  gate_xor(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 1;
  gate_xor(&a, &b, &out);
  if (out != 1)
    return 0;

  a = 0;
  b = 0;
  gate_xor(&a, &b, &out);
  if (out != 0)
    return 0;

  return 1; // All tests passed
}

int test_gate_mux() {
  u8 a, b, sel, out;

  a = 0;
  b = 1;
  sel = 0;
  gate_mux(&a, &b, &sel, &out);
  if (out != 0)
    return 0;

  a = 0;
  b = 1;
  sel = 1;
  gate_mux(&a, &b, &sel, &out);
  if (out != 1)
    return 0;

  a = 1;
  b = 0;
  sel = 0;
  gate_mux(&a, &b, &sel, &out);
  if (out != 1)
    return 0;

  a = 1;
  b = 0;
  sel = 1;
  gate_mux(&a, &b, &sel, &out);
  if (out != 0)
    return 0;

  return 1; // All tests passed
}

int test_gate_demux() {
  u8 in, sel, out0, out1;

  in = 1;
  sel = 0;
  gate_demux(&in, &sel, &out0, &out1);
  if (out0 != 1 || out1 != 0)
    return 0;

  in = 1;
  sel = 1;
  gate_demux(&in, &sel, &out0, &out1);
  if (out0 != 0 || out1 != 1)
    return 0;

  in = 0;
  sel = 0;
  gate_demux(&in, &sel, &out0, &out1);
  if (out0 != 0 || out1 != 0)
    return 0;

  in = 0;
  sel = 1;
  gate_demux(&in, &sel, &out0, &out1);
  if (out0 != 0 || out1 != 0)
    return 0;

  return 1; // All tests passed
}

int test_gate_not16() {
  u16 in, out;

  for (int i = 0; i <= 0xFFFF; i++) {
    in = (u16)i; // Ensure `in` is a 16-bit value
    gate_not16(&in, &out);
    if (out != ((~i) & 0xFFFF)) {
      print_binary(i, 16);
      print_binary(out, 16);
      return 0;
    }
  }
  return 1;
}
// This can't be tested properly because the time complexity using the full
// or_16 and iterating it through this is n^3
int test_gate_or16() {
  u16 a, b, out;

  for (int i = 0; i <= 0xFF; i++) {
    for (int j = 0; j <= 0xFF; j++) {
      a = (u16)i;
      b = (u16)j;
      gate_or16(&a, &b, &out);
      if (out != ((a | b) & 0xFFFF)) {
        return 0;
      }
    }
  }

  for (int i = 0xFF00; i <= 0xFFFF; i++) {
    for (int j = 0xFF00; j <= 0xFFFF; j++) {
      a = (u16)i;
      b = (u16)j;
      gate_or16(&a, &b, &out);
      if (out != ((a | b) & 0xFFFF)) {
        return 0;
      }
    }
  }

  return 1; // All tests passed
}

int test_gate_and16() {
  u16 a, b, out;

  for (int i = 0; i <= 0xFF; i++) {
    for (int j = 0; j <= 0xFF; j++) {
      a = (u16)i;
      b = (u16)j;
      gate_and16(&a, &b, &out);
      if (out != ((a & b) & 0xFFFF)) {
        return 0;
      }
    }
  }

  for (int i = 0xFF00; i <= 0xFFFF; i++) {
    for (int j = 0xFF00; j <= 0xFFFF; j++) {
      a = (u16)i;
      b = (u16)j;
      gate_and16(&a, &b, &out);
      if (out != ((a & b) & 0xFFFF)) {
        return 0;
      }
    }
  }

  return 1; // All tests passed
}

int test_gate_mux16() {
  u16 a, b, out;
  u8 sel;

  a = 0xFFFF;
  b = 0x0000;
  sel = 1;
  gate_mux16(&a, &b, &sel, &out);
  if (out != b) {
    return 0;
  }

  a = 0xFFFF;
  b = 0x0000;
  sel = 0;
  gate_mux16(&a, &b, &sel, &out);
  if (out != a) {
    return 0;
  }

  return 1; // All tests passed
}

int test_gate_mux4way16() {
    u16 a, b, c, d, out;
    u8 sel;

    a = 0b1010101; b = 0; c = 0; d = 0;
    sel = 0;
    gate_mux4way16(&a, &b, &c, &d, &sel, &out);
    if (out != a) {
        return 0;
    }

    a = 0; b = 0b1101101; c = 0; d = 0;
    sel = 1;
    gate_mux4way16(&a, &b, &c, &d, &sel, &out);
    if (out != b) {
        return 0;
    }

    a = 0; b = 0; c = 0b0100101; d = 0;
    sel = 0b10;
    gate_mux4way16(&a, &b, &c, &d, &sel, &out);
    if (out != c) {
        return 0;
    }

    a = 0; b = 0; c = 0; d = 0b10111011;
    sel = 0b11;
    gate_mux4way16(&a, &b, &c, &d, &sel, &out);
    if (out != d) {
        return 0;
    }

    a = 0; b = 0; c = 0; d = 0;
    for (int i = 0; i < 4; i++) {
        sel = (u8)i;
        gate_mux4way16(&a, &b, &c, &d, &sel, &out);
        if (out != 0) {
            return 0;
        }
    }

    return 1; // All tests passed
}


int test_gate_mux8way16() {
    u16 a, b, c, d, e, f, g, h, out;
    u8 sel;

    a = 0b1010101010101010;
    b = 0b0101010101010101;
    c = 0b1111000011110000;
    d = 0b0000111100001111;
    e = 0b0011001100110011;
    f = 0b1100110011001100;
    g = 0b1111111100000000;
    h = 0b0000000011111111;

    sel = 0b000;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != a) {
        return 0;
    }

    sel = 0b001;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != b) {
        return 0;
    }

    sel = 0b010;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != c) {
        return 0;
    }

    sel = 0b011;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != d) {
        return 0;
    }

    sel = 0b100;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != e) {
        return 0;
    }

    sel = 0b101;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != f) {
        return 0;
    }

    sel = 0b110;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != g) {
        return 0;
    }

    sel = 0b111;
    gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
    if (out != h) {
        return 0;
    }

    a = b = c = d = e = f = g = h = 0;
    for (int i = 0; i < 8; i++) {
        sel = (u8)i;
        gate_mux8way16(&a, &b, &c, &d, &e, &f, &g, &h, &sel, &out);
        if (out != 0) {
            return 0;
        }
    }

    return 1; // All tests passed
}

int test_gate_demux4way() {
    u8 in, sel, out0, out1, out2, out3;

    in = 1; sel = 0b00;
    gate_demux4way(&in, &sel, &out0, &out1, &out2, &out3);
    if (out0 != 1 || out1 != 0 || out2 != 0 || out3 != 0) {
        return 0;
    }

    in = 1; sel = 0b01;
    gate_demux4way(&in, &sel, &out0, &out1, &out2, &out3);
    if (out0 != 0 || out1 != 1 || out2 != 0 || out3 != 0) {
        return 0;
    }

    in = 1; sel = 0b10;
    gate_demux4way(&in, &sel, &out0, &out1, &out2, &out3);
    if (out0 != 0 || out1 != 0 || out2 != 1 || out3 != 0) {
        return 0;
    }

    in = 1; sel = 0b11;
    gate_demux4way(&in, &sel, &out0, &out1, &out2, &out3);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 1) {
        return 0;
    }

    return 1; // All tests passed
}


int test_gate_demux8way() {
    u8 in, sel, out0, out1, out2, out3, out4, out5, out6, out7;

    in = 1; sel = 0b000;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 1 || out1 != 0 || out2 != 0 || out3 != 0 || 
        out4 != 0 || out5 != 0 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b001;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 1 || out2 != 0 || out3 != 0 || 
        out4 != 0 || out5 != 0 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b010;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 1 || out3 != 0 || 
        out4 != 0 || out5 != 0 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b011;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 1 || 
        out4 != 0 || out5 != 0 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b100;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 0 || 
        out4 != 1 || out5 != 0 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b101;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 0 || 
        out4 != 0 || out5 != 1 || out6 != 0 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b110;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 0 || 
        out4 != 0 || out5 != 0 || out6 != 1 || out7 != 0) {
        return 0;
    }

    in = 1; sel = 0b111;
    gate_demux8way(&in, &sel, &out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7);
    if (out0 != 0 || out1 != 0 || out2 != 0 || out3 != 0 || 
        out4 != 0 || out5 != 0 || out6 != 0 || out7 != 1) {
        return 0;
    }

    return 1; // All tests passed
}

void run_tests() {
  printf("Testing gate functions...\n");

  printf("test_gate_nand: %s\n", test_gate_nand() ? "PASS" : "FAIL");
  printf("test_gate_not: %s\n", test_gate_not() ? "PASS" : "FAIL");
  printf("test_gate_and: %s\n", test_gate_and() ? "PASS" : "FAIL");
  printf("test_gate_or: %s\n", test_gate_or() ? "PASS" : "FAIL");
  printf("test_gate_xor: %s\n", test_gate_xor() ? "PASS" : "FAIL");
  printf("test_gate_mux: %s\n", test_gate_mux() ? "PASS" : "FAIL");
  printf("test_gate_demux: %s\n", test_gate_demux() ? "PASS" : "FAIL");
  printf("test_gate_not16: %s\n", test_gate_not16() ? "PASS" : "FAIL");
  printf("test_gate_or16: %s\n", test_gate_or16() ? "PASS" : "FAIL");
  printf("test_gate_and16: %s\n", test_gate_and16() ? "PASS" : "FAIL");
  printf("test_gate_mux16: %s\n", test_gate_mux16() ? "PASS" : "FAIL");
  printf("test_gate_mux4way16: %s\n", test_gate_mux4way16() ? "PASS" : "FAIL");
  printf("test_gate_mux8way16: %s\n", test_gate_mux8way16() ? "PASS" : "FAIL");
  printf("test_gate_demux4way: %s\n", test_gate_demux4way() ? "PASS" : "FAIL");
  printf("test_gate_demux8way: %s\n", test_gate_demux8way() ? "PASS" : "FAIL");
}

int main() {
  run_tests();
  return 0;
}