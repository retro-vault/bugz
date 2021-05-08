/*
 * inst_set.h
 *
 * Instruction set (table) declaration.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2016 tomaz stih
 *
 * 04.11.2016   tstih
 *
 */
#ifndef _INST_SET_H
#define _INST_SET_H

#include <stdint.h>

typedef struct instruction_s {
    uint32_t opcodes;
    uint32_t omask;
    char mnemonic[20];
    uint8_t size;
    uint8_t tstates;
    uint8_t tstates_fail;
} instruction_t;

extern instruction_t instruction_set[];
extern uint32_t inst;
extern uint8_t *o1, *o2;
extern uint16_t om1,om2;

#endif /* _INST_SET_H */