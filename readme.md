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
bc|breakpoint-clear                   <address|*>             Clear breakpoint at a given address
bl|breakpoint-list                                            List all breakpoints
bs|breakpoint-set                     <address>               Set breakpoint at a given address
---                                   ---                     ---
md|memory-dump                        <address> <offset>      Dump memory at an address for a given offset
mr|memory-read                        <address>               Read byte from a given memory address
mrw|memory-read-word                  <address>               Read word from a given memory address
mw|memory-write                       <address> <byte>        Write byte to a given memory address
mww|memory-write-word                 <address> <word>        Write word to a given memory address
---                                   ---                     ---
pa|processor-accumulator                                      Display processor accumulator
pas|processor-accumulator-set         <byte>                  Set processor accumulator to given value
pc|processor-core                                             Display processor core
pcy|processor-cycle                                           Display current processor cycle
pf|processor-flags                                            Display processor flags
pfs|processor-flags-set               <byte>                  Set processor flags to given value
px|processor-index-x                                          Display processor index-x
pxs|processor-index-x-set             <byte>                  Set processor index-x to given value
py|processor-index-y                                          Display processor index-y
pys|processor-index-y-set             <byte>                  Set processor index-y to given value
pi|processor-irq                                              Signal processor with a maskable interrupt
pn|processor-nmi                                              Signal processor with a non-maskable interrupt
ppc|processor-program-counter                                 Display processor program counter
ppcs|processor-program-counter-set    <word>                  Set processor program counter to given value
pr|processor-reset                                            Reset processor
psp|processor-stack-pointer                                   Display processor stack pointer
psps|processor-stack-pointer-set      <byte>                  Set processor stack pointer to given value
ps|processor-step                                             Step processor through a single cycle
pss|processor-stop                                            Set processor stop flag
psc|processor-stop-clear                                      Clear processor stop flag
pws|processor-wait                                            Set processor wait flag
pwc|processor-wait-clear                                      Clear processor wait flag
---                                   ---                     ---
vf|video-frame                                                Display current video frame
vfs|video-fullscreen                  <bool>                  Fullscreen display window
vh|video-hide                         <bool>                  Hide display window
---                                   ---                     ---
q|exit                                                        Exit debug mode
h|help                                                        Display help information
v|version                                                     Display version information
```

Changelog
=========

Version 0.1.1847
----------------
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
