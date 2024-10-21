#include "or.h"
#include "and.h"
#include "not.h"

int mux(int a, int b, int sel)
{
    return (or (and(a, not(sel)), and(b, sel)));
}