Implementation in C of the SLATEC mathematical library.

## WHAT IS SLATEC ##
SLATEC is a comprehensive and reliable numerical library developed
in Fortran, available on Netlib at <http://www.netlib.org/slatec/>. It
includes special functions such as the 3J and 6J Wigner Symbols,
the Bessel functions, the Airy function, the Gamma function, and many more.

SLATEC was made to the highest standards by the US military
in the 70s (<http://en.wikipedia.org/wiki/SLATEC>). It is now used
by countless scientists worldwide for more peaceful purposes.

## DESCRIPTION ##
As earlier versions of the Fortran programming language are becoming
less and less popular even in the scientific world, I decided to convert
SLATEC to C.

So far I have implemented only a subset of the SLATEC library, sufficient 
to compute Wigner 3J Symbols (also called Clebsch-Gordan coefficients),
Wigner 6J Symbols (also called Racah's W-coefficients) and both 
spherical and regular Bessel functions.

In this project I provide two separate files that you might
find useful:

* `slatec_3j_C.c`, a direct translation of the SLATEC library into C.
* `slatec_c_interface.c`, a C-Fortran interface containing wrapper functions
  that allow the use of SLATEC functions directly in C;

The 'test' folder contains executable code to test both files. Based on my
personal tests, both the execution speed and the numerical precision
in C are the same as in Fortran, provided that you use equivalent optimization
flags in the two languages.

## INSTALLATION ##
The main code amounts to two files, `slatec_c_interface.c` and `slatec_3j_C.c`.
Their compilation is straightforward; for an example, please refer to the
`makefile` in the test folder.

## CONTRIBUTE! ##
Please feel free to contribute to the project via Github:  
<https://github.com/coccoinomane/slatec>  
It would be great to implement more SLATEC functions, either
in the interface or in the translation file. The process should
be straightforward if you use as templates the functions that
are already implemented.

## CREDITS ##
I wish to thank John Burkardt for writing the Fortran 90 version of 
the SLATEC library, which I include in this project, and in general
for his great website of numerical functions:
<http://people.sc.fsu.edu/~jburkardt/>

