#include "../include/gates.h"
#include "../include/print_binary.h"
#include "../include/get_bit.h"
#include <stdio.h>

// TODO: replace int with this, char is 1 byte...
typedef signed char byte;

void test(void) {
  printf("------------------------------\n");
  printf("size of int %llubytes | %llubit\n", sizeof(int), sizeof(int) * 8);
  printf("------------------------------\n");
  for (int a = 0; a <= 1; a++) {
    for (int b = 0; b <= 1; b++) {
      printf("------------------------------\n");
      printf("A = %d | B = %d \n", a, b);
      printf("NAND of %d and %d is %d\n", a, b, gate_nand(a, b));
      printf("NOT of %d and is %d\n", a, gate_not(a));
      printf("AND of %d and %d is %d\n", a, b, gate_and(a, b));
      printf("OR of %d and %d is %d\n", a, b, gate_or(a, b));
      printf("XOR of %d and %d is %d\n", a, b, gate_xor(a, b));
      printf("------------------------------\n");
    }
  }

  printf("----------MUX TEST------------\n");
  for (int a = 0; a <= 1; a++) {
    for (int b = 0; b <= 1; b++) {
      for (int s = 0; s <= 1; s++) {
        printf("A = %d | B = %d | S = %d | MUX = %d\n", a, b, s,
               gate_mux(a, b, s));
      }
    }
  }
  printf("---------END MUX TEST---------\n");

  printf("---------DEMUX TEST-----------\n");
  for (int in = 0; in <= 1; in++) {
    for (int sel = 0; sel <= 1; sel++) {
      int demuxResult = gate_demux(in, sel);
      printf("sel = %d | in = %d | out1 = %d | out2 = %d\n", sel, in,
             demuxResult & 1, (demuxResult >> 1) & 1);
    }
  }
  printf("--------END DEMUX TEST--------\n");
  printf("---------NOT 16-----------\n");
  print_binary(gate_not16(700001), 16);
  printf("--------END DEMUX TEST--------\n");

  printf("---------GET BIT TEST-----------\n");
  int testNumber = 0b1001001101;
  print_binary(testNumber, 16);

  for (int i = 0; i < 16; i++) {
    printf("%d ", get_bit(testNumber, i));
  }
  printf("\n--------END DEMUX TEST--------\n");
}

int main(void) {
  test();
  printf("\n");
  getchar();
  return 0;
}
