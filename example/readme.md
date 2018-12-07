E65 Examples
============

This folder contains a series of binaries/sources that have been tested with E65

![Demo](https://github.com/majestic53/e65/blob/master/example/demo.png "Demo")

Usage
=====

All the examples have been pre-compiled as binaries and ihex files. To run the examples, first compile E65 and launch it with the following command:

### Launch Binary

To load a binary (.bin) file into the emulator:

```
$ e65 <PATH_TO_BIN_FILE>

For example: e65 ./test/snake/snake.bin
```

### Launch iHex

To load an ihex (.hex) file into the emulator:

```
$ e65 -i <PATH_TO_HEX_FILE>

For example: e65 -i ./test/snake/snake.hex
```

### Launch Debug Mode

To run the emulator in debug mode:

```
$ e65 -d <PATH_TO_FILE>

For example: e65 -d -i ./test/snake/snake.hex
