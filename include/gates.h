#include <stdint.h> // For uint8_t and uint16_t
#ifndef GATES_H
#define GATES_H

typedef uint8_t u8;
typedef uint16_t u16;

// Single-bit gates
void gate_nand(u8 *a, u8 *b, u8 *out);
void gate_not(u8 *a, u8 *out);
void gate_and(u8 *a, u8 *b, u8 *out);
void gate_or(u8 *a, u8 *b, u8 *out);
void gate_xor(u8 *a, u8 *b, u8 *out);

// Single-bit multiplexer and demultiplexer
void gate_mux(u8 *a, u8 *b, u8 *sel, u8 *out);
void gate_demux(u8 *in, u8 *sel, u8 *out0, u8 *out1);

// 16-bit gates
void gate_not16(u16 *in, u16 *out);
void gate_or16(u16 *a, u16 *b, u16 *out);
void gate_and16(u16 *a, u16 *b, u16 *out);
void gate_mux16(u16 *a, u16 *b, u8 *sel, u16 *out);

// 8-way OR gate for 8-bit input
void gate_or8way(u8 *in, u8 *out);

// 4-way and 8-way multiplexers for 16-bit inputs
void gate_mux4way16(u16 *a, u16 *b, u16 *c, u16 *d, u8 *sel, u16 *out);
void gate_mux8way16(u16 *a, u16 *b, u16 *c, u16 *d, u16 *e, u16 *f, u16 *g,
                    u16 *h, u8 *sel, u16 *out);

// 4-way and 8-way demultiplexers for single-bit inputs
void gate_demux4way(u8 *in, u8 *sel, u8 *out0, u8 *out1, u8 *out2, u8 *out3);
void gate_demux8way(u8 *in, u8 *sel, u8 *out0, u8 *out1, u8 *out2, u8 *out3,
                    u8 *out4, u8 *out5, u8 *out6, u8 *out7);

#endif