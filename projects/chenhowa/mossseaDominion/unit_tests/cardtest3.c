



/* Unit test for the councilRoom card
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



int testCouncilRoom() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int return_value;
    int player;
    int condition;
    int i;
    int numPlayers = 4;

    //Declarations to initialize game
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState, initialState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);

    //Save the initial state of the game
    memcpy(&initialState, &postState, sizeof(struct gameState));
    player = postState.whoseTurn;

    // Initial set up of game.
    postState.deckCount[player] = 4;
    for(i = 0; i < postState.deckCount[player]; i++) {
        postState.deck[player][i] = adventurer;  //Set deck to all adventurers; 
    }

    //Give remaining 4 players a single adventurer on top of their deck
    postState.numPlayers = numPlayers;
    for(i = 0; i < postState.numPlayers; i++) {
        if(i != player) {
            postState.deckCount[i] = 4;
            postState.deck[i][postState.deckCount[i] - 1] = adventurer;
        } 
    }

    printf("\nTESTING councilRoom\n");

    /***** TEST 1 ***/
    memcpy(&preState, &postState, sizeof(struct gameState));
    description = "Return value is correct";
    return_value = cardEffect(council_room, -1, -1, -1, &postState, 0, 0);
    condition = return_value == 0;
    didAllPass = assertTrue(condition , description) && didAllPass;
    if(!condition) {
        logMisMatch("return", 0, return_value); 
    }

    description = "Player received 4 new cards in hand";
    condition = postState.handCount[player] == preState.handCount[player] + 4;
    didAllPass = assertTrue(condition , description) && didAllPass;
    if(!condition) {
        logMisMatch("count", preState.handCount[player] + 4, postState.handCount[player]); 
    }

    description = "Those 4 new cards are all adventurer";
    condition = postState.hand[player][postState.handCount[player] - 1] == adventurer &&
                postState.hand[player][postState.handCount[player] - 2] == adventurer &&
                postState.hand[player][postState.handCount[player] - 3] == adventurer &&
                postState.hand[player][postState.handCount[player] - 4] == adventurer; 
    didAllPass = assertTrue(condition, description) && didAllPass;
    if(!condition) {
        logMisMatch("top card", adventurer, postState.hand[player][postState.handCount[player] - 1]); 
        logMisMatch("second card", adventurer, postState.hand[player][postState.handCount[player] - 2]); 
        logMisMatch("third card", adventurer, postState.hand[player][postState.handCount[player] - 3]); 
        logMisMatch("fourth card", adventurer, postState.hand[player][postState.handCount[player] - 4]); 
    }

    description = "Player's deckCount is 4 less";
    condition = postState.deckCount[player] == preState.deckCount[player] - 4;
    didAllPass = assertTrue(condition , description) && didAllPass;
    if(!condition) {
        logMisMatch("count", preState.deckCount[player] - 4, postState.deckCount[player]); 
    }

    description = "Player's buy count has increased by 1";
    condition = postState.numBuys == preState.numBuys + 1;
    didAllPass = assertTrue(condition , description)
                && didAllPass;
    if(!condition) {
        logMisMatch("buys", preState.numBuys + 1, postState.numBuys);    
    }

    description = "All the other players increased their hand count by 1";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.handCount[i] == preState.handCount[i] + 1) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "All the other players received an adventurer in hand";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.hand[i][postState.handCount[i] - 1] == adventurer) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "All the other players have 1 less card in deck";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.deckCount[i] == preState.deckCount[i] - 1) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;


    description = "No other changes occurred";
    //Make the only changes that should have occurred to preState.
    preState.handCount[player] += 4;
    preState.hand[player][preState.handCount[player] - 1] = adventurer;
    preState.hand[player][preState.handCount[player] - 2] = adventurer;
    preState.hand[player][preState.handCount[player] - 3] = adventurer;
    preState.hand[player][preState.handCount[player] - 4] = adventurer;
    preState.deckCount[player] -= 4;
    preState.numBuys += 1;

    for(i = 0; i < numPlayers; i++) {
        if( i != player ) {
            preState.handCount[i] += 1; 

            preState.hand[i][preState.handCount[i] - 1] = adventurer;

            preState.deckCount[i] -= 1;
        } 
    }

    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    condition = mem_cmp_return == 0;
    didAllPass = assertTrue(condition, description) && didAllPass;

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testCouncilRoom();

    if(passing) {
        printf("councilRoom(): SUCCESS: All tests passed!");
    } else {
        printf("councilRoom(): WARNING: At least one test failed");
    }
    printf("\n\n");

    return 0;
}
