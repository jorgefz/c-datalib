/** @file vec.h
 * Definitions for datalib vector.
 * Resizeable array data structure allocated in the heap
 * where the size and capacity are stored in a header
 * located before the first element of the array.
 */

#ifndef DATALIB_VEC
#define DATALIB_VEC

#include "stdlib.h" /* size_t */

/* --- Macro functions --- */

/* Return a new vector of elements of a given type T  */
#define vec_init(T) _vec_init(sizeof(T))

/* Returns a pointer to the last element of a vector V */
#define vec_last(V) (vec_size((V))==0 ? (V) : (V)+vec_size((V))-1)

/* Returns a pointer to the end of a vector V */
#define vec_end(V) ( (V)+vec_size((V)) )

/* Changes the size of a vector V to have S elements */
#define vec_resize(V, S) \
    do { \
        void* temp__ = _vec_resize((V), sizeof(*(V)), (S)); \
        (V) = temp__; \
    } while(0)

#define vec_insert(V, I, E) \
    do { \
        size_t idx__ = (I); \
        void* temp__ =  _vec_insert((V), sizeof(*(V)), idx__); \
        (V) = temp__; \
        (V)[idx__] = (E); \
    } while(0)

/* Appends a new element E to a vector V */
#define vec_push(V, E) \
    do { \
        void* temp__ = _vec_resize((V), sizeof(*(V)), vec_size((V))+1); \
        (V) = temp__; \
        *vec_last(V) = (E); \
    } while(0)

/* Adds a new element E at the front of a vector V */
#define vec_push_front(V, E) vec_insert((V), 0, (E))

/* Removes the first element of a vector V */
#define vec_pop_front(V) _vec_pop_front((V), sizeof(*(V)))

/* Removes the item at index I from a vector V */
#define vec_delete(V, I) _vec_delete((V), sizeof(*(V)), (I))

/* Makes a copy of a vector V */
#define vec_copy(V) _vec_copy((V), sizeof(*(V)))


/* --- Public functions --- */

/* Returns the number of elements in a vector `vec` */
size_t vec_size(void* vec);

/* Return the capapcity of a vector `vec` */
size_t vec_capacity(void* vec);

/* Returns 1 if vector `vec` is empty and 0 otherwise */
size_t vec_empty(void* vec);

/* Removes all items from a vector `vec` */
void vec_clear(void* vec);

/* Free an initialised vector `vec` */
void vec_free(void* vec);

/* Removes the last element of a vector `vec` */
void vec_pop(void* vec);


/* --- Private functions --- */ 
/*       Use via macros     */

/* Initialise a new vector with a given element size */
void* _vec_init(size_t item_size);

/* Extends the capacity of a vector `vec` to the next power of two */
void* _vec_extend(void* vec, size_t item_size, size_t capacity);

/* Changes the size of a vector `vec` to size `size` */
void* _vec_resize(void* vec, size_t item_size, size_t size);

/* Makes space for a new element at index `index` in a vector `vec` */
void* _vec_insert(void* vec, size_t item_size, size_t index);

/* Removes the first element of a vector `vec` */
void _vec_pop_front(void* vec, size_t item_size);

/* Removes the item at index `index` from a vector `vec` */
void _vec_delete(void* vec, size_t item_size, size_t index);

/* Makes a copy of a vector `vec` */
void* _vec_copy(void* vec, size_t item_size);



#endif /* DATALIB_VEC */