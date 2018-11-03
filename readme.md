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
TBD
```

Changelog
=========

Version 0.1.1843
----------------
*Updated: 11/3/2018*

* Added bus singleton
* Integrated bus into runtime

*Updated: 11/2/2018*

* Added display singleton
* Integrated display into runtime

*Updated: 11/1/2018*

* Implemented runtime main loop
* Integrated SDL into runtime

*Updated: 10/31/2018*

* Added trace singleton

*Updated: 10/28/2018*

* Added signal/thread types

*Updated: 10/27/2018*

* Initial commit

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
