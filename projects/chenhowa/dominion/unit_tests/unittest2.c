
/* Basic non-fuzzy unit tests for dominion.c function whoseTurn
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


//Contains all tests for whoseTurn()
int testWhoseTurn() {
    //Declaration of testing-specific variables
    char *description_1;
    char *description_2;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int player;
    int maxPlayer = 5;
    int condition;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);


    description_1 = "whoseTurn returns the correct player";
    description_2 = "whoseTurn does not change the game state";

    /**************TEST 1: return value ****************************/
    for(player = 0; player <= maxPlayer; player++) {
        printf("Testing player %i\n", player);
        // Update hand count
        postState.whoseTurn = player;

        // Save the state of the game in preState
        memcpy(&preState, &postState, sizeof(struct gameState));
        condition = player == whoseTurn(&postState);
        didAllPass = assertTrue(condition, description_1) && didAllPass;
        if(!condition) {
            printf("expected player = %i, got %i", player, whoseTurn(&postState)); 
        }

        /**************TEST 2: unchanged game state *********************/
        mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
        condition = mem_cmp_return == 0;
        didAllPass = assertTrue(condition, description_2) && didAllPass;
        if(!condition) {
            printf("expected return = 0, got %i", mem_cmp_return); 
        }

    }

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testWhoseTurn();

    if(passing) {
        printf("whoseTurn(): SUCCESS: All tests passed!");
    } else {
        printf("whoseTurn(): WARNING: At least one test failed!");
    }
    printf("\n");

    return 0;
}
