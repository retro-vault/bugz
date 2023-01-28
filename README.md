![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url] [![license.badge]][license.url]

# bugz

BUGZ is the worlds' smallest Z80 disassembler. It is written in C89 and 
should compile on just about any machine with a standard library. 

 > One required function that might be missing in older implementations 
 > is the `bsearch`. The GeeksForGeeks site provides the 
 > [default implementation](https://www.geeksforgeeks.org/binary-search/).  

## How does it work?

BUGZ is a table disassembler. Each instruction in the instruction table
has a name (a string, with `printf` compatible arguments for operands), 
a 32 bit "opcode" (the longest instruction in Z80 is exactly 4 bytes), 
and a 32 bit mask to tell which part of the "opcode" is instruction,
which the operand(s), and which can be ignored. 

Opcode mask byte values can be:

| mask byte |  meaning                            |
|-----------|-------------------------------------|
| 00        | Ignore this byte                    |
| 01        | Opcode (you have o match this part) |
| 02        | 8 bit operand                       |
| 03        | Low byte of 16 bit operand          |
| 04        | High byte of 16 bit operand         |
| 05        | 8 bit jump operand (JR, DJNZ)       |
| 06        | Index register offset operand (+/-) |

### How to interpret the instruction table entry?

An instruction `DJNZ %hhd` will have opcode of `0x00000010`, and
a mask of `0x00000501`. First byte of the mask is `0x01` which means
that first byte in memory must equal to first byte of the opcode 
(i.e must be `0x10`). Second byte of the mask is `0x05` which means 
second byte in memory is an 8 bit jump offset value. Other bytes in 
mask are `0x00` and are ignored. Hence if you are examining a memory
address and the first byte is `0x10` then take the second byte as
a signed byte and use it as argument to `printf`, together with the
 `DJNZ %hhd` instruction format string. 

 > For convenience, every instruction in the instruction table
 > also contains instruction size (i.e. how many bytes are valid).

## How to compile it?

Make sure you have `make` and `gcc` tools installed. Open the terminal,
go to the `bugz` directory, and type -

`make`

The `main.c` file contains a `main()` function that accepts one argument -
the name of the binary file. It reads it and dump its disassembled code 
on the standard output.

The `48.rom` file is a sample Z80 binary (ZX Spectrum 48K ROM image). 
After building BUGZ run it like this -  

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

[status.badge]:  https://img.shields.io/badge/status-stable-dkgreen.svg
