#include "nand.h"

int xor (int a, int b) {
    return(nand(nand(a,nand(a,b)),nand(b,nand(a,b))));
}