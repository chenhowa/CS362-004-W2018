

#include "assertions.h"



int assertEq(int expected, int actual, char* label, char* description) {
    if (expected != actual) {
        printf("\tFAIL %s...expected %s = %i, got %i\n",
                description, label, expected, actual); 
        return FALSE;
    }
    return TRUE;

}
