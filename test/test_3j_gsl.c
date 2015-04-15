/*
 *  Test the GSL function 'gsl_sf_coupling_3j'.  Note that since version 1.15 of GSL,
 *  this function was updated to handle a larger range.
 */

#include "stdio.h"
#include "gsl/gsl_sf_coupling.h"
#include "gsl/gsl_errno.h"

int main (int argc, char const *argv[]) {

  if (argc!=7) {
    printf("usage:    %s <l1> <l2> <l3> <m1> <m2> <m3>\n", argv[0]);
    return 1;
  }
  int l1 = atoi(argv[1]);
  int l2 = atoi(argv[2]);
  int l3 = atoi(argv[3]);
  int m1 = atoi(argv[4]);
  int m2 = atoi(argv[5]);
  int m3 = atoi(argv[6]);

  // Compute the 3j
  gsl_sf_result gsl_result;
  int status = gsl_sf_coupling_3j_e(2*l1, 2*l2, 2*l3, 2*m1, 2*m2, 2*m3, &gsl_result);
  
  // Print the result
  printf("3J(%d,%d,%d)(%d,%d,%d) = %g\n", l1,l2,l3,m1,m2,m3,gsl_result.val);
  
  // Print the error message if present
  printf("       status = %d\n", status);
  printf("       %s\n", gsl_strerror(status));


  return 0;
  
}