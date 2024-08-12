#ifndef DATALIB_DEFS_H
#define DATALIB_DEFS_H

#ifdef DATALIB_NO_STD
    #error "Must use standard library"
#else
    #include <stdlib.h> /* malloc, free */
    #include <string.h> /* memmove */
    #include <stdint.h> /* uint32_t */
    #include <stdarg.h> /* varags */

    #define DATALIB_ALLOC malloc
    #define DATALIB_FREE  free
    #define DATALIB_MEMMOVE memmove
#endif

#endif /* DATALIB_DEFS_H */