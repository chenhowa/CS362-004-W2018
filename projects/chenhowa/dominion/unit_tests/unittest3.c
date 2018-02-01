

/* Basic non-fuzzy unit tests for dominion.c function isGameOver
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
int testIsGameOver() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int i;
    int enoughCards = 4;
    int gameOver = 1;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState, idealState;

    //First, initialize the game
    initializeGame(numPlayers, kingdomCards, seed, &postState);



    /**********  TEST 1: Game is not over if neither victory condition is satisfied */
    // First set all supplies to be 4, except province and treasure_map 
    for(i = 0; i < treasure_map + 1; i++) {
        postState.supplyCount[i] = enoughCards; 
    }
    postState.supplyCount[province] = 1;
    postState.supplyCount[treasure_map] = 1;

    //Save reset state    
    memcpy(&idealState, &postState, sizeof(struct gameState));
    
    //Save preState state
    memcpy(&preState, &postState, sizeof(struct gameState));

    // Check that the game is not over
    description = "Game is not over when conditions are not satisfied";
    didAllPass = didAllPass && assertTrue(gameOver != isGameOver(&postState), description);

    // Check that the game state was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = didAllPass && assertTrue(mem_cmp_return == 0, description);

    /*********   TEST 2: Game is over if only province pile is empty  */
    // Restore game state and adjust it.
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[province] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that the game is over 
    description = "Game is over when province supply pile is empty";
    didAllPass = didAllPass && assertTrue (gameOver == isGameOver(&postState), description);

    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = didAllPass && assertTrue(mem_cmp_return == 0, description);

    /**********  TEST 3: Games is over if only 3 supply piles are empty */
    // Restore game state and adjust it.
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[curse] = 0;
    postState.supplyCount[treasure_map] = 0;
    postState.supplyCount[council_room] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that that the game is over
    description = "Game is over when 3 supply piles are empty";
    didAllPass = didAllPass && assertTrue(gameOver == isGameOver(&postState), description);

    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = didAllPass && assertTrue(mem_cmp_return == 0, description);

    printf("\nFUCK YOU\n");

    /***********  TEST 4: Game is over if 3 piles are empty AND province is empty */
    // Restore game state and adjust it.
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[province] = 0;
    postState.supplyCount[curse] = 0;
    postState.supplyCount[treasure_map] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that that the game is over
    description = "Game is over when both conditions apply";
    didAllPass = didAllPass && assertTrue (gameOver == isGameOver(&postState), description);
    
    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = didAllPass && assertTrue(mem_cmp_return == 0, description);

    fflush(stdout);

    return didAllPass;
}


int main(int argc, char *argv[])
{
    int passing = FALSE;
    passing = testIsGameOver();

    if(passing) {
        printf("isGameOver(): SUCCESS: All tests passed!");
    } else {
        printf("isGameOver(): WARNING: At least one test failed!");
    }
    printf("\n");

    return 0;
}
