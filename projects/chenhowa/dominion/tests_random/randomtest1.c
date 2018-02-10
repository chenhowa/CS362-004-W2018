/* Howard Chen
 * Fuzzy tester for dominion.c: adventurerEffect()
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

int checkAdventurerEffect(struct gameState* post, int player, int iteration) {

    struct gameState pre;
    int ret;
    char* description;
    int treasureDeckCount = 0;
    int treasureDiscardCount = 0;
    int i;
    int card;
    int index_1;
    int index_2;
    int tempHandSize;

    //printf("\niteration %i", iteration);

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting adventurerEffect\n");
    fflush(stdout);
    ret = adventurerEffect(post, player);
    printf("Ending adventurerEffect\n");
    fflush(stdout);
    assertEq(0, ret, "return", description);


    //Based on the pre game state, make the necessary changes
    // according to the understanding of how adventurerEffect works
    //
    // According to shuffle, the cards in the Deck are the cards that 
    // are reshuffled

    //Count the number of treasures in deck and discard, separately.
    printf("After call to FUT\n");
    fflush(stdout);
    for(i = 0; i < pre.deckCount[player]; i++) {
        card = pre.deck[player][i];
        if(cardIsTreasure(card)) {
            treasureDeckCount++; 
        } 
    }

    for(i = 0; i < pre.discardCount[player]; i++) {
        card = pre.discard[player][i];
        if(cardIsTreasure(card)) {
            treasureDiscardCount++; 
        }
    }

    // If there are 2+ treasure in deck.
    if(treasureDiscardCount >= 2) {
        printf("Case 1\n");
        fflush(stdout);
        //Then handCount increased.
        pre.handCount[player] += 2;

        //Determine indices of two treasures, and put them in hand
        index_1 = -1;
        index_2 = -1;
        for(i = pre.deckCount[player] - 1; i > -1; i--) {
            card = pre.deck[player][i];
            if(index_1 >= 0 && index_2 >= 0) {
                break; //Stop looping once two indices are found 
            }

            if(cardIsTreasure(card)) {
                if(index_1 < 0) {
                    index_1 = i; 
                } else if(index_2 < 0) {
                    index_2 = i; 
                } 
            }
        }
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][index_1];
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][index_2];

        //deckCount decreases by the size of temphand
        tempHandSize = pre.deckCount[player] - index_2;
        pre.deckCount[player] -= tempHandSize;

        //discardCount will increase by the other cards in tempHandSize.
        pre.discardCount[player] += tempHandSize - 2;
        //Trust discardCard to do its job correctly.
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
        //Check that no other changes were made when calling the FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));

        assertEq(0, ret, "memcmp return", description);

    } else if (treasureDeckCount + treasureDiscardCount >= 2) {
        printf("Case 2\n");
        fflush(stdout);
    // If treasureDeck + treasureDiscard >= 2
        //Then handCount increased.
        pre.handCount[player] += 2;
    
        index_1 = -1;
        //Determine indices of hand treasure, and put in hand
        for(i = 0; i < pre.handCount[player]; i++) {
            card = pre.hand[player][i];
            if(index_1 >= 0) {
                break; 
            }
            if(cardIsTreasure(card)) {
                index_1 = i; 
            }
        }
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][index_1];
        pre.hand[player][pre.handCount[player] - 1] = post->hand[player][pre.handCount[player] - 1];
        //Check that this card was a treasure
        description = "Top card is treasure";
        assertEq(TRUE, cardIsTreasure(pre.hand[player][pre.handCount[player] - 1]),
                "cardIsTreasure", description);
        
        //Unclear what state of discard, deck, and their counts will be
        // So just copy post's values. 
/*
        printf("Starting final test\n");
        fflush(stdout);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
        printf("Copying last memory\n");
        fflush(stdout);
        pre.deckCount[player] = post->deckCount[player];
        memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.deckCount[player]);
*/

        //Check taht no other changes were made when calling FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        assertEq(0, ret, "memcmp return", description);
        fflush(stdout);
    
    
    } else if (treasureDeckCount == 1) {
        printf("Case 3\n");
        fflush(stdout);
    // If treasureDeck == 1, then treasureDiscard == 0
        //Find the card in deck and put it in hand
        pre.handCount[player] += 1;
        for(i = 0; i < pre.handCount[player]; i++) {
            card = pre.hand[player][i];
            if(index_1 >= 0) {
                break; 
            }
            if(cardIsTreasure(card)) {
                index_1 = i; 
            }
        }
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][index_1];

        //Since at least one shuffle had to be done, state of deck, discard, and their 
        // counts is unclear. Just copy from post
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
        pre.deckCount[player] = post->deckCount[player];
        memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.deckCount[player]);

        // Check no other changes were made
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        assertEq(0, ret, "memcmp return", description);
    }
    fflush(stdout);


    return 0;

}





int main() {
    int numTests = 2000;
    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, p;
    struct gameState G;
    printf ("Testing adventurerEffect.\n");
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
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * (MAX_DECK - 5 - G.deckCount[p])); // ensure no overflow
        G.handCount[p] = floor(Random() * MAX_HAND - 5); //ensure no oveflow

        for(i = 0; i < G.deckCount[p]; i++) {
            G.deck[p][i] = floor(Random() * treasure_map); 
        }
        for(i = 0; i < G.discardCount[p]; i++) {
            G.discard[p][i] = floor(Random() * treasure_map); 
        }

        checkAdventurerEffect(&G, p, n);
    }

    printf ("ALL TESTS OK\n");



    return 0;
}
