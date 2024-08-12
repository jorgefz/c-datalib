#ifndef DATALIB_NUMV_H
#define DATALIB_NUMV_H

#include "defs.h"


struct numv {
    size_t size; /* Number of items in the array */
    double data[]; /* Pointer to the array items */
};

void numv_debug_print(double* nv);

/* Return the number of items in a numv array `v` */
size_t numv_size(void* v);

/* Returns a pointer to the end of a numv array */
double* numv_end(double* nv);

/* --- Destructor --- */
/* Free a numv array */
void numv_free(void* p);

/* Free an arbitrary number of numv arrays.
Useful as many numv functions return new arrays.
*/
void numv_free_n(size_t n, ...);

/* --- Constructors --- */

/* Create a new numv array of size `n` without initialising its elements */
double* numv_empty(size_t n);

/* Create a new numv array of size `n` initialised to a value `value` */
double* numv_full(size_t n, double value);

/* Create a new numv array of size `n` initialised to zero */
double* numv_zeros(size_t n);

/* Create a new numv array with `n` values evenly spaced between `start` and `end` */
double* numv_range(double start, double end, size_t n);

/* Create a new numv array from a raw memory buffer */
double* numv_from_array(size_t n, double* data);

/* Allocate a new copy of an numv array */
double* numv_copy(double* nv);

/* Create a new numv array from a 'slice' of another.
 * e.g. the items between two indices [i,j] inclusive.
 * The indices may be negative to indicate index from the back of the array.
 */
double* numv_slice(double* nv, long i, long j);

/* Create a new numv array by concatenating two other arrays */
double* numv_concat(double*a, double*b);

/* Create a new nuvm array by concatenating `n` other arrays */
double* numv_concat_n(size_t n, ...);


/* --- Transforms --- */

/* Self */
/* Apply a function `fn` that takes extra arguments to a numv array */
double* numv_apply_args(double* nv, double (*fn)(double,void*), void* args);

/* Apply a function `fn` to a numv array */
double* numv_apply(double* nv, double (*fn)(double));

double* numv_sqrt(double* nv);
double* numv_cbrt(double* nv);
double* numv_replace_nans(double* nv, double value);

/* array - array */
double* numv_add(double* a, double* b);
double* numv_sub(double* a, double* b);
double* numv_mult(double* a, double* b);
double* numv_div(double* a, double* b);
double* numv_pow(double* a, double* b);
double* numv_hypot(double* a, double* b); /* sqrt(a^2 + b^2) */

/* array - scalar */
double* numv_adds(double* a, double value);
double* numv_subs(double* a, double value);
double* numv_mults(double* a, double value);
double* numv_divs(double* a, double value);
double* numv_pows(double* a, double value);



/* --- Aggregate --- */

double numv_agg(double* nv, double (*fn)(double,double));

double numv_mean();
double numv_median();
double numv_mode();
double numv_std();
double numv_max();
double numv_min();
double numv_sum();
size_t numv_imax();
size_t numv_imin();



#endif /* DATALIB_NUMV_H */