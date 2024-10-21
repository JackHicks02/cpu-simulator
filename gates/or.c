#include "nand.h"
#include "not.h"

int or (int a, int b)
{
    //not(not(a) and not(b))
    return nand(not(a), not(b));
}