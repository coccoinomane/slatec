#include "slatec_c_interface.h"



// ==============================================================================
// =                                3J and 6J symbols                           =
// ==============================================================================


/** 
 * Compute the 3j symbol
 * (    l1     l2     l3   )
 * ( -m2-m3    m2     m3   )
 * for all allowed values of 'L1'.
 * 
 * The result has double precision and shall be stored into the 'result' array,
 * that needs to be preallocated to contain at least l2+l3 - abs(l2-l3) + 1 elements.
 *
 */
int threej_l1(
       int l2, int l3, int m2, int m3,    // In
       int *l1_min, int *l1_max,          // Out, 'l1' limits for which the result is computed
       double **result,                   // Out, has size equal to 'result_size' (should be allocated already)
       int *result_size                   // Out, equal to l1_max + l1_min + 1.
       // ErrorMsg errmsg       
       )
{
         
  /* Prototype of the Fortran function:
    subroutine DRC3JJ (L2, L3, M2, M3, L1MIN, L1MAX, THRCOF, NDIM, &
         IER)
    INTEGER NDIM, IER
    DOUBLE PRECISION L2, L3, M3, M3, L1MIN, L2MAX, THRCOF(NDIM)  */
         
  /* The Slatec function DRC3JJ computes the 3j symbol for any allowed value
  of l1.  Here we compute the number of such values */     
  int m1 = -m2-m3;
  *l1_min = MAX(abs(l2-l3),abs(m1)); 
  *l1_max = l2+l3;
  *result_size = (int)(*l1_max-*l1_min+1.);

  /* This variable will contain the potential error message.
  For the meanings of the error messages, refer to the
  documentation in the file slatec_3j_f90.f90  */
  int ier = 0;

  /* drc3jm_ accepts doubles rather than integers, so we need to cast our arguments */
  double l2D = (double)(l2);
  double l3D = (double)(l3);
  double m2D = (double)(m2);
  double m3D = (double)(m3);
  double l1_min_D = (double)(*l1_min);
  double l1_max_D = (double)(*l1_max);

  /* Perform the actual computation */
  drc3jj_ (&l2D, &l3D, 
           &m2D, &m3D, &l1_min_D, &l1_max_D,
           *result, result_size, &ier);

  /* Check that we computed the correct bounds for the resulting array (disable for speed) */
  if ((*l1_min != (int)l1_min_D) || (*l1_max != (int)l1_max_D)) {
    printf ("the 'l1' limits in DRC3JJ are different that those give as an input: %d!=%d, %d!=%d.\n",
    *l1_min, (int)l1_min_D, *l1_max, (int)l1_max_D);
  }

  /* Return _FAILURE_ if something went wrong */
  if (ier != 0) {
    printf("drc3jj_ exited with error code ier = %d\n", ier);
    return _FAILURE_;
  }

  // *** Some debug
  // printf("3j(%d,%d,%d)(%d,%d,%d) = %.15g\n", *l1_min, l2, l3, -m2-m3, m2, m3, (*result)[0]);
  
  return _SUCCESS_;
  
}





/** 
 * Compute the 3j symbol
 * (  l1    l2     l3   )
 * (  m1    m2  -m1-m2  )
 * for all allowed values of 'm2'.
 *
 * The result has double precision and shall be stored into the 'result' array, that needs
 * to be preallocated to contain at least MIN(l2,l3-m1) - MAX(-l2,-l3-m1) + 1 elements.
 */
int threej_m2(
       int l1, int l2, int l3, int m1,    // In
       int *m2_min, int *m2_max,          // Out, 'm2' limits for which the result is computed
       double **result,                   // Out, has size equal to 'result_size' (should be allocated already)
       int *result_size                   // Out, equal to m2_max-m2_min+1
       // ErrorMsg errmsg       
       ) {
         
  /*   Prototype of the Fortran function:
     subroutine DRC3JM (L1, L2, L3, M1, M2MIN, M2MAX, THRCOF, NDIM, &
          IER)
     INTEGER NDIM, IER
     DOUBLE PRECISION L1, L2, L3, M1, M2MIN, M2MAX, THRCOF(NDIM)  */
         
  /*   The Slatec function DRC3JM computes the 3j symbol for any allowed value
     of m2.  Here we compute the number of such values */
  *m2_min = MAX(-l2,-l3-m1); 
  *m2_max = MIN(l2,l3-m1);
  *result_size = (int)(*m2_max-*m2_min+1.);

  /*   This variable will contain the potential error message.
     For the meanings of the error messages, refer to the
     documentation in the file slatec_3j_f90.f90  */
  int ier = 0;

  /* drc3jm_ accepts doubles rather than integers, so we need to cast our arguments */
  double l1D = (double)(l1);
  double l2D = (double)(l2);
  double l3D = (double)(l3);
  double m1D = (double)(m1);
  double m2_min_D = (double)(*m2_min);
  double m2_max_D = (double)(*m2_max);
         
  /* Perform the actual computation */
  drc3jm_ (&l1D, &l2D, &l3D,
           &m1D, &m2_min_D, &m2_max_D,
           *result, result_size, &ier);

  /* Check that we computed the correct bounds for the resulting array (disable for speed) */
  if( (*m2_min != (int)m2_min_D) || (*m2_max != (int)m2_max_D)) {
    printf ("found a discordance between the 'm2' limits of the 3j symbol computed by DRC3JM and those we estimated above.\n");
    return _FAILURE_;
  }          

  /* Return _FAILURE_ if something went wrong */
  if (ier != 0) {
    printf("drc3jm_ exited with error code ier = %d\n", ier);
    return _FAILURE_;
  }
  
  return _SUCCESS_;
  
}






