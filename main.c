#include <stdio.h>

int nand(int a, int b);
int not(int a);
int and (int a, int b);
int or (int a, int b);

int main(void)
{
    test();

    return 0;
}

int test(void)
{
    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 1; b++)
        {
            printf("------------------------------\n");
            printf("A = %d | B = %d \n", a, b);
            printf("NAND of %d and %d is %d\n", a, b, nand(a, b));
            printf("NOT of %d and is %d\n", a, not(a));
            printf("AND of %d and %d is %d\n", a, b, and(a, b));
            printf("OR of %d and %d is %d\n", a, b, or(a, b));
            printf("------------------------------\n");
        }
    }
}