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
