

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


int testIsGameOver() {
    //Declaration of testing-specific variables
    char *description;
    int mem_cmp_return;
    int didAllPass = TRUE;
    int i;
    int enoughCards = 4;
    int gameOver = 1;
    int condition;

    //Declarations to initialize game
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int seed = 100;
    struct gameState preState, postState, idealState;

    //First, initialize the game
    memset(&postState, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, kingdomCards, seed, &postState);



    printf("\nTESTING isGameOver\n");
    /**********  TEST 1: Game is not over if neither victory condition is satisfied */
    // First set all supplies to be 4, except province and treasure_map 
    printf("*************Test 1: Neither condition is satisfied\n");
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
    condition = gameOver != isGameOver(&postState);
    didAllPass = assertTrue(condition, description) && didAllPass;
    if(!condition) {
        printf("\texpected gameOver = %i got %i\n", FALSE, isGameOver(&postState) );
    }

    // Check that the game state was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

    /*********   TEST 2: Game is over if only province pile is empty  */
    // Restore game state and adjust it.
    printf("*************Test 2: Province pile is empty\n");
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[province] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that the game is over 
    description = "Game is over when province supply pile is empty";
    condition = gameOver == isGameOver(&postState);
    didAllPass = assertTrue (condition, description) && didAllPass;
    if(!condition) {
        printf("\texpected gameOver = %i, got %i\n", TRUE, isGameOver(&postState)); 
    }

    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

    /**********  TEST 3: Games is over if only 3 supply piles are empty */
    // Restore game state and adjust it.
    printf("*************Test 3: Supply piles are empty\n");
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[curse] = 0;
    postState.supplyCount[treasure_map] = 0;
    postState.supplyCount[council_room] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that that the game is over
    description = "Game is over when 3 supply piles are empty";
    condition = gameOver == isGameOver(&postState);
    didAllPass = assertTrue(condition, description) && didAllPass;
    if(!condition) {
        printf("\texpected gameOver = %i, got %i\n", TRUE, isGameOver(&postState)); 
    }

    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

    /***********  TEST 4: Game is over if 3 piles are empty AND province is empty */
    // Restore game state and adjust it.
    printf("*************Test 4: 3 piles are empty AND province pile is empty\n");
    memcpy(&postState, &idealState, sizeof(struct gameState));
    postState.supplyCount[province] = 0;
    postState.supplyCount[curse] = 0;
    postState.supplyCount[treasure_map] = 0;

    //Save the state
    memcpy(&preState, &postState, sizeof(struct gameState));

    //Check that that the game is over
    description = "Game is over when both conditions apply";
    condition = gameOver == isGameOver(&postState);
    didAllPass = assertTrue (condition, description) && didAllPass;
    if(!condition) {
        printf("\texpected gameOver = %i, got %i\n", TRUE, isGameOver(&postState)); 
    }
    
    //Check that the game was not changed
    description = "Game state was not changed";
    mem_cmp_return = memcmp(&preState, &postState, sizeof(struct gameState));
    didAllPass = assertTrue(mem_cmp_return == 0, description) && didAllPass;

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
    printf("\n\n");

    return 0;
}
