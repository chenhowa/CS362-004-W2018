


/* Howard Chen
 * Fuzzy tester for dominion.c: minionEffect()
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

int checkMinionEffect(struct gameState* post, int player, int iteration, int handPos, int choice1, int choice2) {

    struct gameState pre;
    int ret;
    char* description;
    int otherPlayer = (player + 1) % 2;
    int expected, actual;
    int passing = TRUE;

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    if(choice1) {
        printf(" Case 1\n"); 
    }
    if(choice2) {
        printf("Case 2\n"); 
    }

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting minionEffect\n");
    fflush(stdout);
    ret = minionEffect(post, player, handPos, choice1, choice2);
    printf("Ending minionEffect\n");
    fflush(stdout);
    passing = passing * assertEq(0, ret, "return", description);

    // Regardless of choice, the number of actions should increase by 1.
    description = "Number of actions increased by 1";
    passing = passing * assertEq(pre.numActions + 1, post->numActions, "numActions", description);
    pre.numActions += 1; // corresponding change.

    if(choice1) {
        //The only state change is that the player gains 2 coins. 
        description = "Number of coins increased by 2";
        passing = passing * assertEq(pre.coins + 2, post->coins, "numCoins", description);
        pre.coins += 2;
    } else if (choice2) {
        // Depending on how many cards are in the deck vs the discard, shuffle may or 
        // may not be called. To avoid checking this too thoroughly for any of the players,
        // I will simply check that the player's hand now has 4 cards, and those 4 cards
        // came from the combination of the player's deck and discard

        description = "Player now has 4 cards in hand";
        passing = passing * assertEq(4, post->handCount[player], "handCount", description);

        description = "Player's post_discard + post_deck = pre_discard + pre_deck + pre_hand - 4";
        expected = pre.discardCount[player] + pre.deckCount[player] +
                    pre.handCount[player] - 4;
        actual = post->discardCount[player] + post->deckCount[player];
        passing = passing * assertEq(expected, actual, "total", description);
        
        // Make corresponding changes
        pre.handCount[player] = 4;
        memcpy(pre.hand[player], post->hand[player], MAX_HAND);
        pre.deckCount[player] = post->deckCount[player];
        memcpy(pre.deck[player], post->deck[player], sizeof(int) * MAX_DECK);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * MAX_DECK);
        
        if(pre.handCount[otherPlayer] > 4) {
            description = "otherPlayer now has 4 cards in hand";
            passing = passing * assertEq(4, post->handCount[otherPlayer], "handCount", description);

            description = "otherPlayer's post_discard + post_deck = pre_discard + pre_deck + pre_hand - 4";
            expected = pre.discardCount[otherPlayer] + pre.deckCount[otherPlayer] +
                        pre.handCount[otherPlayer] - 4;
            actual = post->discardCount[otherPlayer] + post->deckCount[otherPlayer];
            passing = passing * assertEq(expected, actual, "total", description);


            //Make corresponding changes
            pre.handCount[otherPlayer] = 4;
            memcpy(pre.hand[otherPlayer], post->hand[otherPlayer], MAX_HAND);
            pre.deckCount[otherPlayer] = post->deckCount[otherPlayer];
            memcpy(pre.deck[otherPlayer], post->deck[otherPlayer], sizeof(int) * MAX_DECK);
            pre.discardCount[otherPlayer] = post->discardCount[otherPlayer];
            memcpy(pre.discard[otherPlayer], post->discard[otherPlayer], sizeof(int) * MAX_DECK);
        }
        // Otherwise other player does nothing.
    }


    //regardless of either choice, check that no other changes were made.
    description = "No other changes have occurred";
    ret = memcmp(&pre, post, sizeof(struct gameState));
    passing = passing * assertEq(0, ret, "memcmp return", description);

    fflush(stdout);


    return passing;

}


int main() {
    int numTests = 2000;
    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, p;
    int otherPlayer;
    int handPos;
    int choice1, choice2;
    int passing = TRUE;
    struct gameState G;
    printf ("Testing minionEffect.\n");
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
        G.numPlayers = 2; //Set standard value of 2 to avoid any issues.
        G.deckCount[p] = floor(Random() * 50 + 1);
        G.discardCount[p] = floor(Random() * 50 + 1); // ensure no overflow
        G.handCount[p] = floor(Random() * 50 + 1); //ensure no oveflow

        G.numActions = floor(Random() * 500);
        G.coins = floor(Random() * 500);

        //Add valid cards to discard and deck
        for(i = 0; i < G.deckCount[p]; i++) {
            G.deck[p][i] = floor(Random() * treasure_map); 
        }
        for(i = 0; i < G.discardCount[p]; i++) {
            G.discard[p][i] = floor(Random() * treasure_map); 
        }

        // Choose a handPos for discarding for the player.
        handPos = floor(Random() * G.handCount[p]);

        //Choose a choice for the player. Recall that it is a binary choice.
        // between choice1 and choice 2
        choice1 = floor(Random() * 2); // 0 or 1?
        choice2 = (choice1 + 1) % 2; // Be whatever choice1 is not.  REPEAT FOR THE SECOND PLAYER
        otherPlayer = (p + 1) % 2;
        G.deckCount[otherPlayer] = floor(Random() * 50 + 1);
        G.discardCount[otherPlayer] = floor(Random() * 50 + 1); 
        G.handCount[otherPlayer] = floor(Random() * 50 + 1); 
        for(i = 0; i < G.deckCount[otherPlayer]; i++) {
            G.deck[otherPlayer][i] = floor(Random() * treasure_map); 
        }
        for(i = 0; i < G.discardCount[otherPlayer]; i++) {
            G.discard[otherPlayer][i] = floor(Random() * treasure_map); 
        }
        G.playedCardCount = floor(Random() * 12 );
        
        G.whoseTurn = p;



        passing = passing * checkMinionEffect(&G, p, n, handPos, choice1, choice2);
    }

    if(passing) {
        printf("ANNOUNCEMENT: All tests passed!"); 
    } else {
        printf("ANNOUNCEMENT: At least one test failed!");
    }



    return 0;
}
