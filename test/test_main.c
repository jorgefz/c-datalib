#include "stdio.h"

void test_vec_run_all();
void test_array_run_all();

int main(int argc, char* argv[]){
    
    test_vec_run_all();
    test_array_run_all();

    printf("All tests passed\n");

    return 0;
}