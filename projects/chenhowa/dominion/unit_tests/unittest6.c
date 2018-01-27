


/* Unit test for the adventurer card
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
int testAdventurer() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int return_value;
    int player;
    int condition;
    int handCount;
    int card;
    int difference;
    int i;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, postState);


    /* THIS TEST MIGHT FAIL BECAUSE NO TREASURE CARDS WERE YET BOUGHT */

    /************** TEST 1: return value is correct *****************/
    description = "Return value is correct";
    player = postState->whoseTurn;
    memcpy(&preState, &postState, sizeof(struct gameState));
    return_value = adventurerEffect(postState, player)
    didAllPass = didAllPass && assertTrue(return_value == 0, description); 

    /************* TEST 2: handCount is greater by 2 *****************/
    description = "hand has incremented by 2 cards";
    didAllPass = didAllPass && assertTrue(
                    preState.handCount[player] + 2 == postState.handCount[player],
                        description);

    /************ TEST 3: discardCount += (x - 2), deckCount -= (x) ***/
    description = "discardCount += (x - 2), deckCount -= (x)";
    condition = (preState.deckCount[player] - postState.deckCount[player])
                == (postState.discardCount[player] - preState.discardCount[player] + 2);
    didAllPass = didAllPass && assertTrue(condition, description);

    /************ TEST 4: New cards in Player's hands are treasures ***/
    description = "Player's two new cards are Treasure cards";
    handCount = postState.handCount[player];
    card = postState.hand[player][handCount - 1];
    condition = card == copper || card == silver || card == gold;
    card = postState.hand[player][handCount - 2];
    condition = condition &&
                (card == copper || card == silver || card == gold);
    didAllPass = didAllPass && assertTrue(condition, description);

    /*********** TEST 5: No other changes occurred *****/
    description = "No other changes occurred";

    /**** To do this, I need to copy things from the preState into the
     * postState, from handcount, deckCount, and discardCount to the actual
     * cards in preState */

    /*** FINISH LATER ***/



    

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testAdventurer();

    if(passing) {
        printf("adventurerEffect(): SUCCESS: All tests passed!");
    } else {
        printf("adventurerEffect(): WARNING: At least one test failed");
    }

    return 0;
}
