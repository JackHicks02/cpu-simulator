#include <stdio.h>
#include "or.h"
#include "and.h"

typedef struct
{
    int out1;
    int out2;
} DemuxResult;

DemuxResult demux(int in, int sel)
{
    DemuxResult result = {
        out1: and(in, sel),
        out2: or(in, sel)
    };
    return result;
}