![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url] [![license.badge]][license.url]

# bugz

BUGZ is the worlds' smallest Z80 disassembler. It is written in C89 and 
should compile on just about any machine with a standard library. 

 > One required function that might be missiong in older implementations 
 > in the `bsearch`. Luckily the GeeksForGeeks site provides the 
 > [default implementation](https://www.geeksforgeeks.org/binary-search/).  

## How does it work?

BUGZ is a table disassembler. It uses a long integer opcode (the longest 
instruction in Z80 is exactly 4 bytes), and a long integer mask to tell 
which part of the opcode is instruction and which the operand(s). 

Mask values are

| mask byte |  meaning                            |
|-----------|-------------------------------------|
| 00        | Ignore this byte                    |
| 01        | Opcode (you have o match this part) |
| 02        | 8 bit operand                       |
| 03        | Low byte of 16 bit operand          |
| 04        | High byte of 16 bit operand         |
| 05        | 8 bit jump operand (JR, DJNZ)       |
| 06        | Index register offset operand (+/-) |

This is how you interpret the values:

an instruction `DJNZ %hhd` will have opcode of `0x00000010`, and
a mask of `0x00000501`. First byte of the mask is `0x01` which means
that first byte in the memory must equal to first byte of the opcode 
(i.e must be `0x10`). Second byte of the mask is `0x05` which means 
second byte of in the memory is an offset value. Other bytes in 
mask are `0x00` and are ignored. Hence if you are examining a memory
address and the first byte is `0x10` then take the second byte as
a signed byte and `printf` it into the `DJNZ %hhd`. 

 > For convenience, every instruction in the instruction set (table)
 > also contains instruction size (i.e. how many bytes are valid).

## How to compile it?

Make sure you have `make` and `gcc` tools installed. Go to the directory
in your terminal and type

`make`

The `main.c` file contains a `main()` function that accepts one argument -
the name of the binary file, reads it and dump its disassembled code on the
stdandard output.

The `48.rom` file is a sample Z80 binary (ZX Spectrum 48K ROM image). 

After building BUGZ run it like this. 

`./bugz 48.rom`

## Extras

The instruction table also contains t-states for each instruction. This 
data is currently not used (I wanted to keep the source code small and 
simple!), but the disassembler can easily be extended to include this 
information into the final listing.

[language.url]:   https://en.wikipedia.org/wiki/ANSI_C
[language.badge]: https://img.shields.io/badge/language-C-blue.svg

[standard.url]:   https://en.wikipedia.org/wiki/C89/
[standard.badge]: https://img.shields.io/badge/standard-C89-blue.svg

[license.url]:    https://github.com/tstih/nice/blob/master/LICENSE
[license.badge]:  https://img.shields.io/badge/license-MIT-blue.svg

[status.badge]:  https://img.shields.io/badge/status-stable-darkgreen.svg