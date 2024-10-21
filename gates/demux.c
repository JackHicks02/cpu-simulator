#include <stdio.h>
#include "not.h"
#include "or.h"
#include "and.h"
#include "demux.h"


DemuxResult demux(int in, int sel)
{
    DemuxResult result = {
        out1: and(in, not(sel)),
        out2: and(in, sel)
    };
    return result;
}