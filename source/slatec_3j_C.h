#ifndef __SLATEC_3J__
#define __SLATEC_3J__

/* Standard libraries */
#include "stdio.h"
#include "math.h"
#include "float.h"

/* Macro definitions */
#define MIN(a,b) (((a)<(b)) ? (a) : (b) ) /**< the usual "min" function */
#define MAX(a,b) (((a)<(b)) ? (b) : (a) ) /**< the usual "max" function */

#define _SUCCESS_ 0 /**< integer returned after successfull call of a function */
#define _FAILURE_ 1 /**< integer returned after failure in a function */

#define alternating_sign(m) ((m)%2 == 0 ? 1 : -1) /**< Return (-1)^m with integer m */


int drc3jm (double L1, double L2, double L3, double M1, /* IN, parameters */
            double *M2MIN, double *M2MAX,               /* OUT, limits of m2 */
            double * THRCOF,                            /* OUT, result */
            int NDIM,                                   /* IN, length of result */
            int * IER);                                 /* OUT, error code, 0 ok */


int drc3jj (double L2, double L3, double M2, double M3, /* IN, parameters */
            double *L1MIN, double *L1MAX,               /* OUT, limits of l1 */
            double * THRCOF,                            /* OUT, result */
            int NDIM,                                   /* IN, length of result */
            int * IER);                                 /* OUT, error code, 0 ok */

int drc6j (double L2, double L3, double L4, double L5, double L6, /* IN, parameters */
           double *L1MIN, double *L1MAX,               /* OUT, limits of l1 */
           double * SIXCOF,                            /* OUT, result */
           int NDIM,                                   /* IN, length of result */
           int * IER);                                 /* OUT, error code, 0 ok */
           
#endif