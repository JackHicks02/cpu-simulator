#include "../include/gates.h"
#include "../include/print_binary.h"
#include <stdio.h>

int gate_nand(int a, int b);
int gate_not(int a);
int gate_and(int a, int b);
int gate_or(int a, int b);
int gate_xor(int a, int b);
int gate_mux(int a, int b, int sel);
int gate_demux(int in, int sel);
int gate_not16(int in);
int gate_or16(int a, int b);

int test_gate_nand() {
  return gate_nand(1, 1) == 0 && gate_nand(1, 0) == 1 && gate_nand(0, 1) == 1 &&
         gate_nand(0, 0) == 1;
}

int test_gate_not() { return gate_not(1) == 0 && gate_not(0) == 1; }

int test_gate_and() {
  return gate_and(1, 1) == 1 && gate_and(1, 0) == 0 && gate_and(0, 1) == 0 &&
         gate_and(0, 0) == 0;
}

int test_gate_or() {
  return gate_or(1, 1) == 1 && gate_or(1, 0) == 1 && gate_or(0, 1) == 1 &&
         gate_or(0, 0) == 0;
}

int test_gate_xor() {
  return gate_xor(1, 1) == 0 && gate_xor(1, 0) == 1 && gate_xor(0, 1) == 1 &&
         gate_xor(0, 0) == 0;
}

int test_gate_mux() {
  return gate_mux(0, 1, 0) == 0 && gate_mux(0, 1, 1) == 1 &&
         gate_mux(1, 0, 0) == 1 && gate_mux(1, 0, 1) == 0;
}

int test_gate_demux() {
  return gate_demux(1, 0) == 1 && gate_demux(1, 1) == 0b10 &&
         gate_demux(0, 0) == 0 && gate_demux(0, 1) == 0;
}

int test_gate_not16() {
  for (int i = 0; i <= 0xFFFF; i++) {
    // must mask to 16 bits or it won't be equal
    if (gate_not16(i) != ((~i) & 0xFFFF)) {
      print_binary(i, 16);
      print_binary(gate_not16(i), 16);
      return 0;
    }
  }
  return 1;
}

// This can't be tested properly because the time complexity using the full
// or_16 and iterating it through this is n^3
int test_gate_or16() {
  for (int a = 0; a <= 0xFF; a++) {
    for (int b = 0; b <= 0xFF; b++) {
      if (gate_or16(a, b) != ((a | b) & 0xFFFF)) {
        return 0;
      }
    }
  }
  for (int a = 0xFF00; a <= 0xFFFF; a++) {
    for (int b = 0xFF00; b <= 0xFFFF; b++) {
      if (gate_or16(a, b) != ((a | b) & 0xFFFF)) {
        return 0;
      }
    }
  }
  return 1;
}

int test_gate_and16() {
  for (int a = 0; a <= 0xFF; a++) {
    for (int b = 0; b <= 0xFF; b++) {
      if (gate_and16(a, b) != ((a & b) & 0xFFFF)) {
        return 0;
      }
    }
  }
  for (int a = 0xFF00; a <= 0xFFFF; a++) {
    for (int b = 0xFF00; b <= 0xFFFF; b++) {
      if (gate_and16(a, b) != ((a & b) & 0xFFFF)) {
        return 0;
      }
    }
  }
  return 1;
}

int test_gate_mux16() {
  int max = 0xFFFF;
  int min = 0;

  if (gate_mux16(max, min, 1) != min) {
    return 0;
  }
  if (gate_mux16(max, min, 0) != max) {
    return 0;
  }

  return 1;
}

int test_gate_mux4way16() {
  int a, b = 0, c = 0, d = 0;
  a = 0b1010101;
  int result = 0;

  result = gate_mux4way16(a, b, c, d, 0);
  if (result != a) {
    return 0;
  }
  a = 0;
  b = 0b1101101;

  result = gate_mux4way16(a, b, c, d, 1);
  if (result != b) {
    return 0;
  }
  b = 0;
  c = 0b0100101;

  result = gate_mux4way16(a, b, c, d, 0b10);
  if (result != c) {
    return 0;
  }
  c = 0;
  d = 0b10111011;

  result = gate_mux4way16(a, b, c, d, 0b11);
  if (result != d) {
    return 0;
  }
  d = 0;

  for (int i = 0; i < 4; i++)
    if (gate_mux4way16(a, b, c, d, i) != 0) {
      return 0;
    }

  return 1;
}

int test_gate_mux8way16() {
  int a, b, c, d, e, f, g, h;
  int result = 0;

  a = 0b1010101010101010;
  b = 0b0101010101010101;
  c = 0b1111000011110000;
  d = 0b0000111100001111;
  e = 0b0011001100110011;
  f = 0b1100110011001100;
  g = 0b1111111100000000;
  h = 0b0000000011111111;

  // Test all selector values
  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b000);
  if (result != a) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b001);
  if (result != b) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b010);
  if (result != c) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b011);
  if (result != d) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b100);
  if (result != e) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b101);
  if (result != f) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b110);
  if (result != g) {
    return 0;
  }

  result = gate_mux8way16(a, b, c, d, e, f, g, h, 0b111);
  if (result != h) {
    return 0;
  }

  // Test with all inputs set to 0
  a = b = c = d = e = f = g = h = 0;
  for (int i = 0; i < 8; i++) {
    if (gate_mux8way16(a, b, c, d, e, f, g, h, i) != 0) {
      return 0;
    }
  }

  return 1;
}

int test_gate_demux4way() {
  int result;

  result = gate_demux4way(1, 0b00);
  if (result != 0b0001) {
    printf("a\n");
    return 0;
  }

  result = gate_demux4way(1, 0b01);
  if (result != 0b0010) {
    return 0;
  }

  result = gate_demux4way(1, 0b10);
  if (result != 0b0100) {
    return 0;
  }

  result = gate_demux4way(1, 0b11);
  if (result != 0b1000) {
    return 0;
  }

  return 1;
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
}

int main() {
  run_tests();
  return 0;
}