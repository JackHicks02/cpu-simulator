#include "nand.h"

int not(int a)
{
    return (nand(a, a) & 1);
}