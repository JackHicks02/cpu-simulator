#include "./get_bit.h"
#include <stdio.h>

void print_binary(int number, int bit) {
  char out[bit + 1];

  for (int i = 0; i < bit; i++) {
    out[bit - i - 1] = get_bit(number, i) ? '1' : '0';
  }
  out[bit] = '\0';

  printf("%s\n", out);
}
