# c-datalib

`datalib` is a library with data structures and data manipulation utilities written in C, which follows the C89 standard.

## Contents

### `vec`
Resizeable generic array that stores its metadata (number of elements and capacity) in the memory before the first element.

### `array`
Resizeable generic array.

### `numv`
Fixed-size numeric array with fast element-wise operations.

### `hashmap`
Hashtable.

### `linkedlist`
Double linked list.


## Usage

Compile the `.c` files in the folder `src` adding the folder `include` (which contains the header files) as an include directory (e.g. `-Iinclude`).

## Running tests

Compile the implementation files in both the `src` and the `test` folders into an executable, adding the `include` as an include directory.
Run the resulting executable to run the tests.


