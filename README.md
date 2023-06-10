# ms8x32 - 256 bit unsigned integers
This is an implementation of 256-bit unsigned integers using eight 32-bit words. Currently done for fun, but possibly in the future it will allow Me to experiment with Elliptic Curve Cryptography, namely cryptosystems based on Curve25519. At the moment the code is NOT cryptographically secure though I would love this project to reach that state some day. Currently I plan on implementing most of basic arithmetic and bitwise operations on the numbers, as well as conversion to and from numeric strings. Afterwards I would like to implement modular arithmetic.

### Compatiblity
The code has been tested under x86-64 linux environment only, though I try not to use any architecture-specific features so it should be possible to use it in other 32-bit-capable systems as well.

### Building
To build run `make`, to remove build files run `make clear`. To build tests (not built by default) run `make test`. The tests may be ran with the `./runtests.sh` script.

### Requirements
The library does not use anything besides standard C headers and requires no external libs. The build process uses standard Make and some basic shell utilities (namely the `dirname` command). Running tests requires only a regular shell, possibly with color support for better readability, though it should work even in absence of it.

After building, library can be found in `build/lib/libms8x32.so`. The library api is in `include/ms8x32/ms8x32.h` and other header files in the same directory.
