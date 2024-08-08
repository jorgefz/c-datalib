#include "vec.h"


#include "stdlib.h" /* malloc, free */
#include "string.h" /* memmove */
#define DATALIB_ALLOC malloc
#define DATALIB_FREE  free
#define DATALIB_MEMMOVE memmove


/* Header of a vector where its metadata is stored */
struct vec_header {
    size_t size;     /* Number of elements */
    size_t capacity; /* Max elements */
    char data[];     /* Pointer to stored elements */
};

static struct vec_header* _vec_get_header(void* vec){
    if (!vec) return NULL;
    return ((struct vec_header*)vec - 1);
}

/* Returns the nearest highest power of two of an integer  */
static size_t _vec_nearest_power_of_two(size_t n){
    if(n <= 1) return 1;
    size_t x = 2;
    n--;
	while (n >>= 1) x <<= 1;
	return x;
}

size_t vec_size(void* vec){
    if (!vec) return 0;
    return _vec_get_header(vec)->size;
}

size_t vec_capacity(void* vec){
    if (!vec) return 0;
    return _vec_get_header(vec)->capacity;
}

size_t vec_empty(void* vec){
    if(!vec || vec_size(vec) == 0) return 1;
    return 0;
}

void vec_clear(void* vec){
    if(!vec) return;
    _vec_get_header(vec)->size = 0;
}

void vec_free(void* vec){
    DATALIB_FREE(_vec_get_header(vec));
}


void vec_pop(void* vec){
    if (!vec || vec_size(vec)==0) return;
    _vec_get_header(vec)->size--;
}

/* Removes the first element of a vector `vec` */
void vec_pop_front(void* vec){

}

/* Removes the item at index `index` from a vector `vec` */
void vec_delete(void* vec, size_t index){
    
}


void* _vec_init(size_t item_size){
    void* vec = _vec_extend(NULL, item_size, 0);
    if(!vec) return NULL;
    return vec;
}

/* Increments capacity of a vector to the next power of two */
void* _vec_extend(void* vec, size_t item_size, size_t capacity){
	struct vec_header* header;

    if(!vec){
        header = DATALIB_ALLOC(capacity*item_size+sizeof(*header));
        if(!header) return NULL;
        header->size = 0;
        header->capacity = capacity;
        return header->data;
    }

    header = _vec_get_header(vec);

    /* Cannot shrink capacity */
    if(capacity <= header->capacity){
        return vec;
    }

    struct vec_header* new_header = DATALIB_ALLOC(sizeof(struct vec_header) + capacity*item_size);
	if(!new_header) return NULL;
    new_header->size = header->size;
    new_header->capacity = capacity;

    DATALIB_MEMMOVE(new_header->data, header->data, new_header->size*item_size);
    DATALIB_FREE(header);

    return new_header->data;
}

void* _vec_resize(void* vec, size_t item_size, size_t size){
    if(!vec) return NULL;
    struct vec_header* header = _vec_get_header(vec);
    
    /* Shrink */
    if (size <= header->size){
        header->size = size;
        return vec;
    }

    /* Expand */
    if(size >= header->capacity){
        vec = _vec_extend(vec, item_size, _vec_nearest_power_of_two(size));
        header = _vec_get_header(vec);
        header->size = size;
        return vec;
    }
    header->size = size;
    return vec;
}

/* Makes space for a new element at index `index` in a vector `vec` */
void* _vec_insert(void* vec, size_t item_size, size_t index){
    if(!vec) return NULL;
    if(index > vec_size(vec)) return vec;

    vec = _vec_resize(vec, item_size, vec_size(vec)+1);
    struct vec_header* header = _vec_get_header(vec);

    size_t src = index * item_size;
    size_t dest = src + item_size;
    size_t n = (header->size - index) * item_size;
    DATALIB_MEMMOVE(header->data + dest, header->data + src, n);

    return vec;
}

/* Makes a copy of a vector `vec` */
void* _vec_copy(void* vec_, size_t item_size){
    char* vec = vec_;
    if(!vec) return NULL;

    char* vec2 = _vec_init(item_size);
    if(!vec2) return NULL;

    _vec_resize(vec2, item_size, vec_size(vec));
    size_t i;
    for(i = 0; i != vec_size(vec); i++){
        vec2[i] = vec[i];
    }
    return vec2;
}
