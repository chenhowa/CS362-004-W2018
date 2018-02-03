



/* Unit test for the councilRoom card
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

    printf("TEST councilRoomEffect\n");

    /******** Test 1: Return value is correct ******/
    memcpy(&preState, &postState, sizeof(struct gameState));
    description = "Test 1: Return value is correct";
    return_value = councilRoomEffect(&postState, player, 0);
    didAllPass = assertTrue(return_value == 0, description) && didAllPass;

    description = "Test 2: Player received 4 new cards in hand";
    didAllPass = assertTrue(postState.handCount[player] == preState.handCount[player] + 4
                    , description) && didAllPass;

    description = "Test 3: Those 4 new cards are all adventurer";
    condition = postState.hand[player][postState.handCount[player] - 1] == adventurer &&
                postState.hand[player][postState.handCount[player] - 2] == adventurer &&
                postState.hand[player][postState.handCount[player] - 3] == adventurer &&
                postState.hand[player][postState.handCount[player] - 4] == adventurer; 
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 4: Player's deckCount is 4 less";
    didAllPass = assertTrue(postState.deckCount[player] == preState.deckCount[player] - 4,                      description) && didAllPass;

    description = "Test 5: Player's buy count has increased by 1";
    didAllPass = assertTrue(postState.numBuys == preState.numBuys + 1, description)
                && didAllPass;

    description = "Test 6: All the other players increased their hand count by 1";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.handCount[i] == preState.handCount[i] + 1) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 7: All the other players received an adventurer in hand";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.hand[i][postState.handCount[i] - 1] == adventurer) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 8: All the other players have 1 less card in deck";
    condition = TRUE;
    for(i = 0; i < numPlayers; i++) {
        if( i != player) {
            condition = (postState.deckCount[i] == preState.deckCount[i] - 1) &&
                        condition;
        }
    }
    didAllPass = assertTrue(condition, description) && didAllPass;


    description = "Test 9: No other changes occurred";
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
        printf("councilRoomEffect(): SUCCESS: All tests passed!");
    } else {
        printf("councilRoomEffect(): WARNING: At least one test failed");
    }
    printf("\n");

    return 0;
}
