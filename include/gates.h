#ifndef GATES_H
#define GATES_H

// some of the gates are c++ keywords and it makes it look disgusting :(
int gate_nand(int a, int b);

int gate_not(int a);

int gate_and(int a, int b);

int gate_or(int a, int b);

int gate_demux(int in, int sel);

int gate_mux(int a, int b, int sel);

int gate_xor(int in, int sel);

int gate_not16(int in);

int gate_or16(int a, int b);

int gate_and16(int a, int b);

int gate_mux16(int a, int b, int sel);

int gate_or8way(int a);

int gate_mux4way16(int a, int b, int c, int d, int s);

int gate_mux8way16(int a, int b, int c, int d, int e, int f, int g, int h,
                   int s);

int gate_demux4way(int in, int sel);

#endif
