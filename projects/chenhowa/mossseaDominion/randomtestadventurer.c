//
// Sean Moss
// Random Test for Adventurer Card
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {

    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
                     smithy, council_room};
    int k = 0;
    int i = 0;
    int j = 0;
    int x;
    int check = 0;
    int totalCheck = 0;
    int incorrectHand = 0;
    int incorrectDiscard = 0;
    int incorrectDeck = 0;
    int supplyAltered = 0;

    printf("--------------------Testing Adventurer Card----------\n");

    // seed random
    srand(time(NULL));

    // runs 1000 random tests
    for(x = 0; x < 1000 ; x++) {
        check = 0;

        struct gameState g;

        int possibleCards[5] = {copper, silver, gold, village, tribute};

        // choose random number of players
        int players = (rand() % 3) + 2;

        // initialize game
        initializeGame(players, cards, rand()%9999999 + 1, &g);

        // choose random starting decks (including hand and discard)
        for(i = 0; i < players; i++){
            g.handCount[i] = rand() % 25;
            g.discardCount[i] = rand() % 15;
            g.deckCount[i] = rand() % 25;
            for(j = 0; j < g.handCount[i]; j++){
                g.hand[i][j] = possibleCards[rand()%5];
            }
            for(j = 0; j < g.discardCount[i]; j++){
                g.discard[i][j] = possibleCards[rand()%5];
            }
            for(j = 0; j < g.deckCount[i]; j++){
                g.deck[i][j] = possibleCards[rand()%5];
            }
        }

        // choose random player to play card
        g.whoseTurn = rand() % players;
        int whoseTurn = g.whoseTurn;

        int handPos = 0;
        // choose random hand position (within limits)
        if(g.handCount[g.whoseTurn] == 0){
            handPos = 0;
            g.handCount[g.whoseTurn] = 1;
        }
        else{
            handPos = rand() % g.handCount[g.whoseTurn];
        }

        // set handPos to adventurer
        g.hand[g.whoseTurn][handPos] = adventurer;


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
        for(k = 0; k < g.handCount[whoseTurn]; k++){
            playerHand[g.hand[g.whoseTurn][k]]++;
        }

        // get cards in players discard (to compare later)
        int playerDiscard[treasure_map + 1];
        for(k = 0; k <= treasure_map; k++){ // initialize array to 0
            playerDiscard[k] = 0;
        }
        for(k = 0; k < g.discardCount[whoseTurn]; k++){
            playerDiscard[g.discard[g.whoseTurn][k]]++;
        }

        // get cards in players deck and first two treasure.
        int totalTreasure  = 0;
        int playerDeck[treasure_map + 1];

        for(k=0; k <= treasure_map; k++){   // initialize all entries to 0
            playerDeck[k] = 0;
        }
        for(k = 0; k <= g.deckCount[g.whoseTurn]; k++){
            if(totalTreasure < 2) {
                if ((g.deck[g.whoseTurn][k] == copper || g.deck[g.whoseTurn][k] == silver || g.deck[g.whoseTurn][k] == gold)) {
                    totalTreasure++;
                    playerHand[g.deck[g.whoseTurn][k]]++;
                }
                else{
                    playerDiscard[g.deck[g.whoseTurn][k]]++;
                }
            }
            playerDeck[g.deck[g.whoseTurn][k]]++; // only add to ideal deck if not being discarded or put in hand
        }

        // add cards already in discard pile to ideal discard array
        for(k=0; k<g.discardCount[g.whoseTurn]; k++){
            playerDiscard[g.discard[g.whoseTurn][k]]++;
        }

        // play adventurer card
        int myReturn = cardEffect(adventurer,0,0,0, &g, handPos, NULL);


        if (myReturn == -1){
            printf(ANSI_COLOR_RED "Test Failed, returned -1\n" ANSI_COLOR_RESET , handPos);
            check += 1;
        }

        // check if player got correct number and type of treasure in hand and that no other
        // changes to hand were made;

        for(k = 0; k < g.handCount[i]; k++){
            playerHand[g.hand[whoseTurn][k]]--; // decrements index of card (should be 0 when finished)
        }                               // to indicate current hand and array are equal

        // check if all entries in playerHand are 0 (indicate it was equal to current player hand
        for(k = 0; k <= treasure_map; k++){
            if (playerHand[k] != 0){
                incorrectHand++;
                check++;
                break;
            }
        }

        // check if ideal discard pile is equal to current discard pile
        for(k=0; k<g.discardCount[whoseTurn]; k++){
            playerDiscard[g.discard[whoseTurn][k]]--;
        }
        // check if ideal discard pile is equal to current discard pile
        for(k=0; k<=treasure_map; k++){
            if(playerDiscard[k] != 0){
                check++;
                incorrectDiscard++;
                break;
            }
        }

        // check if deck changed properly (ideal deck and actual deck are equal)
        for(k=0; k<g.deckCount[whoseTurn];k++){
            playerDeck[g.deck[whoseTurn][k]]--;
        }
        for(k=0; k<= treasure_map; k++){
            if(playerDeck[k] != 0){
                incorrectDeck++;
                check++;
                break;
            }
        }

        // checks if supply card piles changed
        for(k=0; k <= treasure_map; k++){
            if(g.supplyCount[k] != supplyCards[k]){
                check++;
                supplyAltered++;
                break;
            }
        }

        if(check > 0){
            totalCheck++;
        }
    }

    if(totalCheck == 0){
        printf( "All tests passed!\n"  );
    }
    else{
        printf( "%d cases failed out of 1000!\n", totalCheck);
        printf("Supply Pile Altered in %d tests\n", supplyAltered);
        printf("Incorrect player hand in %d tests\n", incorrectHand);
        printf("Incorrect player discard in %d tests\n",incorrectDiscard);
        printf("Incorrect player deck in %d tests\n", incorrectDiscard);
    }


    return 0;
};