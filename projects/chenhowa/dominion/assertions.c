
/* assertions.c
 * Implementation file for assertTrue() function
 * Author: Howard Chen
 * Date created: 1-25-2017
 *
 */


#include <stdio.h> //for printf-like functions
#include <string.h> //for memcp like functions
#include "assertions.h"


int assertTrue(int condition, char* test_description) {
    fprintf(stderr, "%s", test_description);
    if(condition == TRUE) {
        fprintf(stderr,  "...PASSED\n");
        return TRUE;
    }
    else {
        fprintf(stderr, "...FAILED\n");
        return FALSE;
    }
}
