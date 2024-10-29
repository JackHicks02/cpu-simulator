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

#endif
