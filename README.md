Implementation in C of the SLATEC mathematical library.

SLATEC is a comprehensive and reliable numerical library developed
in Fortran, available on Netlib at http://www.netlib.org/slatec/.

SLATEC was made to the highest standards by the US military
in the 70s (http://en.wikipedia.org/wiki/SLATEC). It is now used
by countless scientists worldwide for more peaceful purposes.

As earlier versions of the Fortran programming language are becoming
less and less popular even in the scientific world, I decided to convert
SLATEC to C. In this project I provide two separate files that you might
find useful:
* slatec_c_interface.c, an C-Fortran interface containing wrapper functions
that allow the use of SLATEC functions directly in C;
* slatec_3j_C.c, a direct translation of the SLATEC library into C.
Furthermore, the 'test' folder contains executable code to test both
files.

I have implemented only a subset of the SLATEC library, sufficient 
to compute Wigner 3J Symbols (also called Clebsch-Gordan coefficients),
Wigner 6J Symbols (also called Racah's W-coefficients) and both 
spherical and regular Bessel functions.

I kindly welcome contributors to implement further SLATEC functions
either in the interface or in the translation file. The process should
be straightforward if you use the functions that are already implemented
as templates.

*** CREDITS ***
I wish to thank John Burkardt for writing the Fortran 90 version of 
the SLATEC library, which I include in this project, and in general
for his great website of numerical functions:
http://people.sc.fsu.edu/~jburkardt/

