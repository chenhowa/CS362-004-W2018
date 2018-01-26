/* Basic non-fuzzy unit tests for dominion.c function numHandCards
 *
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "assertions.h"
#include "rngs.h"
#include <stdlib.h>


//Contains all tests for numHandCards()
int testNumHandCards() {
    //Declaration of testing-specific variables
    char *description_1;
    char *description_2;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int maxHandCards = 20;
    int cards;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, postState);


    description_1 = "numHandCards returns the correct number of cards";
    description_2 = "numHandCards does not change the game state";

    /**************TEST 1: return value ****************************/
    for(cards = 0; cards <= maxHandCards; cards++) {
        // Update hand count
        postState->handCount[ whoseTurn(postState) ] = cards;

        // Save the state of the game in preState
        memcpy(&preState, &postState, sizeof(struct gameState));

        didAllPass = didAllPass && assertTrue(cards == numHandCards(postState), description_1);
        printf("%i %s\n", cards, "cards")

        /**************TEST 2: unchanged game state *********************/
        mem_cmp_return = memcmp(&prestate, &postState, sizeof(struct gameState));
        didAllPass = didAllPass && assertTrue(return_value == 0, description_2);
        printf("%i %s\n", cards, "cards")

    }

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testNumHandCards();

    if(passing) {
        printf("All tests passed!");
    } else {
        printf("One test did not pass");
    }

    return 0;
}
