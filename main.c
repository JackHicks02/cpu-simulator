#include <stdio.h>

int nand(int a, int b);
int not(int a);
int and (int a, int b);

int main(void)
{
    int a = 1, b = 1;

    printf("NAND of %d and %d is %d\n", a, b, nand(a, b));
    printf("NOT of %d and is %d\n", a, not(a));
    printf("AND of %d and %d is %d\n", a, b, and(a, b));

    return 0;
}