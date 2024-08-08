#include "vec.h"
#include "stdio.h"
#include "assert.h"

void _debug_print_vec(int* vec){
    printf("[");
    int i;
    for(i = 0; i != vec_size(vec); ++i){
        printf("%d", vec[i]);
        if(i + 1 < vec_size(vec)){
            printf(", ");
        }
    }
    printf("]\n");
}

void test_vec_init_int(){
    int* v = vec_init(int);
    assert(v);
    assert(vec_size(v) == 0);
    assert(vec_capacity(v) == 0);
    assert(vec_last(v) == v);
    assert(vec_end(v) == v);
    assert(vec_empty(v));
    vec_free(v);
}

void test_vec_init_str(){
    char* strings = vec_init(char[16]);
    assert(strings);
    assert(vec_size(strings) == 0);
    assert(vec_capacity(strings) == 0);
    assert(vec_last(strings) == strings);
    assert(vec_end(strings) == strings);
    vec_free(strings);
}

void test_vec_resize(){
    int* v = vec_init(int);
    vec_resize(v, 3);
    assert(v);
    assert(vec_size(v) == 3);
    assert(vec_capacity(v) == 4);
    assert(vec_last(v) == (v + 2));
    assert(vec_end(v) == (v + 3));
    vec_free(v);
}

void test_vec_push(){
    int* v = vec_init(int);
    vec_push(v, 5);
    assert(v);
    assert(vec_size(v) == 1);
    assert(vec_capacity(v) == 1);
    assert(vec_last(v) == v);
    assert(vec_end(v) == v + 1);
    assert(v[0] == 5);
    vec_free(v);
}

void test_vec_pop(){
    int* v = vec_init(int);
    vec_push(v, 5);
    vec_push(v, 10);
    vec_pop(v);
    assert(v);
    assert(vec_size(v) == 1);
    assert(vec_capacity(v) == 2);
    assert(vec_last(v) == v);
    assert(vec_end(v) == v + 1);
    assert(v[0] == 5);
    vec_free(v);
}

void test_vec_clear(){
    int* v = vec_init(int);
    vec_resize(v, 10);
    assert(vec_size(v) == 10);
    vec_clear(v);
    assert(vec_size(v) == 0);
    assert(vec_empty(v));
    vec_free(v);
}

void test_vec_insert(){
    int* v = vec_init(int);
    vec_push(v, 0);
    vec_push(v, 1);
    vec_push(v, 2);
    vec_insert(v, 1, 99);
    assert(v);
    assert(vec_size(v) == 4);
    assert(v[1] == 99);
    assert(v[2] == 1);
    assert(v[3] == 2);
    vec_free(v);
}

void test_vec_insert_front(){
    int* v = vec_init(int);
    vec_push(v, 0);
    vec_push(v, 1);
    vec_push(v, 2);
    vec_insert(v, 0, 99);
    assert(v);
    assert(vec_size(v) == 4);
    assert(v[0] == 99);
    assert(v[1] == 0);
    assert(v[2] == 1);
    assert(v[3] == 2);
    vec_free(v); 
}

void test_vec_insert_back(){
    int* v = vec_init(int);
    vec_push(v, 0);
    vec_push(v, 1);
    vec_push(v, 2);
    vec_insert(v, vec_size(v), 99);
    _debug_print_vec(v);
    assert(v);
    assert(vec_size(v) == 4);
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 2);
    assert(v[3] == 99);
    vec_free(v); 
}

void test_vec_insert_empty(){
    int* v = vec_init(int);
    vec_insert(v, 0, 99);
    _debug_print_vec(v);
    assert(v);
    assert(vec_size(v) == 1);
    assert(v[0] == 99);
    vec_free(v); 
}



void test_vec_run_all(){

    test_vec_init_int();
    test_vec_init_str();
    test_vec_resize();
    test_vec_push();
    test_vec_pop();
    test_vec_clear();
    test_vec_insert();
    test_vec_insert_front();
    test_vec_insert_back();
    test_vec_insert_empty();

    printf("vec tests passed\n");
}