/* assertions.h
 *
 *
 *
 */

#include <stdio.h>

#define TRUE 1
#define FALSE 0

int assertEq(int expected, int actual, char* label, char* description);
