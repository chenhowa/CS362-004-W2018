


/* Unit test for the adventurer card
 *
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


int testAdventurer() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int return_value;
    int player;
    int condition;
    int i;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState, initialState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);

    //Save the initial state of the game
    memcpy(&initialState, &postState, sizeof(struct gameState));
    player = postState.whoseTurn;

    /********** TEST 1: When top two cards in deck are Treasures copper and silver ********/
    // Set up game
    postState.deckCount[player] = 5; //To avoid tons of code, just use a deck of 5.
    for(i = 0; i < postState.deckCount[player]; i++) {
        postState.deck[player][i] = adventurer; 
    } 
    postState.deck[player][postState.deckCount[player] - 1] = copper;
    postState.deck[player][postState.deckCount[player] - 2] = silver;
    
    //Save this state for later comparison.
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 1: return value is correct";
    return_value = adventurerEffect(&postState, player);
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    description = "Test 1: player's deck has two fewer cards";
    didAllPass = assertTrue(postState.deckCount[player] == preState.deckCount[player] - 2,
                    description) && didAllPass;

    description = "Test 1: player's hand has two more cards";
    didAllPass = assertTrue(postState.handCount[player] == preState.handCount[player] + 2, 
                    description) && didAllPass;

    description = "Test 1: Those two new cards are the copper and silver";
    condition = postState.hand[player][postState.handCount[player] - 1] == silver &&
                postState.hand[player][postState.handCount[player] - 2] == copper;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 1: No other changes were made";
    preState.deckCount[player] -= 2;
    preState.handCount[player] += 2;
    preState.hand[player][preState.handCount[player] - 1] = silver;
    preState.hand[player][preState.handCount[player] - 2] = copper;
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description);

    // Restore postState to initial condition 
    memcpy(&postState, &initialState, sizeof(struct gameState));

    /*************** TEST 2: Bottom two cards are treasures silver and gold,
     *                  The top 3 are all adventurers ***/
    postState.deckCount[player] = 5;
    postState.deck[player][0] = silver;
    postState.deck[player][1] = gold;
    postState.deck[player][2] = adventurer;
    postState.deck[player][3] = adventurer;
    postState.deck[player][4] = adventurer;

    //Save state for later comparison.
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 2: Return value is correct";
    return_value = adventurerEffect(&postState, player);
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    description = "Test 2: player's hand has two more cards";
    didAllPass = assertTrue(postState.handCount[player] == preState.handCount[player] + 2, 
                    description) && didAllPass;

    description = "Test 2: Those two new cards are the gold and silver";
    condition = postState.hand[player][postState.handCount[player] - 1] == silver &&
                postState.hand[player][postState.handCount[player] - 2] == gold;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: player's deck now has no cards at all";
    didAllPass = assertTrue(postState.deckCount[player] == 0, description) && didAllPass;

    description = "Test 2: discardCount has 3 more cards";
    didAllPass = assertTrue(postState.discardCount[player] ==
                preState.discardCount[player] + 3, description) && didAllPass;
    
    description = "Test 2: the three discarded cards are all adventurers";
    condition = postState.discard[player][postState.discardCount[player] - 1] == adventurer &&
        postState.discard[player][postState.discardCount[player] - 2] == adventurer &&
        postState.discard[player][postState.discardCount[player] - 3] == adventurer;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: No other changes were made";
    preState.deckCount[player] = 0;
    preState.discardCount[player] += 3;
    preState.discard[player][preState.discardCount[player] - 1] = adventurer;
    preState.discard[player][preState.discardCount[player] - 2] = adventurer;
    preState.discard[player][preState.discardCount[player] - 3] = adventurer;
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

    //restore postState to initial state.
    memcpy(&postState, &initialState, sizeof(struct gameState));

    /***************** Test 3: 1 card (gold) in deck **********/
    postState.deckCount[player] = 5;
    for(i = 0; i < postState.deckCount[player]; i++) {
        postState.deck[player][i] = adventurer; 
    } 
    postState.deck[player][postState.deckCount[player] - 1] = gold;
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 3: Return value is correct, proving no infinite loop possible";
    return_value = adventurerEffect(&postState, player);
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    description = "Test 3: Player's handCount has increased by 1";
    didAllPass = assertTrue(postState.handCount[player] == preState.handCount[player] + 1,
                description) && didAllPass;

    description = "Test 3: The new card is the gold";
    didAllPass = assertTrue(postState.hand[player][postState.handCount[player] - 1] == gold,
                description) && didAllPass;

    //Can't test that no other changes were made or the state of the discard pile, as adventurerEffect contains shuffle,
    // which randomizes the game state a whoooole bunch

    // //restore postState to initial state.
    memcpy(&postState, &initialState, sizeof(struct gameState));

    /*************** Test 4: 1 card (copper) in deck, 1 card (gold) in discard pile **/
    postState.deckCount[player] = 5;
    for(i = 0; i < postState.deckCount[player]; i++) {
        postState.deck[player][i] = adventurer; 
    } 
    postState.deck[player][postState.deckCount[player] - 1] = copper;
    postState.discardCount[player] = 1;
    postState.discard[player][0] = gold;
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 4: Return value is correct, proving no infinite loop possible";
    return_value = adventurerEffect(&postState, player);
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    description = "Test 4: Player's handCount has increased by 2";
    didAllPass = assertTrue(postState.handCount[player] == preState.handCount[player] + 2,
                description) && didAllPass;

    description = "Test 4: The new cards are the gold and copper";
    condition = postState.hand[player][postState.handCount[player] - 1] == gold &&
                postState.hand[player][postState.handCount[player] - 2] == copper;
    didAllPass = assertTrue(condition, description) && didAllPass;

    /* Can't test discard pile or that no other changes were made, as the shuffle function in adventurerEffect randomizes the game state a wwhoooooole bunch 
     */

    // //restore postState to initial state.
    memcpy(&postState, &initialState, sizeof(struct gameState));

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
    printf("\n");

    return 0;
}
