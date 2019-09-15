#ifndef BLUE_H 
#define BLUE_H

#include <sys/types.h> /* off_t */

typedef struct {
    char* hash;
    off_t size;
} SIGNATURE;

int
BlueSearch(const SIGNATURE sign, const char* root);

#endif
