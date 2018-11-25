E65
===

A small 6502 emulator, written in C++

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
make release
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
./bin/e65 [ARGS]
```

### Interface

```
e65 [-d|-h|-i|-v] input

-d|--debug             Enter debug mode
-h|--help              Display help information
-i|--ihex              Load ihex file
-v|--version           Display version information
```

### Debug Interface

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
dasm|disassemble                      <address> <offset>      Disassemble instructions at an address for a
								given offset
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
fs|fullscreen                         <value>                 Fullscreen display window
h|hide                                <value>                 Hide display window
---                                   ---                     ---
?|help                                                        Display help information
v|version                                                     Display version information
q|exit                                                        Exit debug mode
```

Changelog
=========

Version 0.1.1847
----------------
*Updated: 11/24/2018*

* Implemented additional processor instructions
	* Todo: branch & jump instructions

*Updated: 11/23/2108*

* Added run/break debug commands
* Added async event handlers
* Cleaned up debug interface

*Updated: 11/22/2018*

* Added additional debug commands

*Updated: 11/21/2018*

* Added arithmetic commands
* Minor code reorg

*Updated: 11/20/2018*

* Added processor implied commands

*Updated: 11/19/2018*

* Added processor commands

Version 0.1.1846
----------------
*Updated: 11/17/2018*

* Added processor core command
* Implemented processor interrupt handler
* Documented e65 public header file

*Updated: 11/13/2018*

* Added processor interrupt handler
* Added processor reset debug command

*Updated: 11/12/2018*

* Added additional debug commands

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
