
/* Howard Chen
 * Fuzzy tester for dominion.c: smithyEffect()
 *
 *
 */
#include "../assertions.h"
#include "../dominion.h"
#include "../dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "../rngs.h"
#include <math.h>

int cardIsTreasure(int card) {
    if(card == gold || card == silver || card == copper) {
        return TRUE; 
    }
    return FALSE;
}

int checkSmithyEffect(struct gameState* post, int player, int iteration) {

    struct gameState pre;
    int ret;
    char* description;
    int passing = TRUE;

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    if(pre.deckCount[player] >= 3) {
        printf(" Case 1\n");
    }
    else if (pre.deckCount[player] + pre.discardCount[player] >= 3) {
        printf(" Case 2\n");
    } else {
        printf(" Case 3: Very few cards in deck and discard. Not important\n");
    }

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting smithyEffect\n");
    fflush(stdout);
    ret = smithyEffect(post, player);
    printf("Ending smithyEffect\n");
    fflush(stdout);
    passing = passing * assertEq(0, ret, "return", description);

    //Based on the pre game state, make the necessary changes
    // according to the understanding of how smithyEffect works
    if(pre.deckCount[player] >= 3) {
        description = "Player's hand count increased by 3";
        passing = passing * assertEq(pre.handCount[player] + 3, post->handCount[player], "handCount", description);
        description = "Player's top hand card is correct";
        passing = passing * assertEq(pre.deck[player][pre.deckCount[player] - 3], 
                    post->hand[player][post->handCount[player] - 1],
                    "card id", description);
        description = "Player's second hand card is correct";
        passing = passing * assertEq(pre.deck[player][pre.deckCount[player] - 2], 
                    post->hand[player][post->handCount[player] - 2],
                    "card id", description);
        description = "Player's third hand card is correct";
        passing = passing * assertEq(pre.deck[player][pre.deckCount[player] - 1], 
                    post->hand[player][post->handCount[player] - 3],
                    "card id", description);

        description = "Player's deckCount decreased by 3";
        passing = passing * assertEq(pre.deckCount[player] - 3, post->deckCount[player], "deckCount", description);

        //Make corresponding changes.
        pre.handCount[player] += 3;
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][pre.deckCount[player] - 3];
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][pre.deckCount[player] - 2];
        pre.hand[player][pre.handCount[player] - 3] = pre.deck[player][pre.deckCount[player] - 1];
        pre.deckCount[player] -= 3;

        //Other than this, no other changes should have been made to the game.
        description = "No other changes were made to the game";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        passing = passing * assertEq(0, ret, "memcmp return", description);
    
    } else if (pre.deckCount[player] + pre.discardCount[player] >= 3) {
        //If the deck is mostly empty because much of it is in the
        // discard, we cannot be sure which cards will end up in smithy's hand,
        // or what the final states of the deck and discard will be. 
        // So we have to trust drawCard here.
        description = "Player's hand count increased by 3";
        passing = passing * assertEq(pre.handCount[player] + 3, post->handCount[player], "handCount", description);
        description = "Shuffle occurred, so discard should now be empty";
        passing = passing * assertEq(0, post->discardCount[player], "discardCount", description);

        //make corresponding changes
        pre.handCount[player] += 3;
        pre.hand[player][pre.handCount[player] - 1] = post->hand[player][post->handCount[player] - 1];
        pre.hand[player][pre.handCount[player] - 2] = post->hand[player][post->handCount[player] - 2];
        pre.hand[player][pre.handCount[player] - 3] = post->hand[player][post->handCount[player] - 3];
        pre.deckCount[player] = pre.deckCount[player] + pre.discardCount[player] - 3;
        memcpy(pre.deck[player], post->deck[player], MAX_DECK);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], MAX_DECK);

        description = "No other changes were made to game";
        ret= memcmp(&pre, post, sizeof(struct gameState));
        passing = passing * assertEq(0, ret, "memcmp return", description);
    
    } else {
        // Otherwise the deck and discard started with with very, very few cards,
        // which would not occur in a real game of dominion.
        // This is not an important case.
        //
    }

    fflush(stdout);


    return passing;

}





int main() {
    int numTests = 2000;
    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, p;
    struct gameState G;
    int passing = TRUE;
    printf ("Testing smithyEffect.\n");
    printf ("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);
    for (n = 0; n < numTests; n++) {
        printf("iteration %i: ", n);
        fflush(stdout);
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * (MAX_DECK));
        G.discardCount[p] = floor(Random() * (MAX_DECK - 5 - G.deckCount[p])); // ensure no overflow
        G.handCount[p] = floor(Random() * (MAX_HAND - 5)); //ensure no oveflow

        //Add valid cards to discard and deck
        for(i = 0; i < G.deckCount[p]; i++) {
            G.deck[p][i] = floor(Random() * treasure_map); 
        }
        for(i = 0; i < G.discardCount[p]; i++) {
            G.discard[p][i] = floor(Random() * treasure_map); 
        }

        //Make the played card count reasonable.
        G.playedCardCount = floor(Random() * (MAX_DECK - 5));

        passing = passing * checkSmithyEffect(&G, p, n);
    }

    if(passing) {
        printf("ANNOUNCEMENT: All tests passed!"); 
    } else {
        printf("ANNOUNCEMENT: At least one test failed!");
    }


    return 0;
}
