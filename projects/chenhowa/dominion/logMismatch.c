
#include <stdio.h>


void logMisMatch(char* name, int expected, int actual) {
    printf("\texpected %s = %i, got %i\n", name, expected, actual); 
}
