
/* Basic non-fuzzy unit tests for dominion.c function whoseTurn
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
    int player;
    int maxPlayer = 30;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, postState);


    description_1 = "whoseTurn returns the correct player";
    description_2 = "whoseTurn does not change the game state";

    /**************TEST 1: return value ****************************/
    for(player = 0; player <= maxPlayer; maxPlayer++) {
        // Update hand count
        postState->whoseTurn = player;

        // Save the state of the game in preState
        memcpy(&preState, &postState, sizeof(struct gameState));

        didAllPass = didAllPass && assertTrue(cards == numHandCards(postState), description_1);
        printf("%i %s\n", player, "player")

        /**************TEST 2: unchanged game state *********************/
        mem_cmp_return = memcmp(&prestate, &postState, sizeof(struct gameState));
        didAllPass = didAllPass && assertTrue(return_value == 0, description_2);
        printf("%i %s\n", player, "player")

    }

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testNumHandCards();

    if(passing) {
        printf("SUCCESS: All tests passed!");
    } else {
        printf("WARNING: At least one test failed!");
    }

    return 0;
}
