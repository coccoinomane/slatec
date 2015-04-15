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

#define MIN(a,b) (((a)<(b)) ? (a) : (b) ) /**< the usual "min" function */
#define MAX(a,b) (((a)<(b)) ? (b) : (a) ) /**< the usual "max" function */

// 3j function from the Slatec library
void drc6j_ (double *l2, double *l3, double *l4, double *l5, double *l6,
             double *l1_min, double *l1_max,
             double *sixcof, int *ndim, int *ier);

// 3j function from the C Slatec library
int drc6j (double l2, double l3, double l4, double l5, double l6,
           double *l1_min, double *l1_max,
           double  *sixcof, int ndim, int *ier);              

int main (int argc, char const *argv[]) {

  if (argc!=7) {
    printf("usage:    %s <l1> <l2> <l3> <l4> <l5> <l6>\n", argv[0]);
    return 1;
  }
  int l1 = atoi(argv[1]);
  double l2 = atof(argv[2]);
  double l3 = atof(argv[3]);
  double l4 = atof(argv[4]);
  double l5 = atof(argv[5]);
  double l6 = atof(argv[6]);

  // ==================
  // = Compute the 6j =
  // ==================
  /*   Prototype of the Fortran function:
      subroutine DRC6J (L2, L3, L4, L5, L6, 
        L1MIN, L1MAX, THRCOF, NDIM, IER)
     INTEGER NDIM, IER
     DOUBLE PRECISION L2, L3, L4, L5, L6, L1MIN, L2MAX, THRCOF(NDIM)  */
           
  
  // The Slatec function DRC6J computes the 6j symbol for any allowed value
  // of l1.  Here we compute the number of such values and allocate memory
  // for the result array.
  double l1_min = MAX(fabs(l2-l3),fabs(l5-l6));
  double l1_max = MIN(l2+l3,l5+l6);
  int out_size = (int)(l1_max-l1_min+1);
  double *result = (double*)calloc(out_size,sizeof(double));

  // Status flag for DRC3JM
  int ier=0;

  // Do the actual computation
  drc6j_ (&l2, &l3, &l4, &l5, &l6,
          &l1_min, &l1_max,
          result, &out_size, &ier);

	// Note that this function will compute all the 6j's for the allowed values of l1
	// given the input parameters.  If we ask for a l1 which is not in the range, then
	// we will get a unmeaningful result or a segmentation fault
	if (l1>l1_max || l1<l1_min) {
		printf("INPUT ERROR: 'l1' should be between %g and %g.\n", l1_min, l1_max);
		return 1;
	}
  
  // Print the error code
  printf("ier = %d\n", ier);

  // Find the index corresponding to the requested m2
  int l1_index = l1 - (int)l1_min;
  
  // Print the result
  printf("6J(%d,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,l4,l5,l6,result[l1_index]);
  
  // ===========================
  // = Use C version of Slatec =
  // ===========================
  
  double * result_C = (double*)calloc(out_size,sizeof(double));
  
  int status = drc6j (l2, l3, l4, l5, l6,
                      &l1_min, &l1_max,
                      result_C, out_size, &ier);
  
  // Print the error code and status
  printf("ier = %d\n", ier);
  printf("status = %d\n", status);
  
  // Print the C result
  printf("6J(%d,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,l4,l5,l6,result_C[l1_index]);

  

  return 0;
  
}