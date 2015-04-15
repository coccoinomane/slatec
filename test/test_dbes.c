/*
 *  Test the SLATEC function 'DBESJ'.
 *  Given the arguments x >= 0.0D0, l >= 0.0D0, print to
 *  screen the value of the spherical Bessel function
 *
 *        j_l ( x )
 *
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define sqrt_pi_over_2 1.25331413731550025120788264241

// 3j function from the Slatec library
void dbesj_ (double *x, double *l, int *N, double *result, int *NZ);


int main (int argc, char const *argv[]) {

  if (argc!=3) {
    printf("usage:    %s <l> <x>\n", argv[0]);
    return 1;
  }
  double l  = atof(argv[1]);
  double x  = atof(argv[2]);

  // ================================
  // = Compute the spherical Bessel =
  // ================================
  /*   Prototype of the Fortran function:
    subroutine DBESJ (X, ALPHA, N, Y, NZ)           */
  
  /*   The Slatec function DBESJ computes the Bessel j_l(x) for the l-values going
     from ALPHA to ALPHA + N -1.  We hand pick N=1, hence the result does not need
     to be an array.  The last argument, NZ, is non-important.  */
  int N = 1, dump;
  double result;

  // Do the actual computation
  l = l + 0.5;   // We are interested in the spherical Bessel functions
  dbesj_ (&x, &l, &N, &result, &dump);
  
  // Compute the spherical Bessel function
  result *= sqrt_pi_over_2/sqrt(x);

  // Print the result
  printf("j(%.4g,%.4g) = %.15g\n", l, x, result);
  
  return 0;
  
}