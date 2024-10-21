#ifndef DEMUX_H
#define DEMUX_H

typedef struct
{
    int out1;
    int out2;
} DemuxResult;
// structs live on the stack, array would need to be static and freed

DemuxResult demux(int in, int sel);

#endif
