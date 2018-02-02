


/* Basic non-fuzzy unit tests for dominion.c function discardCard()
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
int testDiscardCard() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int i;
    int trashFlag;
    int player;
    int discardedCard;
    int lastCard;
    int handPos;
    int return_value;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState, idealState;

    //First, initialize the game
    memset(&postState, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, kingdomCards, seed, &postState);
    memcpy(&idealState, &postState, sizeof(struct gameState));

    /************* Test 1: trash, large hand, discard NOT last card *****/
    memcpy(&postState, &idealState, sizeof(struct gameState));
    // Set the player up with a hand of 5 cards;
    player = postState.whoseTurn;
    postState.handCount[player] = 5;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }
    // First, save prestate.
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Set remaining parameters
    handPos = 0;
    trashFlag = 1;

    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 1: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Check that changing preState turns it into postState
    preState.hand[player][handPos] = lastCard;
    preState.hand[player][preState.handCount[player] - 1] = -1;
    preState.handCount[player]--;

    description = "Test 1: No undesired changes were made to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    /************ TEST 2: trash, 1 card, discard 1 card ******/
    memcpy(&postState, &idealState, sizeof(struct gameState));

    //Set the player with a hand of just 1 card.
    postState.handCount[player] = 1;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }

    memcpy(&preState, &postState, sizeof(struct gameState));
    //Set remaining parameters 
    handPos = 0;
    trashFlag = 1;

    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 2: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Take a card away from preState.
    preState.handCount[player]--;
    preState.hand[player][preState.handCount[player]] = -1;

    description = "Test 2: No undesired changes were made to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    /************ TEST 3: trash, large hand, discard last card */
    memcpy(&postState, &idealState, sizeof(struct gameState));

    postState.handCount[player] = 5;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }

    memcpy(&preState, &postState, sizeof(struct gameState));
    //Set remaining parameters 
    handPos = postState.handCount[player] - 1;
    trashFlag = 1;
    
    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 3: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Take last hand card away from preState.
    preState.handCount[player]--;
    preState.hand[player][preState.handCount[player]] = -1;

    description = "Test 3: No undesired changes were made to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);


    /************* Test 4: no trash, large hand, discard NOT last card *****/
    memcpy(&postState, &idealState, sizeof(struct gameState));
    // Set the player up with a hand of 5 cards;
    player = postState.whoseTurn;
    postState.handCount[player] = 5;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }
    // First, save prestate.
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Set remaining parameters
    handPos = 0;
    trashFlag = 0;

    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 4: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Check that changing preState turns it into postState
    preState.hand[player][handPos] = lastCard;
    preState.hand[player][preState.handCount[player] - 1] = -1;
    preState.handCount[player]--;

        //Put the discarded card in the played pile
    preState.playedCards[preState.playedCardCount] = discardedCard;
    preState.playedCardCount++;

    description = "Test 4: No undesired changes were made to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    /************ TEST 5: no trash, 1 card, discard 1 card ******/
    memcpy(&postState, &idealState, sizeof(struct gameState));

    //Set the player with a hand of just 1 card.
    postState.handCount[player] = 1;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }

    memcpy(&preState, &postState, sizeof(struct gameState));
    //Set remaining parameters 
    handPos = 0;
    trashFlag = 0;

    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 5: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Take a card away from preState.
    preState.handCount[player]--;
    preState.hand[player][preState.handCount[player]] = -1;

    //Put it in the played pile
    preState.playedCards[preState.playedCardCount] = discardedCard;
    preState.playedCardCount++;

    description = "Test 5: No undesired changes were made to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    /************ TEST 6: NO trash, large hand, discard last card */
    memcpy(&postState, &idealState, sizeof(struct gameState));

    postState.handCount[player] = 5;
    for(i = 0; i < postState.handCount[player]; i++) {
        postState.hand[player][i] = adventurer;
    }

    memcpy(&preState, &postState, sizeof(struct gameState));
    //Set remaining parameters 
    handPos = postState.handCount[player] - 1;
    trashFlag = 0;
    
    //Save important values for testing
    discardedCard = postState.hand[player][handPos];
    lastCard = postState.hand[player][postState.handCount[player] - 1];

    //Verify return value
    return_value = discardCard(handPos, player, &postState, trashFlag);
    description = "Test 6: Return value is correct";
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    //Take last hand card away from preState.
    preState.handCount[player]--;
    preState.hand[player][preState.handCount[player]] = -1;

    //Put it in the played pile
    preState.playedCards[preState.playedCardCount] = discardedCard;
    preState.playedCardCount++;

    description = "Test 6: No undesired changes were mae to the game";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    fflush(stdout);

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testDiscardCard();

    if(passing) {
        printf("discardCard(): SUCCESS: All tests passed!");
    } else {
        printf("discardCard(): WARNING: At least one test failed!");
    }
    printf("\n");

    return 0;
}
