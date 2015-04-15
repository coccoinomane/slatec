/*
 *  Test the SLATEC function 'DRC3JJ'.
 *  Given the arguments L2, L3, M2, M3, print to
 *  screen the value of the 3j symbol:
 *
 *          (    L1    L2    L3  )
 *          ( -M2-M3   M2    M3  )
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"


// 3j function from the Slatec library
void drc3jj_ (double *l2, double *l3,
              double *m2, double *m3, double *l1_min, double *l1_max,
              double *thrcof, int *ndim, int *ier);

// 3j function from the C Slatec library
int drc3jj (double l2, double l3,
            double m2, double m3, double *l1_min, double *l1_max,
            double  *thrcof, int ndim, int *ier);              

int main (int argc, char const *argv[]) {

  if (argc!=6) {
    printf("usage:    %s <l1> <l2> <l3> <m1> <m2>\n", argv[0]);
    return 1;
  }
  int l1 = atoi(argv[1]);
  double l2 = atof(argv[2]);
  double l3 = atof(argv[3]);
  double m1 = atof(argv[4]);
  double m2 = atof(argv[5]);  
  double m3 = -m1-m2;

  // ==================
  // = Compute the 3j =
  // ==================
  /*   Prototype of the Fortran function:
      subroutine DRC3JJ (L2, L3, M2, M3, L1MIN, L1MAX, THRCOF, NDIM, &
           IER)
     INTEGER NDIM, IER
     DOUBLE PRECISION L2, L3, M3, M3, L1MIN, L2MAX, THRCOF(NDIM)  */
           
  
  // The Slatec function DRC3JJ computes the 3j symbol for any allowed value
  // of l1.  Here we compute the number of such values and allocate memory
  // for the result array.
  double l1_min = abs(l2-l3);
  double l1_max = l2+l3;
  int out_size = (int)(l1_max-l1_min+1.);
  double *result = (double*)calloc(out_size,sizeof(double));

  // Status flag for DRC3JM
  int ier=0;

  // Do the actual computation
  drc3jj_ (&l2, &l3,
           &m2, &m3, &l1_min, &l1_max,
           result, &out_size, &ier);

	// Note that this function will compute all the 3j's for the allowed values of l1
	// given the input parameters.  If we ask for a l1 which is not in the range, then
	// we will get a unmeaningful result or a segmentation fault
  // if (l1>l1_max || l1<l1_min) {
  //   printf("INPUT ERROR: 'l1' should be between %g and %g.\n", l1_min, l1_max);
  //   return 1;
  // }
  
  // Print the error code
  printf("FORTRAN RESULT:\n");
  printf("ier = %d\n", ier);

  // Find the index corresponding to the requested m2
  int l1_index = l1 - (int)l1_min;
  
  // Print the result
  printf("3J(%d,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,m1,m2,m3,result[l1_index]);
  
  // ===========================
  // = Use C version of Slatec =
  // ===========================
  
  double * result_C = (double*)calloc(out_size,sizeof(double));
  
  int status = drc3jj (l2, l3,
                       m2, m3, &l1_min, &l1_max,
                       result_C, out_size, &ier);
  
  // Print the error code and status
  printf("C RESULT:\n");
  printf("ier = %d\n", ier);
  printf("status = %d\n", status);
  
  // Print the C result
  printf("3J(%d,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,m1,m2,m3,result_C[l1_index]);

  

  return 0;
  
}