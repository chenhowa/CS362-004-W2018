

/* Unit test for the smithy card
 *
 *
 *
 */

#include "../logMismatch.h"
#include "../dominion.h"
#include "../dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "../assertions.h"
#include "../rngs.h"
#include <stdlib.h>


int testSmithy() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int numHand;
    int numDeck;
    int player;
    int return_value;
    int cardsCorrect = FALSE;
    int condition;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);
    player = postState.whoseTurn;

    //Make sure player has enough cards
    postState.deckCount[player] = 5;
    postState.deck[player][postState.deckCount[player] - 1] = adventurer;
    postState.deck[player][postState.deckCount[player] - 2] = adventurer;
    postState.deck[player][postState.deckCount[player] - 3] = adventurer;

    //First, save preState and relevant values.
    memcpy(&preState, &postState, sizeof(struct gameState));
    numDeck = postState.deckCount[player];
    numHand = postState.handCount[player];

    printf("\nTESTING smithy\n");
    /************  TEST 1: return value is correct *****/
    description = "Return value is 0";
    return_value = smithyPlay(-1, -1, -1, &postState, 1, 0);
    condition = return_value == 0;
    didAllPass = assertTrue(condition , description) && didAllPass;
    if(!condition) {
        logMisMatch("return", 0, return_value); 
    }

    /***********   TEST 2: player received 3 extra card in hand ****/
    //Assumes drawCard works correctly
    description = "Player received 3 extra cards";
    condition = numHand + 3 == postState.handCount[player];
    didAllPass = assertTrue(condition ,
                    description) && didAllPass;
    if(!condition) {
        logMisMatch("cards", numHand + 3, postState.handCount[player]); 
    }

    /**********    TEST 3: The 3 extra cards came from the player's own deck ****/
    //Assumes drawCard works correctly
    description = "The 3 cards came from the player's deck";
    condition = numDeck - 3 == postState.deckCount[player];
    didAllPass = assertTrue(condition , 
            description) && didAllPass;
    if(!condition) {
        logMisMatch("cards", numDeck - 3, postState.deckCount[player]); 
    }

    /*********     TEST 4: The 3 extra cards in hand are the correct cards ****/
    description = "The 3 cards in hand are the correct cards";
    cardsCorrect = postState.hand[player][postState.handCount[player] - 1] == adventurer &&
                    postState.hand[player][postState.handCount[player] - 2] == adventurer &&
                    postState.hand[player][postState.handCount[player] - 3] == adventurer;
    didAllPass = assertTrue(cardsCorrect, description) && didAllPass;
    if(! cardsCorrect) {
        logMisMatch("top card", adventurer, postState.hand[player][postState.handCount[player] - 1]); 
        logMisMatch("middle card", adventurer, postState.hand[player][postState.handCount[player] - 2]); 
        logMisMatch("bottom card", adventurer, postState.hand[player][postState.handCount[player] - 3]); 
    }

    /*********    Test 5: No other changes were made to the game state ****/
    description = "No other changes were made to the game state";
    preState.deckCount[player] -= 3;  //decrease cards in deck
    preState.handCount[player] += 3;  // increase cards in hand
    preState.hand[player][preState.handCount[player] - 1] = adventurer;
    preState.hand[player][preState.handCount[player] - 2] = adventurer;
    preState.hand[player][preState.handCount[player] - 3] = adventurer;
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

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
    printf("\n\n");

    return 0;
}
