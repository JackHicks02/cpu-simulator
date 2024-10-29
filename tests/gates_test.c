#include "../include/gates.h"
#include <stdio.h>

int test_gate_nand() {
  return gate_nand(1, 1) == 0 && gate_nand(1, 0) == 1 && gate_nand(0, 1) == 1 &&
         gate_nand(0, 0) == 1;
}

void run_tests() {
  printf("Testing gate functions...\n");

  printf("test_gate_nand: %s\n", test_gate_nand() ? "PASS" : "FAIL");
}

int main() {
  run_tests();
  return 0;
}