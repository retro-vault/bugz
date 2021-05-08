/*
 * main.c
 *
 * BUGZ main entry point and entire dissasembly logic.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2016 tomaz stih
 *
 * 04.11.2016   tstih
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "inst_set.h"

uint8_t * read_file(char *fname, long *fsize) {
    FILE *f = fopen(fname, "rb");
    fseek(f, 0, SEEK_END);
    *fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
    uint8_t *bytes = malloc(*fsize + 1);
    fread(bytes, *fsize, 1, f);
    fclose(f);
    return bytes;
}

int compare_instruction(const void *opcode, const void *instruction) {
    uint8_t length=((instruction_t*)instruction)->size, *b1=(uint8_t*)opcode, *b2=(uint8_t*)instruction, *msk=(uint8_t*)(&(((instruction_t*)instruction)->omask));
    while (length--) {
            if ((*msk) == 0x01) { /* Opcode */
                if (*b1-*b2) return *b1-*b2;
            } else if ((*msk)!=4) { /* New operand. */
                if (o1==NULL) { om1=0x00ff; o1=b1; } else { om2=0x00ff; o2=b1; }
            } else
                om1=0xffff;
            b1++; b2++; msk++;
    }
    return 0; /* The same */
}

char* dissasemble(uint8_t* memory, uint16_t addr, uint16_t size, char* buffer) {

    while (addr < size) { /* Take a hike. */

        /* Fetch */
        o1 = o2 = NULL; inst = 0;
        memcpy(&inst,&(memory[addr]),size-addr>=4?4:size-addr+1);

        /* Decode. Will set o1 and o2 to point into inst. */
        instruction_t * instruction=bsearch((void *)&inst, (void *)instruction_set, 698, sizeof(instruction_t), compare_instruction);

        /* Print. */
        sprintf(buffer + strlen(buffer), "%04X\t", addr); /* Addr. */
        if (instruction!=NULL) {
                if (o2)
                    sprintf(buffer + strlen(buffer), instruction->mnemonic,*((uint16_t*)o1)&om1, *((uint16_t*)o2)&om2);
                else if (o1)
                    sprintf(buffer + strlen(buffer), instruction->mnemonic,*((uint16_t*)o1)&om1);
                else
                    sprintf(buffer + strlen(buffer), "%s", instruction->mnemonic);
                sprintf(buffer + strlen(buffer), "\n"); /* Separator. */
                addr+=instruction->size;
        } else
            addr++; /* Not recognized. Just skip. */
    }

    return buffer;
}

#define KILOBYTE 1024

int main(int argc, char* argv[])
{
    if (argc!=2) {
        printf("Please provide filename as first (and only) argument.\r\n");
        exit(1);
    }

    long fsize;
    uint8_t * rom=read_file(argv[1], &fsize);
    char buffer[KILOBYTE * KILOBYTE]; /* ought to do it */

    puts(dissasemble(rom, 0, fsize, buffer));

    free(rom); /* Release memory before closing. */
    return 0;
}