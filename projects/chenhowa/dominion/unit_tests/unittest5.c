

/* Unit test for the smithy card
 *
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
int testSmithy() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int numHand;
    int numDeck;
    int player;
    int return_value;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, postState);


    /************  TEST 1: return value is correct *****/
    description = "Return value is 0";
    //First, save preState and relevant values.
    memcpy(&preState, &postState, sizeof(struct gameState));
    player = postState->whoseTurn;
    numDeck = postState->deckCount[player];
    numHand = postState->handCount[player];

    return_value = smithyEffect(postState, player, 1); 

    didAllPass = didAllPass && assertTrue(return_value == 0, description1);

    /***********   TEST 2: player received 3 extra card in hand ****/
    description = "Player received 3 extra cards";
    didAllPass = didAllPass && assertTrue(numHand + 3 == postState->handCount[player],
                    description);


    /**********    TEST 3: The 3 extra cards came from the player's own deck ****/
    description = "The 3 cards came from the player's deck";
    didAllPass = didAllPass && assertTrue(numDeck - 3 == postState->deckCount[player], 
            description);

    /*********    Test 4: No other changes were made to the game state ****/
    description = "No other changes were made to the game state";
    preState->deckCount[player] -= 3;
    preState->handcount[player] += 3;
    mem_cmp_return = memcmp(&preState, postState, sizeof(struct gameState));
    didAllPass = didAllPass && assertTrue(mem_cmp_return == 0, description);

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testSmithy();

    if(passing) {
        printf("smithyEffect(): SUCCESS: All tests passed!");
    } else {
        printf("smithEffect(): WARNING: At least one test failed");
    }

    return 0;
}
