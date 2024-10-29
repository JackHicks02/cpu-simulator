#ifndef GATES_H
#define GATES_H

// some of the gates are c++ keywords and it makes it look disgusting :(
int nand(int a, int b);

int not(int a);

int and(int a, int b);

int or(int a, int b);

int demux(int in, int sel);

int mux(int a, int b, int s);

int xor(int in, int sel);

int not16(int in);

#endif
