#include <stdio.h>

int nand(int a, int b);
int not(int a);

int main(void)
{
    int a = 1, b = 1;
    int result = nand(a, b);

    printf("NAND of %d and %d is %d\n", a, b, result);
    printf("NOT of %d and is %d\n", a, not(a));

    return 0;
}