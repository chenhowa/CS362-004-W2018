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
    int expected, actual;
    int passing = TRUE;

    //printf("\niteration %i", iteration);

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    //Count the number of treasures in preState's deck and discard, separately.
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

    if(treasureDiscardCount >= 2) {
        printf("  Case 1\n");
    }
    else if ((treasureDeckCount + treasureDiscardCount) >= 2) {
        printf("  Case 2\n");
    } else if ((treasureDeckCount + treasureDiscardCount) == 1) {
        printf("  Case 3\n");
    } else if ((treasureDeckCount + treasureDiscardCount) == 0) {
        // This behavior is undefined? 
        printf("  Case 4\n");
    }

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting adventurerEffect\n");
    fflush(stdout);
    ret = adventurerEffect(post, player);
    printf("Ending adventurerEffect\n");
    fflush(stdout);
    passing = passing * assertEq(0, ret, "return", description);


    //Based on the pre game state, make the necessary changes
    // according to the understanding of how adventurerEffect works
    //
    // According to shuffle, the cards in the Deck are the cards that 
    // are reshuffled


    // If there are 2+ treasure in deck.
    if(treasureDiscardCount >= 2) {
        //Then handCount increased by 2.
        description = "player's hand increased by 2";
        passing = passing * assertEq(pre.handCount[player] + 2, post->handCount[player], "handCount", description);
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
                    index_1 = i;  //top card in deck is index_1
                } else if(index_2 < 0) {
                    index_2 = i;  //second card in deck is index_2 
                } 
            }
        }
        description = "player's top hand card is correct";
        passing = passing * assertEq(pre.deck[player][index_2],
                    post->hand[player][post->handCount[player] - 1],
                    "card id", description);
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][index_2];

        description = "player's second hand card is correct";
        passing = passing * assertEq(pre.deck[player][index_1],
                    post->hand[player][post->handCount[player] - 2],
                    "card id", description);
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][index_1];

        //deckCount decreases by the size of temphand and the 2 Treasures
        tempHandSize = pre.deckCount[player] - index_2 - 2;
        description = "deckCount decreased by the number of cards drawn";
        passing = passing * assertEq(pre.deckCount[player] - tempHandSize - 2,
                post->deckCount[player],
                "deckCount", description);
        pre.deckCount[player] -= tempHandSize;

        //discardCount will increase by the other cards in tempHandSize.
        description = "discardCount increases by only the size of tempHand";
        passing = passing * assertEq(pre.discardCount[player] + tempHandSize,
                post->discardCount[player],
                "discardCount", description);
        pre.discardCount[player] += tempHandSize;

        //Trust discardCard to do its job correctly.
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
        //Check that no other changes were made when calling the FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        passing = passing * assertEq(0, ret, "memcmp return", description);

    } else if ((treasureDeckCount + treasureDiscardCount) >= 2) {
        // If treasureDeck + treasureDiscard >= 2
        //Then handCount increased.
        description = "player's hand increased by 2";
        passing = passing * assertEq(pre.handCount[player] + 2, post->handCount[player], "handCount", description);
        pre.handCount[player] += 2;
    
        index_1 = -1;
        //Determine indices of hand treasure, and put in hand
        for(i = 0; i < pre.deckCount[player]; i++) {
            card = pre.deck[player][i];
            if(index_1 >= 0) {
                break; 
            }
            if(cardIsTreasure(card)) {
                index_1 = i; 
            }
        }
        description = "Second card in hand is correct";
        passing = passing * assertEq(pre.deck[player][index_1],
                post->hand[player][post->handCount[player] - 2],
                "card id", description);
        //Make corresponding changes to preState.
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][index_1];
        pre.hand[player][pre.handCount[player] - 1] = post->hand[player][post->handCount[player] - 1];
        //Check that the top two cards are treasure
        description = "Top card is treasure";
        passing = passing * assertEq(TRUE, cardIsTreasure(post->hand[player][post->handCount[player] - 1]),
                "cardIsTreasure", description);
        description = "Second card is treasure";
        passing = passing * assertEq(TRUE, cardIsTreasure(post->hand[player][post->handCount[player] - 2]),
                "cardIsTreasure", description);

        //Check that deck + discard has only decreased by 2
        description = "deck + discard has only decreased by 2";
        expected = pre.deckCount[player] + pre.discardCount[player] - 2;
        actual = post->deckCount[player] + post->discardCount[player];
        passing = passing * assertEq(expected, actual, "deck + discard", description);
        
        //Unclear what state of discard, deck, and their counts will be
        // So just copy post's values. 

        printf("Starting final test\n");
        fflush(stdout);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], MAX_DECK);
        printf("Copying last memory\n");
        fflush(stdout);
        pre.deckCount[player] = post->deckCount[player];
        memcpy(pre.deck[player], post->deck[player], MAX_DECK);

        //Check that no other changes were made when calling FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        passing = passing * assertEq(0, ret, "memcmp return", description);
        fflush(stdout);
    
    
    } else if ((treasureDeckCount + treasureDiscardCount) == 1) {
        fflush(stdout);
    // If treasureDeck == 1, then treasureDiscard == 0
        //Find the card in deck and put it in hand
        description = "handCount increases by 1";
        passing = passing * assertEq(pre.handCount[player] + 1, post->handCount[player],
                    "handCount", description);
        pre.handCount[player] += 1;

        index_1 = -1;
        if(treasureDeckCount == 1)  { 
            for(i = 0; i < pre.deckCount[player]; i++) {
                card = pre.deck[player][i];
                if(index_1 >= 0) {
                    break; 
                }
                if(cardIsTreasure(card)) {
                    index_1 = i; 
                }
            }
            description = "Top hand card is correct";
            passing = passing * assertEq(pre.deck[player][index_1],
                    post->hand[player][post->handCount[player] - 1],
                    "card id", description);
            pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][index_1];
        }
        else if(treasureDiscardCount == 1)  { 
            //Copy the card over, since it was in discard and shuffle is unpredictable
            pre.hand[player][pre.handCount[player] - 1] = post->hand[player][post->handCount[player] - 1];
        }

        description = "Top hand card is a treasure";
        passing = passing * assertEq(TRUE, cardIsTreasure(post->hand[player][post->handCount[player] - 1]),
                "cardIsTreasure", description);
        
        //Check that deck + discard has only decreased by 1
        description = "deck + discard has only decreased by 1";
        expected = pre.deckCount[player] + pre.discardCount[player] - 1;
        actual = post->deckCount[player] + post->discardCount[player];
        passing = passing * assertEq(expected, actual, "deck + discard", description);

        //Unclear what state of discard, deck, and their counts will be
        // So just copy post's values. 
        printf("Starting final test\n");
        fflush(stdout);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.discard[player], post->discard[player], MAX_DECK);
        printf("Copying last memory\n");
        fflush(stdout);
        pre.deckCount[player] = post->deckCount[player];
        memcpy(pre.deck[player], post->deck[player], MAX_DECK);

        //Check that no other changes were made when calling FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));
        passing = passing * assertEq(0, ret, "memcmp return", description);
        fflush(stdout);

    } else if ((treasureDeckCount + treasureDiscardCount) == 0) {
        // This behavior is undefined? So I won't run many tests for it,
        // except that the sum of deck and discard should not change.
        description = "Deck + discard does not change";
        expected = pre.deckCount[player] + pre.discardCount[player];
        actual = post->deckCount[player] + post->discardCount[player];

        passing = passing * assertEq(expected, actual, "deck + discard", description);
    }
    fflush(stdout);


    return 0;

}





int main() {
    int numTests = 2000;
    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, p;
    int passing = TRUE;
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

        passing = passing * checkAdventurerEffect(&G, p, n);
    }

    if(passing) {
        printf("ANNOUNCEMENT: All tests passed!"); 
    } else {
        printf("ANNOUNCEMENT: At least one test failed!");
    }



    return 0;
}
