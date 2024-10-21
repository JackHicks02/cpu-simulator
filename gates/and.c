#include "not.h"
#include "nand.h"

int and (int a, int b)
{
    return not(nand(a, b));
}