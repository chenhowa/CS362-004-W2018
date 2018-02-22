
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
    initializeGame(4,cards, 100, &g);
    printf("--------------------Testing Adventurer Card----------\n");
    // set player decks


// set all players initial hands and discard piles
    for(i = 0; i < 4; i++){
        g.handCount[i] = 5;
        g.hand[i][0] = adventurer;
        g.discardCount[i] = 3;
        for(k=1; k<5; k++){
            g.hand[i][k] = village;
            g.discard[i][k] = copper;
        }
    }

    // set player 1 entire deck to gold
    g.deckCount[0] = 6;
    for(int i = 0; i < 6; i++){
        g.deck[0][i] = gold;
    }

    // set deck player 2 to gold, and copper silver
    g.deckCount[1] = 6;
    for(int i = 0; i < 6; i++){
        if(i%2 == 0){
            g.deck[0][i] = gold;
        }
        else if (i%3 == 0){
            g.deck[1][i] = silver;
        }
        else{
            g.deck[1][i] = copper;
        }
    }

    // set player 3 to no treasure
    g.deckCount[2] = 8;
    for(int i = 0; i < 8; i++){
        g.deck[0][i] = adventurer;
    }

    // player 4 has only 1 treausure
    g.deckCount[3] = 6;
    for(int i = 0; i < 6; i++){
        if(i == 5){
            g.deck[3][i] = copper;
        }
        else{
            g.deck[3][i] = adventurer;
        }
    }


    // loop through test decks (players)
    for(i = 0; i < 5; i++){
        check = 0;
        g.whoseTurn = i%4;

        if(i == 5){

            g.deckCount[0] = 0;
            g.discardCount[0] = 3;
            for(int i = 0; i < 5; i++){
                g.discard[0][i] = copper;
                g.deck[0][i] = -1;
            }
        }

        // save supply of kingdom and victory cards (to check later)

        int supplyCards[treasure_map+1];
        for(k = 0; k <= treasure_map; k++){
            supplyCards[k] = g.supplyCount[k];
        }

        // get cards in players hand (to compare later)
        int playerHand[treasure_map + 1];
        for(k = 0; k <= treasure_map; k++){ // initialize array to 0
            playerHand[k] = 0;
        }
        for(int k = 0; k < g.handCount[i]; k++){
            playerHand[g.hand[i][k]]++;
        }

        // get cards in players discard (to compare later)
        int playerDiscard[treasure_map + 1];
        for(k = 0; k <= treasure_map; k++){ // initialize array to 0
            playerDiscard[k] = 0;
        }
        for(int k = 0; k < g.discardCount[i]; k++){
            playerDiscard[g.discard[i][k]]++;
        }

        // get cards in players deck and first two treasure.
        int totalTreasure  = 0;
        int playerDeck[treasure_map + 1];

        for(k=0; k <= treasure_map; k++){   // initialize all entries to 0
            playerDeck[k] = 0;
        }
        for(k = 0; k <= g.deckCount[i]; k++){
            if(totalTreasure < 2) {
                if ((g.deck[i][k] == copper || g.deck[i][k] == silver || g.deck[i][k] == gold)) {
                    totalTreasure++;
                    playerHand[g.deck[i][k]]++;
                }
                else{
                    playerDiscard[g.deck[i][k]]++;
                }
            }
            playerDeck[g.deck[i][k]]++; // only add to ideal deck if not being discarded or put in hand
        }

        // add cards already in discard pile to ideal discard array
        for(k=0; k<g.discardCount[i]; k++){
//            printf("adding card %d\n", g.discard[i][k]);
            playerDiscard[g.discard[i][k]]++;
        }

        cardEffect(adventurer, 0, 0, 0, &g, 0, 0);

        // check if player got correct number and type of treasure in hand and that no other
        // changes to hand were made;

        for(k = 0; k < g.handCount[i]; k++){
            playerHand[g.hand[i][k]]--; // decrements index of card (should be 0 when finished)
        }                               // to indicate current hand and array are equal

        // check if all entries in playerHand are 0 (indicate it was equal to current player hand
        for(k = 0; k <= treasure_map; k++){
            if (playerHand[k] != 0){
                printf("Incorrect cards in player Hand!\n");
                check++;
                break;
            }
        }

        // check if ideal discard pile is equal to current discard pile
        for(k=0; k<g.discardCount[i]; k++){
            playerDiscard[g.discard[i][k]]--;
        }
        // check if ideal discard pile is equal to current discard pile
        for(k=0; k<=treasure_map; k++){
            if(playerDiscard[k] != 0){
                printf("Incorrect cards in player discard pile!\n");
                check++;
                break;
            }
        }

        // check if deck changed properly (ideal deck and actual deck are equal)
        for(k=0; k<g.deckCount[i];k++){
            playerDeck[g.deck[i][k]]--;
        }
        for(k=0; k<= treasure_map; k++){
            if(playerDeck[k] != 0){
                printf("Player deck does not have correct cards!\n");
                check++;
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

        if(check != 0){
            printf("Deck Configuration %d tests: Failed! (%d tests failed)\n", i, check);
        }
        else{
            printf("Deck Configuration %d tests: Passed!\n", i);
        }
    }
}
