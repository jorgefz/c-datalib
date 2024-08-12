#ifndef DATALIB_NUMV_MASK_H
#define DATALIB_NUMV_MASK_H

#include "defs.h"


/* === numv_mask === */
struct numv_mask {
    size_t size; 
    uint32_t bits[];
};

uint32_t numv_mask_get(uint32_t* mask, size_t index);
uint32_t* numv_mask_set(uint32_t* mask, size_t index, uint32_t value);

/* --- Constructors --- */
uint32_t* numv_mask_init(size_t n);
uint32_t* numv_mask_ones(size_t n);
uint32_t* numv_mask_zeros(size_t n);
uint32_t* numv_mask_copy(uint32_t* mask);

/* Create mask by applying function to numeric vec */
uint32_t* numv_mask_from_func(double* nv, uint32_t (*fn)(double));
uint32_t* numv_mask_from_func_args(double* nv, uint32_t (*fn)(double,void*), void* args);

/* Modify mask with bitwise operations: and, or, not, xor*/
uint32_t* numv_mask_and(uint32_t* mask1, uint32_t* mask2);
uint32_t* numv_mask_or(uint32_t* mask1, uint32_t* mask2);
uint32_t* numv_mask_xor(uint32_t* mask1, uint32_t* mask2);
uint32_t* numv_mask_not(uint32_t* mask);

/* Check mask */
uint32_t numv_mask_all(uint32_t* mask); // Returns 1 if all bits are set
uint32_t numv_mask_any(uint32_t* mask); // Returns 1 if any bit is set

/* Filter numeric vec with a mask */
double* numv_apply_mask(double* nv, uint32_t* mask);

/* Create a new array by filtering another array with a function
    Only elements on which the function returns 1 are added to the new array.
*/
double* numv_filter(double* nv, uint32_t (*fn)(double));

double* numv_filter_args(double* nv, uint32_t (*fn)(double,void*), void* args);


#endif /* DATALIB_NUMV_MASK_H */