/** 
 * Compute the 6j symbol
 * {   l1     l2     l3   }
 * {   l4     l5     l6   }
 * for all allowed values of 'l1'.
 * 
 * The result had double precision and shall be stored into the 'result' array, that
 * needs to be preallocated to contain at least
 * MIN(L2+L3,L5+L6) - MAX(ABS(L2-L3),ABS(L5-L6)) + 1 elements.
 *
 */

int sixj_l1(
       int l2, int l3, int l4, int l5, int l6,    // In
       int *l1_min, int *l1_max,                  // Out, 'l1' limits for which the result is computed
       double **result,                           // Out, has size equal to 'result_size' (should be allocated already)
       int *result_size                           // Out, equal to l1_max + l1_min + 1.
       // ErrorMsg errmsg       
       )
{
         
  /* Prototype of the Fortran function:
    subroutine DRC6J (L2, L3, L4, L5, L6, L1MIN, L1MAX, SIXCOF, NDIM, &
             IER)    
    DOUBLE PRECISION L2, L3, L4, L5, L6, L1MIN, L1MAX, SIXCOF(NDIM)
    INTEGER NDIM, IER */
         
  /* The Slatec function DRC6J computes the 6j symbol for any allowed value
    of l1.  Here we compute the number of such values and allocate memory
    for the result array.  */
     
  *l1_min = MAX (abs(l2-l3), abs(l5-l6));
  *l1_max = MIN (l2+l3, l5+l6);
  *result_size = (int)(*l1_max-*l1_min+1);

  /* This variable will contain the potential error message.
    For the meanings of the error messages, refer to the
    documentation in the file slatec_3j_f90.f90  */
  int ier = 0;

  /* drc6j_ accepts doubles rather than integers, so we need to cast our arguments */
  double l2D = (double)(l2);
  double l3D = (double)(l3);
  double l4D = (double)(l4);
  double l5D = (double)(l5);
  double l6D = (double)(l6);
  double l1_min_D = (double)(*l1_min);
  double l1_max_D = (double)(*l1_max);

  /* Perform the actual computation */
  extern void drc6j_();
  drc6j_ (&l2D, &l3D, &l4D, &l5D, &l6D,
          &l1_min_D, &l1_max_D,
          *result, result_size, &ier);

  /* Check that we computed the correct bounds for the resulting array */
  if( (*l1_min != (int)l1_min_D) || (*l1_max != (int)l1_max_D)) {
    printf ("found a discordance between the 'l1' limits of the 6j symbol computed by DRC6JJ and those we estimated above.\n");
    return _FAILURE_;
  }          

  /* Return _FAILURE_ if something went wrong */
  if (ier != 0) {
    printf("drc6j_ exited with error code ier = %d\n", ier);
    return _FAILURE_;
  }

  // *** Some debug
  // printf("6j{%d,%d,%d}{%d,%d,%d} = %.15g\n", *l1_min, l2, l3, l4, l5, l6, (*result)[0]);
  
  return _SUCCESS_;
  
}



// ==============================================================================
// =                                Bessel functions                            =
// ==============================================================================


/**
 *  Given the arguments l >= 0.0D0, x >= 0.0D0, compute
 *  the value of the spherical Bessel function
 *
 *        j_l( x )
 *
 *  for values of l going from l to l+N-1.
 *
 * This function has single precision.  In order to use double
 * precision, change float -> double and us dbesj_ instead of
 * besj_.
 *
 */
int besselj_l1(
       float l,                          // In
       float x,                          // In
       int N,                            // In
       float **result                    // Out (array of size N)
       // ErrorMsg errmsg
       )
{
  
  int dump, i;

  /* The Slatec function BESJ computes the Bessel J_l(x) for the l-values going
  from l to l + N -1. The last argument, NZ, is non-important.  Since we are
  interested in the spherical Bessel functions, we increment l by 0.5.  */
  l = l + 0.5;
  besj_ (&x, &l, &N, *result, &dump);

  /*  Uncomment the following line if you need to use double precision */
  // dbesj_ (&x, &l, &N, *result, &dump);
  
  /* Compute the spherical Bessel function */
  float factor = sqrt_pi_over_2/sqrt(x);
  for(i=0; i<N; ++i)
    (*result)[i] *= factor;

  // *** Some debug
  // printf("j(%.15g,%20.15g) = %.15g\n", l-0.5, x, (*result)[0]);
  
  return _SUCCESS_; 
  
}



/**
 *  Given the arguments l >= 0.0D0, x >= 0.0D0, compute
 *  the value of the Bessel function
 *
 *        J_l( x )
 *
 *  for values of l going from l to l+N-1.
 *
 * This function has single precision.  In order to use double
 * precision, change float -> double and us dbesj_ instead of
 * besj_.
 *
 */
int besselJ_l1(
       float l,                          // In
       float x,                          // In
       int N,                            // In
       float **result                    // Out (array of size N)
       // ErrorMsg errmsg
       )
{
  
  int dump;

  /*   The Slatec function BESJ computes the Bessel J_l(x) for the l-values going
     from l to l + N -1. The last argument, NZ, is non-important. */
  besj_ (&x, &l, &N, *result, &dump);

  /*  Uncomment the following line if you need to use double precision */
  // dbesj_ (&x, &l, &N, *result, &dump);
  
  // *** Some debug
  // printf("j(%.15g,%20.15g) = %.15g\n", l, x, (*result)[0]);
  
  return _SUCCESS_; 
  
}