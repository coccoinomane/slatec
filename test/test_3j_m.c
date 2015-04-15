/*
 *  Test the SLATEC function 'DRC3JM'.
 *  Given the arguments L1, L2, L3, M1, M2, print to
 *  screen the value of the 3j symbol:
 *
 *          (  L1   L2    L3   )
 *          (  M1   M2  -M1-M2 )
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MIN(a,b) (((a)<(b)) ? (a) : (b) ) /**< the usual "min" function */
#define MAX(a,b) (((a)<(b)) ? (b) : (a) ) /**< the usual "max" function */

// 3j function from the Fortran Slatec library
void drc3jm_ (double *l1, double *l2, double *l3,
              double *m1, double *m2_min, double *m2_max,
              double *thrcof, int *ndim, int *ier);

// 3j function from the C Slatec library
int drc3jm (double l1, double l2, double l3,
            double m1, double *m2_min, double *m2_max,
            double  *thrcof, int ndim, int *ier);              

// Limits function from the Slatec library
double d1mach_ (int * index);

// Simple test function I defined and put in the Slatec library
void set_array_to_one_ (double *, int *);


int main (int argc, char const *argv[]) {

  if (argc!=6) {
    printf("usage:    %s <l1> <l2> <l3> <m1> <m2>\n", argv[0]);
    return 1;
  }
  double l1 = atof(argv[1]);
  double l2 = atof(argv[2]);
  double l3 = atof(argv[3]);
  double m1 = atof(argv[4]);
  double m2 = atof(argv[5]);

  // ===================================
  // = Tests on the C-Fotran interface =
  // ===================================
  // Snippet that tests that arrays are passed correctly from C to Fortran
  // int size = 10;
  // double *pntr = (double*)calloc(size,sizeof(double));
  // 
  // set_array_to_one_(pntr, &size);
  // 
  // int i=0;
  // for(i=0; i<size; ++i) {
  //   printf("%g\n", pntr[i]);
  // }

  // Print the largest 'double' number 
  // int D1MACH_argument = 2;
  // printf("D1MACH(%d) = %g\n", D1MACH_argument, d1mach_(&D1MACH_argument));


  // ==================
  // = Compute the 3j =
  // ==================
  // Prototype in Fortran:
  // subroutine DRC3JM (L1, L2, L3, M1, M2MIN, M2MAX, THRCOF, NDIM, &
  //      IER)
  // INTEGER NDIM, IER
  // DOUBLE PRECISION L1, L2, L3, M1, M2MIN, M2MAX, THRCOF(NDIM)
  
  
  // The Slatec function DRC3JM computes the 3j symbol for any allowed value
  // of m2.  Here we compute the number of such values and allocate memory
  // for the result array.
  double m2_min = MAX(-l2,-l3-m1);
  double m2_max = MIN(l2,l3-m1);
  int out_size = m2_max-m2_min+1;
  double *result = (double*)calloc(out_size,sizeof(double));
  printf ("Will compute %d 3j's in the range m2=[%d,%d]\n", out_size, (int)m2_min, (int)m2_max);

  // Status flag for DRC3JM
  int ier=0;

  // Do the actual computation
  drc3jm_ (&l1, &l2, &l3,
           &m1, &m2_min, &m2_max,
           result, &out_size, &ier);

	// Note that this function will compute all the 3j's for the allowed values of m2
	// given the input parameters.  If we ask for a m2 which is not in the range, then
	// we will get a unmeaningful result or a segmentation fault
	if (m2>m2_max || m2<m2_min) {
		printf("INPUT ERROR: 'm2' should be between %d and %d.\n", (int)m2_min, (int)m2_max);
		return 1;
	}
  
  // Print the error code
  printf("ier = %d\n", ier);

  // Find the index corresponding to the requested m2
  int m2_index = m2 - (int)m2_min;
  
  // Print the Fortran result
  printf("3J(%g,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,m1,m2,-m1-m2,result[m2_index]);

  // ===========================
  // = Use C version of Slatec =
  // ===========================
  
  double * result_C = (double*)calloc(out_size,sizeof(double));
  
  int status = drc3jm (l1, l2, l3,
                       m1, &m2_min, &m2_max,
                       result_C, out_size, &ier);

  // Print the error code and status
  printf("ier = %d\n", ier);
  printf("status = %d\n", status);

  // Print the C result
  printf("3J(%g,%g,%g)(%g,%g,%g) = %g\n", l1,l2,l3,m1,m2,-m1-m2,result_C[m2_index]);

  return 0;
  
}