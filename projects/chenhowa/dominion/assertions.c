
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
    printf("%s", test_description);
    if(condition == TRUE) {
        printf("%s\n", "...PASSED");
        return TRUE;
    }
    printf("%s\n", "...FAILED");
    return FALSE;
}
