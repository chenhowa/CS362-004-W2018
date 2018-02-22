
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

/* Here deck = hand + discard + deck */


int main() {

    struct gameState g;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
                     smithy, council_room};

    printf("--------------------Testing fullDeckCount()----------\n");

    // testing at initialization
    initializeGame(2, cards, 100, &g);

    //testing invalid cards
    if(fullDeckCount(0, 4, &g) != -1){
        printf("Card value too high returns -1: Failed!\n");
    }
    else{
        printf("Card value too high returns -1: Passed!\n");
    };

    if(fullDeckCount(0, -1, &g) != -1){
        printf("Card value too low returns -1: Failed!\n");
    }
    else{
        printf("Card value too low returns -1: Passed!\n");
    };

    //testing invalid player number

    if(fullDeckCount(3, copper, &g) != -1){
        printf("Player number higher than current players returns -1: Failed!\n");
    }
    else{
        printf("Player number higher than current players returns -1: Passed!\n");
    }


    // testing correct card count for all players after initialization
    memset(&g, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(4, cards, 100, &g);
    int i = 0;
    for(i=0; i<4; i++){
        if(fullDeckCount(i, copper, &g) == 7){
            printf("Player %d has 7 copper at initialization: Passed!\n", i);
        }
        else{
            printf("Player %d has 7 copper at initialization: Failed!\n", i);
        }
        if(fullDeckCount(i, estate, &g) == 3){
            printf("Player %d has 7 copper at initialization: Passed!\n", i);
        }
        else{
            printf("Player %d has 7 copper at initialization: Failed!\n", i);
        }
    }

    memset(&g, 23, sizeof(struct gameState));   // clear the game state

    // testing manual adds

    g.deckCount[0] = 0;
    g.handCount[0] = 0;
    g.discardCount[0] = 0;
    int check = 0;
    for(i=0; i <= treasure_map; i++){
        if(fullDeckCount(0, copper, &g) != 0) {
            check += 1;
            break;
        }
    }

    // testing manual combinations of cards in piles
    check = 0;
    int j = 0;
    int k = 0;
    for(i = 0; i <=2; i++){
        for(j = 0; j <= 2; j ++){
            for(k = 0; k <= 2; k++){
                g.deckCount[0] = i;
                g.handCount[0] = j;
                g.discardCount[0] = k;

                g.deck[0][i] = copper;
                g.hand[0][j] = copper;
                g.discard[0][k] = copper;

                if(fullDeckCount(0, copper, &g) != (i + j + k)){
                    check += 1;
                    printf("Expected %d copper in deck, %d in hand and %d in discard, got total of %d\n", i, j, k, fullDeckCount(0, copper, &g));
                }
            }
        }
    }
    if(check != 0){
        printf("Manual Add: Correct count with various combos in hand, discard and deck: Failed!\n");
    }
    else{
        printf("Manual Add: Correct count with various combos in hand, discard and deck: Passed!\n");
    }
}