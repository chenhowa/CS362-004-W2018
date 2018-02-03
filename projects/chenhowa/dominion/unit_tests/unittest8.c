




/* Unit test for the minionEffect function
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


int testMinion() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int return_value;
    int player;
    int condition;
    int i;
    int j;
    int numPlayers = 3;
    int choice1;
    int choice2;
    int count;

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

    printf("TEST minionEffect\n");
    /*********** TEST 1: choice 1 *****************/
    //initial set-up.
    choice1 = 1;
    choice2 = 0;
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 1: return value is correct";
    return_value = minionEffect(&postState, player, 0, choice1, choice2);
    condition = return_value == 0;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 1: player has gained 2 coins";
    condition = postState.coins == preState.coins + 2;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 1: player has gained an action";
    condition = postState.numActions == preState.numActions + 1;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 1: Nothing else has changed";
    preState.coins += 2;
    preState.numActions += 1;
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    condition = mem_cmp_return == 0;
    didAllPass = assertTrue(condition, description) && didAllPass;

    //Restore game to initial state.
    memcpy(&postState, &initialState, sizeof(struct gameState));

    /********** TEST 2: choice 2, 2 other players have > 4 cards, 1 has <= 4 cards */
    //Set up test.
    postState.whoseTurn = postState.numPlayers - 1;
    player = postState.whoseTurn;
    choice1 = 0;
    choice2 = 1;
    postState.handCount[player] = 3; //Give player a hand of 3 cards
    postState.hand[player][0] = adventurer;
    postState.hand[player][1] = minion;
    postState.hand[player][2] = adventurer;
    postState.deckCount[player] = 4; //Give player a deck of all smithies.
    for(i = 0; i < postState.deckCount[player]; i++) {
        postState.deck[player][i] = smithy; 
    }

    //Give most other players a hand of 5 cards, all adventurers
    // Give all players a deck of 4 smithy
    for(i = 0; i < postState.numPlayers - 1; i++) {
        if(i != player) {
            postState.handCount[i] = 5; 

            for(j = 0; j < postState.handCount[i]; j++) {
                postState.hand[i][j] = adventurer;
            }

            postState.deckCount[i] = 4;
            for(j = 0; j < postState.deckCount[i]; j++) {
                postState.deck[i][j] = smithy; 
            }
        } 
    }

    //Give one player a hand of 6 adventurers
    postState.handCount[0] += 1;
    postState.hand[0][postState.handCount[0] - 1] = adventurer;

    //Give one player a hand of just 4 adventurers;
    postState.handCount[1] -= 1;

    //Save preState.
    memcpy(&preState, &postState, sizeof(struct gameState));

    description = "Test 2: Return value is correct";
    return_value = minionEffect(&postState, player, 0, choice1, choice2);
    condition = return_value == 0;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: player's handCount is now 4";
    condition = postState.handCount[player] == 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: player's hand is now full of smithy";
    condition = TRUE;
    for(i = 0; i < postState.handCount[player]; i++) {
        condition = (postState.hand[player][i] == smithy) && condition; 
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: Player's deck is now 4 less";
    condition = postState.deckCount[player] == preState.deckCount[player] - 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: Player's discard is now 3 more";
    condition = postState.discardCount[player] == preState.discardCount[player] + 3;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 2: Player's top of discard consists of adventurer, minion, adventurer";
    condition = postState.discard[player][postState.discardCount[player] - 1] == adventurer &&
            postState.discard[player][postState.discardCount[player] - 2] == minion &&
            postState.discard[player][postState.discardCount[player] - 3] == adventurer; 
    didAllPass = assertTrue(condition, description) && didAllPass;
    
    description = "Test 2: player has gained an action";
    condition = postState.numActions == preState.numActions + 1;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 3: Other with 5 cards in hand has handCount of 4";
    player = 2;
    condition = postState.handCount[player] == 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 3: Other with 5 cards has hand full of smithy";
    condition = TRUE;
    for(i = 0; i < postState.handCount[player]; i++) {
        condition = (postState.hand[player][i] == smithy) && condition; 
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 3: Other with 5 cards has deck with 4 less";
    condition = postState.deckCount[player] == preState.deckCount[player] - 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 3: Other with 5 cards has discard with 5 more";
    condition = postState.discardCount[player] == preState.discardCount[player] + 5;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 3: Other with 5 cards has discard pile gained 5 adventurers";
    count = postState.discardCount[player];
    condition = TRUE;
    for(i = count - 5; i < count; i++) {
        condition = (postState.discard[player][i] == adventurer) && condition; 
    }

    description = "Test 4: Other with 6 cards in hand has handCount of 4";
    player = 0;
    condition = postState.handCount[player] == 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 4: Other with 6 cards has hand full of smithy";
    condition = TRUE;
    for(i = 0; i < postState.handCount[player]; i++) {
        condition = (postState.hand[player][i] == smithy) && condition; 
    }
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 4: Other with 6 cards has deck with 4 less";
    condition = postState.deckCount[player] == preState.deckCount[player] - 4;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 4: Other with 6 cards has discard with 6 more";
    condition = postState.discardCount[player] == preState.discardCount[player] + 6;
    didAllPass = assertTrue(condition, description) && didAllPass;

    description = "Test 4: Other with 6 cards has discard pile gained 6 adventurers";
    count = postState.discardCount[player];
    condition = TRUE;
    for(i = count - 6; i < count; i++) {
        condition = (postState.discard[player][i] == adventurer) && condition; 
    }

    /* FINAL CHECK */
    description = "Test 5: No other changes occurred: other with 4 cards in hand experienced no effects";
    player = postState.numPlayers - 1; //Restore changes to original player
    preState.handCount[player] = 4;
    for(i = 0; i < preState.handCount[player]; i++) {
        preState.hand[player][i] = smithy; 
    }
    preState.deckCount[player] -= 4;
    preState.discardCount[player] += 3;
    count = preState.discardCount[player];
    preState.deck[player][count - 1]  = adventurer;
    preState.deck[player][count - 2]  = minion;
    preState.deck[player][count - 3]  = adventurer;
    preState.numActions += 1; //player gained an action

    //Restore changes to player with 5 cards
    player = 2; 
    preState.handCount[player] = 4;
    for(i = 0; i < preState.handCount[player]; i++) {
        preState.hand[player][i] = smithy; 
    }
    preState.deckCount[player] -= 4;
    preState.discardCount[player] += 5;
    count = preState.discardCount[player];
    for(i = count - 5; i < count; i++) {
        preState.discard[player][i] = adventurer; 
    }

    //Restore changes to player with 6 cards
    player = 0; 
    preState.handCount[player] = 4;
    for(i = 0; i < preState.handCount[player]; i++) {
        preState.hand[player][i] = smithy; 
    }
    preState.deckCount[player] -= 4;
    preState.discardCount[player] += 6;
    count = preState.discardCount[player];
    for(i = count - 6; i < count; i++) {
        preState.discard[player][i] = adventurer; 
    }

    //Compare to see if no changes
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    condition = mem_cmp_return == 0;
    didAllPass = assertTrue(condition, description) && didAllPass;

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testMinion();

    if(passing) {
        printf("minionEffect(): SUCCESS: All tests passed!");
    } else {
        printf("minionEffect(): WARNING: At least one test failed");
    }
    printf("\n");

    return 0;
}
