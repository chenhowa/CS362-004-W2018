#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main() {

    struct gameState g;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
                     smithy, council_room};
    int k = 0;
    int i = 0;
    int j = 0;
    int check = 0;
    initializeGame(4, cards, 100, &g);
    printf("--------------------Testing Gardens Card----------\n");
    // set all players initial hands and discard piles
    for(i = 0; i < 4; i++){
        g.handCount[i] = 5;
        g.hand[i][0] = gardens;
        g.discardCount[i] = 5;
        g.deckCount[i] = 5;
        for(k=0; k<5; k++){
            g.hand[i][k] = village;
            g.discard[i][k] = copper;
            g.deck[i][k] = village;
        }
    }
    check = 0;

    // test returns -1 for all players
    for(int i = 0; i < 4; i++){
        g.whoseTurn = i;
        if(cardEffect(gardens, 0, 0, 0, &g, 0, 0) != -1){
            printf("Gardens did not return -1 for player %d\n", i);
            check++;
        }
    }
    if(check == 0){
        printf("Returns -1 for all players: Passed!\n");
    }
    else{
        printf("Returns -1 for all players: Failed!\n");
    }

    check = 0;
    memset(&g, 23, sizeof(struct gameState));   // clear the game state
    // set all players initial hands and discard piles
    initializeGame(4, cards, 100, &g);

    for(i = 0; i < 4; i++){
        g.handCount[i] = 5;
        g.hand[i][0] = gardens;
        g.discardCount[i] = 5;
        g.deckCount[i] = 5;
        for(k=0; k<5; k++){
            g.hand[i][k] = village;
            g.discard[i][k] = copper;
            g.deck[i][k] = village;
        }
    }

    g.whoseTurn = 0;
    int playerCardCount[4]; // save current players card count
    for(k = 0; k < 4; k++){
        playerCardCount[k] = g.handCount[k];
    }
    // save supply of kingdom and victory cards (to check later)

    int supplyCards[treasure_map+1];
    for(k = 0; k <= treasure_map; k++){
        supplyCards[k] = g.supplyCount[k];
    }

    // get how many cards of each type player has (to check later)
    int numberOfCards[treasure_map + 1];
    for(k=0; k <= treasure_map; k++){
        numberOfCards[k] = fullDeckCount(0, k, &g);
    }
    // test if players decks, hands and discard remains unchanged after playing
    // checking if handcount for all players is as expected
    for(k = 0; k < 4; k++){
        if(g.handCount[k] != playerCardCount[k]){
            check += 1;
            printf("Expected %d cards in player %d hand got %d!\n",playerCardCount[k], k, g.handCount[k]);
        }
    }

    for(k=0; k <= treasure_map; k++){
        if(numberOfCards[k] != fullDeckCount(0, k, &g)){
            check++;
            printf("player cards changed\n");
            break;
        }
    }

    // checks if supply card piles changed
    for(k=0; k <= treasure_map; k++){
        if(g.supplyCount[k] != supplyCards[k]){
            printf("Supply cards altered!\n");
            check++;
            break;
        }
    }

    if(check == 0){
        printf("Hand State Change Tests: Passed!\n");
    }
    else{
        printf("Hand State Change Tests: Failed!\n");
    }
}