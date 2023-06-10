ms8x32

256-bit integers, implemented as eight 32-bit words. Currently done for
fun, but possibly in the future it will allow me to experiment with ECC.
At the moment the code is NOT cryptographically secure though i would
love this project to reach that state some day. Currently i plan on
implementing most of basic arithmetic and bitwise operations on the
numbers, as well as conversion to and from numeric strings. Afterwards i
would like to implement modular arithmetic.

The code has been tested under x86-64 linux environment only, though i
try not to use any architecture-specific features so that it could be
used on other 32-bit-capable architectures as well.

To build run make, to remove build files run make clear. To build tests
(not built by default) run make test. The tests may be ran with the
./runtests.sh script (the script runs make test every time just in
case).

The library does not use anything besides standard C headers and
requires no external libs. The build process uses standard Make and some
basic shell utilities (namely dirname command). Running tests requires
only a regular shell, possibly with color support for better
readability, though it should work even in absence of it.

After building, library can be found in build/lib/libms8x32.so. The
library api is in include/ms8x32/ms8x32.h and other header files in the
same directory.
