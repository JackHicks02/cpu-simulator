#include <stdio.h>
#include "./gates/gates.h"
#include "./utils/get_bit.h"
#include "./utils/print_binary.h"

// TODO: replace int with this, char is 1 byte...
typedef signed char byte;

void test(void)
{
    printf("------------------------------\n");
    printf("size of int %ldbytes | %ldbit\n", sizeof(int), sizeof(int) * 8);
    printf("------------------------------\n");
    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 1; b++)
        {
            printf("------------------------------\n");
            printf("A = %d | B = %d \n", a, b);
            printf("NAND of %d and %d is %d\n", a, b, nand(a, b));
            printf("NOT of %d and is %d\n", a, not(a));
            printf("AND of %d and %d is %d\n", a, b, and(a, b));
            printf("OR of %d and %d is %d\n", a, b, or (a, b));
            printf("XOR of %d and %d is %d\n", a, b, xor(a, b));
            printf("------------------------------\n");
        }
    }

    printf("----------MUX TEST------------\n");
    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 1; b++)
        {
            for (int s = 0; s <= 1; s++)
            {
                printf("A = %d | B = %d | S = %d | MUX = %d\n", a, b, s, mux(a, b, s));
            }
        }
    }
    printf("---------END MUX TEST---------\n");

    printf("---------DEMUX TEST-----------\n");
    for (int in = 0; in <= 1; in++)
    {
        for (int sel = 0; sel <= 1; sel++)
        {
            int demuxResult = demux(in, sel);
            printf("sel = %d | in = %d | out1 = %d | out2 = %d\n", sel, in, demuxResult & 1, (demuxResult >> 1) & 1);
        }
    }
    printf("--------END DEMUX TEST--------\n");
    printf("---------NOT 16-----------\n");
    print_binary(not16(0b110101), 16);
    printf("--------END DEMUX TEST--------\n");
}

int main(void)
{
    test();
    return 0;
}
