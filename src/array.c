#include "array.h"


/* Returns the nearest highest power of two of an integer */
static uint32_t array_nearest_power_of_two(uint32_t n){
    if(n <= 1) return 1;
    uint32_t x = 2;
    n--;
	while (n >>= 1) x <<= 1;
	return x;
}

/* Increments capacity of an array */
static array_t* array_extend_capacity(array_t* array, uint32_t capacity){
	if(!array) return NULL;

	void* data = DATALIB_ALLOC(capacity * array->element_size);
	if(!data) return NULL;
	
	memmove(data, array->data, array->size * array->element_size);
	DATALIB_FREE(array->data);
	array->data = data;
	array->capacity = capacity;
	return array;
}


/* -- INITIALIZATIONS -- */

/*
Initialises an array via a given pointer.
Should be later freed using `array_uninit`.
*/
void* array_init(array_t* array, uint32_t element_size){
	if(!array || element_size == 0) return NULL ;
	*array = (array_t){0};
	array->element_size = element_size;
	return array;
}

/*
Deallocates and resets the array data without freeing the array object itself.
*/
void array_uninit(array_t* array){
	if(!array) return;
	if(array->data) DATALIB_FREE(array->data);
	*array = (array_t){0};
}


/* Creates a new array of size zero */
array_t* array_create(uint32_t element_size){
	if(element_size == 0) return NULL;
	array_t* array = DATALIB_ALLOC(sizeof(array_t));
	if(!array) return NULL;
	array->size = 0;
	array->data = NULL;
	array->element_size = element_size;
	return array;
}

/* Frees all the elements of an array */
void array_destroy(array_t* array){
	if(!array) return;
	if(array->data) DATALIB_FREE(array->data);
	DATALIB_FREE(array);
}

array_t* array_copy(array_t* orig){
	if(!orig) return NULL;
	array_t* new = malloc(sizeof(array_t));
	if(!new) return NULL;
	memmove(new, orig, sizeof(array_t));

	if(!orig->data){
		return new;
	}

	size_t bytes = orig->capacity * orig->element_size;
	new->data = DATALIB_ALLOC(bytes);
	memmove(new->data, orig->data, bytes);
	return new;
}

/* Pre-allocates a given number of elements but does not initialise them */
array_t* array_resize(array_t* array, uint32_t size){
	if(!array || array->element_size == 0) return NULL;

	if(size <= array->size){
		/* Shrinking - no need to delete anything.
		   Old data will eventually be overwritten if extended again. */
		array->size = size;
		return array;
	}
	
	/* Round up new capacity to the highest power of two closest to the size */
	if(size >= array->capacity){
		array_extend_capacity(array, array_nearest_power_of_two(size));
	}

	array->size = size;
	return array;
}

/* -- SETTERS -- */
/* Overwrites an element at the given index with the given data */
void* array_set(array_t* array, void* element, uint32_t index){
	if(!array || array->element_size == 0 || index >= array->size) return NULL;
	char* addr = array->data + index * array->element_size;
	if(!element){
		memset(addr, 0, array->element_size);
	} else {
		memmove(addr, element, array->element_size);
	}
	return addr;
}

/* -- RETRIEVALS -- */
/* Returns a pointer to the element at the specified index */
void* array_get(array_t* array, uint32_t index){
	if(!array || array->element_size == 0 || index >= array->size) return NULL;
	char* addr = array->data + index * array->element_size;
	return addr;
}

/* Returns a pointer to the first element */
void* array_front(array_t* array){
	if(!array || array->size == 0) return NULL;
	return array->data;
}

/* Returns a pointer to the last element */
void* array_back(array_t* array){
	if(!array || array->size == 0) return NULL;
	return array_get(array, array->size-1);
}

/* Returns a pointer to first byte after the end of the array */
void* array_end(array_t* array){
	if(!array || !array->data || array->element_size == 0) return NULL;
	if(array->size == 0){
		return array_back(array);
	}
	return (char*)array_back(array) + array->element_size;
}

/* -- INSERTING -- */
/* Inserts an element at the given index */
array_t* array_insert(array_t* array, void* element, uint32_t index){
	if(!array || array->element_size == 0 || index > array->size){
		return NULL;
	}

	if(array->size >= array->capacity || !array->data){
		array_t* r = array_extend_capacity(array, array_nearest_power_of_two(array->size));
		if(!r) return NULL;
	}
	
	char* addr = array->data + index * array->element_size;
	uint32_t move_bytes = (array->size - index) * array->element_size;
	
	if(move_bytes > 0){
		/* Displace elements to make space for new one
		   This operation is invalid if you want to insert
		   at the end of the array */
		memmove(addr + array->element_size, addr, move_bytes);
	}

	if(!element){
		memset(addr, 0, array->element_size);
	} else {
		memmove(addr, element, array->element_size);
	}
	array->size++;
	return array;
}

/* Inserts the element to the end of the array */
array_t* array_push_back(array_t* array, void* element){
	return array_insert(array, element, array->size);
}

/* Inserts the element to the beginning of the array */
array_t* array_push_front(array_t* array, void* element){
	return array_insert(array, element, 0);
}

/* -- DELETING -- */
/* Removes the element at the given index */
array_t* array_remove(array_t* array, uint32_t index){
	if(!array || !array->data || index >= array->size){
		return NULL;
	}

	if (index == array->size - 1){
		array->size--;
		return array;
	}
	
	char* dest = array->data + index * array->element_size;
	char* orig = dest + array->element_size;
	uint32_t move_bytes = (array->size - index) * array->element_size;

	memmove(dest, orig, move_bytes);

	array->size--;
	return array;
}

/* Removes the element last element of the array */
array_t* array_pop_back(array_t* array){
	if(array->size == 0) return NULL;
	return array_remove(array, array->size-1);
}

/* Removes the element first element of the array */
array_t* array_pop_front(array_t* array){
	return array_remove(array, 0);
}

/* Removes all elements on the array */
array_t* array_clear(array_t* array){
	if(!array) return NULL;
	array->size = 0;
	return array;
}

