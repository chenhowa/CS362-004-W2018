

#include "assertions_better.h"
#include <stdio.h>


int assertEq(int expected, int actual, char* label, char* description) {
    if (expected != actual) {
        printf("\tFAIL %s...expected %s = %i, got %i\n",
                description, label, expected, actual); 
        fflush(stdout);
        return FALSE;
    }
    printf("\tPASS %s\n", description);
    fflush(stdout);
    return TRUE;
}
