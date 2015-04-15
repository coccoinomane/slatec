#ifndef __SLATEC_3J_INTERFACE__
#define __SLATEC_3J_INTERFACE__

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define sqrt_pi_over_2 1.25331413731550025120788264241
#define MIN(a,b) (((a)<(b)) ? (a) : (b) ) /**< the usual "min" function */
#define MAX(a,b) (((a)<(b)) ? (b) : (a) ) /**< the usual "max" function */
#define _SUCCESS_ 0 /**< integer returned after successfull call of a function */
#define _FAILURE_ 1 /**< integer returned after failure in a function */


int threej_l1(
       int l2, int l3, int m2, int m3,    // In
       int *l1_min, int *l1_max,          // Out, 'm2' limits for which result was computed
       double **result,                   // Out
       int *result_size                   // Out
       // ErrorMsg errmsg
       );

int threej_m2(
      int l1, int l2, int l3, int m1,    // In
      int *m2_min, int *m2_max,          // Out, 'm2' limits for which result was computed
      double **result,                   // Out
      int *result_size                   // Out
      // ErrorMsg errmsg         
      );

int sixj_l1(
       int l2, int l3, int l4, int l5, int l6,    // In
       int *l1_min, int *l1_max,                  // Out, 'l1' limits for which the result is computed
       double **result,                           // Out, has size equal to 'result_size' (should be allocated already)
       int *result_size                           // Out, equal to l1_max + l1_min + 1.
       // ErrorMsg errmsg       
       );

int besselj_l1(
       float l,                          // In
       float x,                          // In
       int N,                            // In
       float **result                    // Out (array of size N)
       // ErrorMsg errmsg
       );

int besselJ_l1(
       float l,                          // In
       float x,                          // In
       int N,                            // In
       float **result                    // Out (array of size N)
       // ErrorMsg errmsg
       );

#endif