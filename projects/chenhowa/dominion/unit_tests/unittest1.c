/* Basic non-fuzzy unit tests for dominion.c function numHandCards
 *
 *
 */


#include "../dominion.h"
#include "../dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "../assertions.h"
#include "../rngs.h"
#include <stdlib.h>


//Contains all tests for numHandCards()
int testNumHandCards() {
    //Declaration of testing-specific variables
    char *description_1;
    char *description_2;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int maxHandCards = 5;
    int cards;
    int condition;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);


    description_1 = "numHandCards returns the correct number of cards";
    description_2 = "numHandCards does not change the game state";

    /**************TEST 1: return value ****************************/
    for(cards = 0; cards <= maxHandCards; cards++) {
        printf("Testing a hand of %i cards\n", cards);
        // Update hand count
        postState.handCount[ postState.whoseTurn ] = cards;

        // Save the state of the game in preState

        memcpy(&preState, &postState, sizeof(struct gameState));
        condition = cards == numHandCards(&postState);
        didAllPass = assertTrue(condition, description_1) && didAllPass;
        if(!condition) {
            printf("\texpected cards = %i, got cards = %i", cards, numHandCards(&postState)); 
        }

        /**************TEST 2: unchanged game state *********************/
        mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
        condition = mem_cmp_return == 0;
        didAllPass = assertTrue(condition, description_2) && didAllPass;
        if(!condition) {
            printf("\texpected return = 0, got return = %i", mem_cmp_return); 
        }

    }

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testNumHandCards();

    if(passing) {
        printf("numHandCards(): SUCCESS - All tests passed!");
    } else {
        printf("numHandCards(): WARNING - At least one test failed");
    }
    printf("\n");

    return 0;
}
