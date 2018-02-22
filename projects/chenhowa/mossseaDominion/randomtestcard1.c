//
// Sean Moss
// Random Test for Garden Card
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {

    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
                     smithy, council_room};
    int k = 0;
    int i = 0;
    int j = 0;
    int check = 0;

    printf("--------------------Testing Gardens Card----------\n");

    // seed random
    srand(time(NULL));

    // runs 1000 random tests
    for(k = 0; k < 2000; k++) {

        struct gameState myGameState;

        // fill gamestate with random data

        for (j = 0; j < sizeof(struct gameState); j++) {
            ( (char*) &myGameState)[j] = floor(rand() * 256);
        }


        // choose random hand position (within limits)
        int handPos = rand() % 10;

        int myReturn = cardEffect(gardens,0,0,0, &myGameState, handPos, NULL);

        if (myReturn != -1){
            printf( "Test Failed at handpos %d! Return not equal to -1\n", handPos);
            check += 1;
        }
    }

    if(check == 0){
        printf( "All tests passed!\n");
    }

    return 0;
};