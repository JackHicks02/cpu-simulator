#include <stdio.h>
#include "not.h"
#include "or.h"
#include "and.h"
#include "demux.h"

int demux(int in, int sel)
{
    // DemuxResult result = {
    //     out1: and(in, not(sel)),
    //     out2: and(in, sel)
    // };

    int out1 = and(in, not(sel));
    int out2 = and(in, sel);
    return (out1 + (out2 << 1));
}