/*
 *  Test the C wrapper 'three_j_l1' of the SLATEC function 'DRC3JJ'.
 *  Given the arguments L2, L3, M2, M3, print to
 *  screen the value of the 3j symbol:
 *
 *          (    L1    L2    L3  )
 *          ( -M2-M3   M2    M3  )
 */



#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "slatec_c_interface.h"


int main (int argc, char const *argv[]) {

  if (argc!=6) {
    printf("usage:    %s <l1> <l2> <l3> <m1> <m2>\n", argv[0]);
    return 1;
  }
  int l1 = atoi(argv[1]);
  int l2 = atof(argv[2]);
  int l3 = atof(argv[3]);
  int m1 = atof(argv[4]);
  int m2 = atof(argv[5]);  
  int m3 = -m1-m2;

  
  // ===================
  // = Compute the 3j  =
  // ===================
  /* Prototype of the C wrapper function:

  int threej_l1(
         int l2, int l3, int m2, int m3,    // In
         int *l1_min, int *l1_max,          // Out, 'm2' limits for which result was computed
         double **result,                   // Out
         int *result_size                   // Out
         );

  */
  
  // The function computes the 3j symbol for any allowed value of l1.  Here we compute the number
  // of such values and allocate memory.
  int l1_min = abs(l2-l3);
  int l1_max = l2+l3;
  int out_size = (int)(l1_max-l1_min+1.);
  double *result = (double*)calloc(out_size,sizeof(double));

  // Compute the 3j
  threej_l1 (l2, l3,
             m2, m3,
             &l1_min,
             &l1_max,
             &result,
             &out_size
             );


	// Note that this function will compute all the 3j's for the allowed values of l1
	// given the input parameters.  If we ask for a l1 which is not in the range, then
	// we will get a unmeaningful result or a segmentation fault
	if (l1>l1_max || l1<l1_min) {
		printf("INPUT ERROR: 'l1' should be between %g and %g.\n", l1_min, l1_max);
		return 1;
	}

  // Find the index corresponding to the requested m2
  int l1_index = l1 - (int)l1_min;
  
  // Print the result
  printf("3J(%d,%d,%d)(%d,%d,%d) = %g\n", l1,l2,l3,m1,m2,m3,result[l1_index]);
  

  return 0;
  
}














