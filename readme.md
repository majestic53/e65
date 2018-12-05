E65
===

A small 6502 emulator, written in C++

![Demo](https://github.com/majestic53/e65/blob/master/example/demo.png "Demo")

This emulator is designed to be used along-side the [A65 assembler](https://github.com/majestic53/a65)

Table of Contents
=================

1. [Build](https://github.com/majestic53/e65#build) -- How to build the project
2. [Usage](https://github.com/majestic53/e65#usage) -- How to use the project
3. [Changelog](https://github.com/majestic53/e65#changelog) -- Project changelist information
4. [License](https://github.com/majestic53/e65#license) -- Project license information

Build
=====

__NOTE__: Tested with the Clang C++ compiler. Modification to the makefiles might be required to build with a different compiler.

Run the following command from the projects root directory:

```
$ make release
```

To build with tracing enabled, run the following command from the project's root directory:

```
$ make TRACE=<LEVEL>
```

Where LEVEL corrisponds to the tracing verbosity (0=Error, 1=Warnings, 2=Information, 3=Verbose)

Usage
=====

Launch from the project root directory:

```
$ ./bin/e65 [ARGS]
```

### Interface

```
e65 [-d|-h|-i|-v] input

-d|--debug             Enter debug mode
-h|--help              Display help information
-i|--ihex              Load ihex file
-v|--version           Display version information
```

### Interface Examples

To load a binary (.bin) file into the emulator:

```
$ e65 <PATH_TO_BIN_FILE>

For example: e65 ./test/snake/snake.bin
```

To load an ihex (.hex) file into the emulator:

```
$ e65 -i <PATH_TO_HEX_FILE>

For example: e65 -i ./test/snake/snake.hex
```

To run the emulator in debug mode:

```
$ e65 -d <PATH_TO_FILE>

For example: e65 -d -i ./test/snake/snake.hex
```

### Debug Interface

These commands are available when running in debug mode:

```
bc|clear                              <address|*>             Clear breakpoint at a given address
bl|list                                                       List all breakpoints
bp|set                                <address>               Set breakpoint at a given address
---                                   ---                     ---
d|dump                                <address> <offset>      Dump memory at an address for a given offset
r|read                                <address>               Read byte from a given memory address
rw|read-word                          <address>               Read word from a given memory address
w|write                               <address> <value>       Write byte to a given memory address
ww|write-word                         <address> <value>       Write word to a given memory address
---                                   ---                     ---
a|accumulator                                                 Display processor accumulator
as|accumulator-set                    <value>                 Set processor accumulator to given value
b|break                                                       Break processor
c|core                                                        Display processor core
cy|cycle                                                      Display current processor cycle
dasm|disassemble                      <address> <offset>      Disassemble instructions at a given address
								and offset
flg|flags                                                     Display processor flags
flgs|flags-set                        <value>                 Set processor flags to given value
x|index-x                                                     Display processor index-x
xs|index-x-set                        <value>                 Set processor index-x to given value
y|index-y                                                     Display processor index-y
ys|index-y-set                        <value>                 Set processor index-y to given value
i|irq                                                         Signal processor with a maskable interrupt
n|nmi                                                         Signal processor with a non-maskable interrupt
pc|program-counter                                            Display processor program counter
pcs|program-counter-set               <value>                 Set processor program counter to given value
rst|reset                                                     Reset processor
g|run                                                         Run processor
sp|stack-pointer                                              Display processor stack pointer
sps|stack-pointer-set                 <value>                 Set processor stack pointer to given value
s|step                                <offset>                Step processor through a given number of steps
sf|step-frame                         <offset>                Step processor through a given number of frames
ss|stop                                                       Set processor stop flag
sc|stop-clear                                                 Clear processor stop flag
ws|wait                                                       Set processor wait flag
wc|wait-clear                                                 Clear processor wait flag
---                                   ---                     ---
f|frame                                                       Display current video frame
fc|frame-cycle                                                Display video frame cycle count
frq|frequency                                                 Display video frequency (Hz)
fs|fullscreen                         <value>                 Fullscreen display window
h|hide                                <value>                 Hide display window
p|pixel                               <x> <y>                 Retrieve display pixel at a given coordinate
ps|pixel-set                          <x> <y> <color>         Set display pixel at a given coordinate
---                                   ---                     ---
?|help                                                        Display help information
v|version                                                     Display version information
q|exit                                                        Exit debug mode
```

### Debug Interface Examples

To retrieve the processor registers:

```
$ c
```

To run the processor:

```
$ r
```

To break the processor:

```
$ b
```

To step the processor through a series of instructions/frames:

```
$ s <OFFSET>

For example: s 10 steps the processor through 10 instructions

$ sf <OFFSET>

For example: sf 10 steps the processor through 10 frames
```

To read/write data in memory:

```
$ r <ADDRESS>

For example: r fffa will read the byte held at 0xfffa

$ rw <ADDRESS>

For example: rw fffa will read the word held at 0xfffa

$ w <ADDRESS> <VALUE>

For example: w fffa aa will write the byte 0xaa to memory location 0xfffa

$ ww <ADDRESS> <VALUE>

For example: ww fffa aabb will write the word 0xaabb to memory location 0xfffa
```

To disassemble instructions in memory:

```
$ dasm <ADDRESS> <OFFSET>

For example: dasm 600 10 will disassemble 16 instructions held at memory location 0x0600
```

### Keyboard Shortcuts

These keyboard shortcuts are available in either normal, debug modes or both:

| Key | Description                         | Mode       |
| :-- | :---------------------------------- | :--------- |
| F11 | Fullscreen display                  | Both       |
| F5  | Refresh display                     | Both       |
| B   | Signal break                        | Debug only |
| G   | Signal run                          | Debug only |
| R   | Signal Reset (RST)                  | Both       |
| M   | Signal maskable Interrupt (IRQ)     | Both       |
| N   | Signal non-maskable Interrupt (NMI) | Both       |

Changelog
=========

Version 0.1.1849
----------------
*Updated: 11/04/2018*

* Added processor interface test fixture

*Updated: 11/03/2018*

* Added test suite files

Version 0.1.1848
----------------
*Updated: 11/02/2018*

* Implemented adc/sbc instructions
	* Todo: Add support for decimal mode
* Added additional keyboard shortcuts
* Bug fixes

*Updated: 11/29/2018-12/01/2018*

* Additional bug fixes

*Updated: 11/28/2018*

* Added additional video debug commands
* Minor bug fixes
	* Cycle count is now based on display mode

*Updated: 11/27/2018*

* Moved runtime into main thread to avoid renderer issues
* Minor reorg of the interface

*Updated: 11/26/2018*

* Implemented jump instructions

*Changelog truncated (see file history for full log)*

License
=======

Copyright(C) 2018 David Jolly <majestic53@gmail.com>

E65 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

E65 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
