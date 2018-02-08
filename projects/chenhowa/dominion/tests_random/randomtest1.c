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

int checkAdventurerEffect(struct gameState* post, int player) {

    struct gameState pre;
    int ret;
    char* description;
    int treasureDeckCount = 0;
    int treasureDiscardCount = 0;
    int i;
    int card;
    int cardIsTreasure;
    int index_1;
    int index_2;
    int tempHandSize;

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    ret = adventurerEffect(post, p);
    assertEq(0, ret, "return", description);


    //Based on the pre game state, make the necessary changes
    // according to the understanding of how adventurerEffect works
    //
    // According to shuffle, the cards in the Deck are the cards that 
    // are reshuffled

    //Count the number of treasures in deck and discard, separately.
    for(i = 0; i < pre.deckCount[player]; i++) {
        card = pre.deck[player][i];
        cardIsTreasure = card == gold || card == silver || card == copper;
        if(cardIsTreasure) {
            treasureDeckCount++; 
        } 
    }

    for(i = 0; i < pre.discardCount[player]; i++) {
        card = pre.discard[player][i];
        cardIsTreasure = card == gold || card == silver || card == copper;
        if(cardIsTreasure) {
            treasureDiscardCount++; 
        }
    }

    // If there are 2+ treasure in deck.
    if(treasureDiscardCount >= 2) {
        //Then handCount increased.
        pre.handCount[player] += 2;

        //Determine indices of two treasures, and put them in hand
        index_1 = -1;
        index_2 = -1;
        for(i = pre.deckCount[player] - 1; i > -1; i--) {
            card = pre.deck[player][i];
            cardIsTreasure = card == gold || card == silver || card == copper;
            if(index_1 >= 0 && index_2 >= 0) {
                break; //Stop looping once two indices are found 
            }

            if(cardIsTreasure) {
                if(index_1 < 0) {
                    index_1 == i; 
                } else if(index_2 < 0) {
                    index_2 == i; 
                } 
            }
        }
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][index_1];
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][index_2];

        //deckCount decreases by the size of temphand
        tempHandSize = pre.deckCount[player] - index_2;
        pre.deckCount[player] -= tempHandSize;

        //discardCount will increase by the other cards in tempHandSize.
        pre.discardCount += tempHandSize - 2;
        //Trust discardCard to do its job correctly.
        memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
        //Check that no other changes were made when calling the FUT
        description = "No other changes were made";
        ret = memcmp(&pre, post, sizeof(struct gameState));

        assertEq(0, ret, "memcmp return", description);

    } else if (treasureDeckCount + treasureDiscardCount >= 2) {
    // If treasureDeck + treasureDiscard >= 2
    
    
    } else if (treasureDeckCount + treasureDiscardCount < 2) {
    // If treasureDeck + treasureDiscard < 2
        //Then handCount increased.
        pre.handCount[player] += 2;
    
        //Determine indices of two treasures, and put them in hand
        
        //Unclear what state of discard, deck, and their counts will be

        //Check taht no other changes were made when calling FUT
    }


    if(pre.deckCount[player] > 2) {
    
    }

    return 0;






int main() {

    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, r, p, deckCount, discardCount, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    printf ("Testing adventurerEffect.\n");
    printf ("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        //Here starts my own code
        checkAdventurerEffect(p, &G);
    }

    printf ("ALL TESTS OK\n");



    return 0;
}
