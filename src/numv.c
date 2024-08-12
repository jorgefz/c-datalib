#include "numv.h"

#include "stdio.h"

void numv_debug_print(double* nv){
    if(!nv){
        printf("[ null ]\n");
        return;
    }
    printf("[");
    for(size_t i = 0; i != numv_size(nv); ++i){
        printf("%g", nv[i]);
        if(i != numv_size(nv) - 1) printf(", ");
    }
    printf("]\n");
}

/* Return the number of items in a numeric vector `v` */
size_t numv_size(void* v){
    if(!v) return 0;
    return *((size_t*)v - 1);
}

/* Returns a pointer to the end of a numv array */
double* numv_end(double* nv){
    if(!nv) return NULL;
    return nv + numv_size(nv);
}

/* Free a numv array */
void numv_free(void* p){
    if(!p) return;
    char* ptr = (char*)p - sizeof(size_t);
    DATALIB_FREE(ptr);
}

/* Free an arbitrary number of numv arrays.
Useful as many numv functions return new arrays.
*/
void numv_free_n(size_t n, ...){
    va_list args;
    va_start(args, n);
    size_t i;
    for(i = 0; i != n; ++i){
        numv_free(va_arg(args,double*));
    }
    va_end(args);
}

/* Create a numeric vector of size `n` with uninitialised values */
double* numv_empty(size_t n){
    if(n == 0) return NULL;
    struct numv* nv = DATALIB_ALLOC(sizeof(struct numv) + n * sizeof(double));
    nv->size = n;
    if(nv) return nv->data;
    return NULL;
}

/* Create a new numv array of size `n` initialised to a value `value` */
double* numv_full(size_t n, double value){
    double* nv = numv_empty(n);
    if(!nv) return NULL;
    double* item;
    for(item = nv; item != numv_end(nv); ++item){
        *item = value;
    }
    return nv;
}

/* Create a new numv array of size `n` initialised to zero */
double* numv_zeros(size_t n){
    return numv_full(n, 0);
}

/* Create a new numv array with `n` values evenly spaced between `start` and `end` */
double* numv_range(double start, double end, size_t n){
    double value = start, step = (end-start)/(double)n;
    double* nv = numv_empty(n);
    if(!nv) return NULL;
    double* item;
    for(item = nv; item != numv_end(nv); ++item){
        *item = value;
        value += step;
    }
    return nv;
}

/* Create a new numv array from a raw memory buffer */
double* numv_from_array(size_t n, double* data){
    double* nv = numv_empty(n);
    if(!nv) return NULL;
    size_t i;
    for(i = 0; i != n; ++i){
        nv[i] = data[i];
    }
    return nv;
}

/* Allocate a new copy of an numv array */
double* numv_copy(double* nv){
    return numv_from_array(numv_size(nv), nv);
}

/* Create a new numv array from a 'slice' of another.
 * e.g. the items between two indices [i,j] inclusive.
 * The indices may be negative to indicate index from the back of the array.
 */
double* numv_slice(double* nv, long i, long j){
    if(!nv) return NULL;
    size_t sz = numv_size(nv);

    /*
     * Negative sign indicates backwards index from the last element    
     *    Array      | a| b| c| d| e|
     *    Pos. Index   0  1  2  3  4
     *    Neg. Index  -5 -4 -3 -2 -1
     */
    if (i < 0) i += sz;
    if (j < 0) j += sz;

    if(i >= j || i < 0 || j >= sz){
        return NULL;
    }
    return numv_from_array(j - i + 1, nv + i);
}


/* Create a new numv array by concatenating two other arrays */
double* numv_concat(double*a, double*b){
    return numv_concat_n(2, a, b);
}


/* Create a new nuvm array by concatenating `n` other arrays */
double* numv_concat_n(size_t n, ...){
    va_list args_sz;
    va_list args_dat;

    va_start(args_sz, n);
    va_copy(args_dat, args_sz);

    /* Total size must first be known to allocate numv array */
    size_t i;
    size_t total_sz = 0;
    for(i = 0; i != n; ++i){
        double* v = va_arg(args_sz, double*);
        total_sz += numv_size(v);
    }
    va_end(args_sz);

    double* nv = numv_empty(total_sz);
    if(!nv){
        va_end(args_dat);
        return NULL;
    }

    /* Copy data from each input array */
    double* p = nv;
    for(i = 0; i != n; ++i){
        double* v = va_arg(args_dat, double*);
        memmove(p, v, numv_size(v) * sizeof(double));
        p += numv_size(v);
        if(p > nv + total_sz) return NULL;
    }
    va_end(args_dat);

    return nv;
}


/* Apply a function `fn` that takes extra arguments to a numv array */
double* numv_apply_args(double* nv, double (*fn)(double,void*), void* args){
    if(!nv || !fn) return NULL;
    size_t i;
    for(i = 0; i != numv_size(nv); ++i){
        nv[i] = fn(nv[i], args);
    }
    return nv;
}


/* Apply a function `fn` to a numv array */
double* numv_apply(double* nv, double (*fn)(double)){
    if(!nv || !fn) return NULL;
    size_t i;
    for(i = 0; i != numv_size(nv); ++i){
        nv[i] = fn(nv[i]);
    }
    return nv;
}



