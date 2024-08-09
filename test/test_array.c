#include "stdio.h"
#include "assert.h"
#include "array.h"

void test_array_init(){
	array_t a;
	void* r = array_init(&a, sizeof(int));
	assert(r == &a);
	assert(a.size == 0);
	assert(a.capacity == 0);
	assert(a.element_size == sizeof(int));
	assert(!a.data);
	array_uninit(&a);
}

void test_array_init_zero_item_size(){
	array_t a;
	void* r = array_init(&a, 0);
	assert(!r);
	array_uninit(&a);
}

void test_array_create(){
	array_t* a = array_create(sizeof(int));
	assert(a);
	assert(a->size == 0);
	assert(a->capacity == 0);
	assert(!a->data);
	assert(a->element_size == sizeof(int));
	array_destroy(a);
}

void test_array_create_zero_element_size(){
	array_t* a = array_create(0);
	assert(!a);
}

void test_array_resize(){
	array_t a;
	array_init(&a, sizeof(int));
	void* r = array_resize(&a, 5);
	assert(r == &a);
	assert(a.size == 5);
	assert(a.capacity == 8); /* nearest power of two */
	assert(a.data);
	array_uninit(&a);
}

void test_array_set(){
	array_t a;
	int r = 1;
	int val1 = 1, val2 = 2, val_null = 0;
	array_init(&a, sizeof(int));
	array_resize(&a, 3);
	r = r && array_set(&a, &val1, 0);
	r = r && array_set(&a, &val2, 1);
	r = r && array_set(&a, NULL, 2);
	assert(r);
	assert(((int*)a.data)[0]==val1);
	assert(((int*)a.data)[1]==val2);
	assert(((int*)a.data)[2]==val_null);
	array_uninit(&a);
}

void test_array_set_out_of_bounds(){
	array_t a;
	void* r;
	array_init(&a, sizeof(int));
	r = array_set(&a, NULL, 0);
	assert(!r);
	array_resize(&a, 5);
	r = array_set(&a, NULL, 10);
	assert(!r);
	array_uninit(&a);
}

void test_array_get(){
	array_t a;
	int vals[] = {5, 6};
	array_init(&a, sizeof(int));
	array_resize(&a, 2);
	array_set(&a, &vals[0], 0);
	array_set(&a, &vals[1], 1);
	int* v1 = array_get(&a, 0);
	int* v2 = array_get(&a, 1);
	assert(*v1 == vals[0]);
	assert(*v2 == vals[1]);
	array_uninit(&a);
}

void test_array_get_out_of_bounds(){
	array_t a;
	array_init(&a, sizeof(int));
	int* v1 = array_get(&a, 0);
	assert(!v1);
	array_resize(&a, 2);
	int* v2 = array_get(&a, 5);
	assert(!v2);
	array_uninit(&a);
}

void test_array_insert(){
	array_t a;
	array_init(&a, sizeof(int));
	array_resize(&a, 3);
	int val1 = 0, val2 = 1, val3 = 2;
	array_set(&a, &val1, 0);
	array_set(&a, &val2, 1);
	array_set(&a, &val3, 2);
	int val_ins = 99;
	void* r = array_insert(&a, &val_ins, 1);
	assert(r);
	assert(a.size == 4);
	assert(*(int*)array_get(&a,0) == val1);
	assert(*(int*)array_get(&a,1) == val_ins);
	assert(*(int*)array_get(&a,2) == val2);
	assert(*(int*)array_get(&a,3) == val3);
	array_uninit(&a);
}

void test_array_insert_wrong_index(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_push_back(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_push_front(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_remove(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_remove_empty(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_pop_back(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}

void test_array_pop_front(){
	array_t a;
	array_init(&a, sizeof(int));
	array_uninit(&a);
}


void test_array_run_all(){
	test_array_init();
	test_array_init_zero_item_size();
	test_array_create();
	test_array_create_zero_element_size();
	test_array_resize();
	test_array_set();
	test_array_set_out_of_bounds();
	test_array_get();
	test_array_get_out_of_bounds();
	test_array_insert();
	test_array_insert_wrong_index();
	test_array_push_back();
	test_array_push_front();
	test_array_remove();
	test_array_pop_back();
	test_array_pop_front();

	printf("array tests passed\n");
}

/*
void test_array(void** state){
	(void)state;

	array_t *r = NULL;

	// Initialise array with element size 0
	// Functions should return NULL value
	array_t z;
	array_init(&z, 0);
	r = array_resize(&z, 10);
	assert_null(r);
	r = array_insert(&z, (void*)5, 0);
	assert_null(r);
	array_uninit(&z);

	// Initialise array of integers
	array_t x;
	array_init(&x, sizeof(int));
	assert_true(x.size==0);
	assert_true(x.capacity==0);
	assert_null(x.data);

	array_uninit(&x);
	assert_true(x.size==0);
	assert_true(x.capacity==0);
	assert_null(x.data);
	assert_true(x.element_size==0);
	
	// Initialise with allocated memory
	array_t* a = array_create(sizeof(int));
	assert_non_null(a);
	assert_true(a->element_size==sizeof(int));
	assert_true(a->size==0);

	// Resize
	r = array_resize(a, 10);
	assert_non_null(r);
	assert_true(a->size==10);
	assert_true(a->capacity==16);
	assert_non_null(a->data);

	// Setting elements
	int res = 1;
	for(int i = 0; i != (int)a->size; ++i){
		res = res && array_set(a, &i, i);
	}
	assert_true(res);

	// Getting elements
	res = 1;
	for(int i = 0; i != (int)a->size; ++i){
		res = res && (*(int*)array_get(a, i) == i);
	}
	assert_true(res);

	res = (*(int*)array_front(a)==0) && (*(int*)array_back(a)==9);
	assert_true(res);

	// Case: value passed is NULL
	r = array_set(a, NULL, 1);
	res = (r) && (*(int*)array_get(a,1) == 0);
	assert_true(res);

	// Limiting case: index out of bounds
	r = array_set(a, NULL, a->size);
	assert_null(r);

	// Inserting a value
	int prev = *(int*)array_get(a, 5);
	int value = 99;
	r = array_insert(a, &value, 5);

	res = r && (a->size == 11);
	res = res && (*(int*)array_get(a,5)==value) && (*(int*)array_get(a,6)==prev);
	assert_true(res);

	// Removing a value
	r = array_remove(a, 1);
	r = array_pop_back(a);
	r = array_pop_front(a);

	res = r && (a->size == 8)
			&& (*(int*)array_front(a)==2)
			&& (*(int*)array_back(a)==8);
	assert_true(res);

	// array_clear
	r = array_clear(a);
	assert_non_null(r);
	assert_true(a->size==0);

	array_destroy(a);

}
*/
