//
// Sean Moss
// Random Test for Garden Card
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
    int l;
    int check = 0;
    int playerCardChanged = 0;
    int handcountIncorrect = 0;
    int returnedError = 0;
    int supplyCardsAltered = 0;
    int incorrectActions = 0;
    int totalCheck = 0;

    printf("--------------------Testing Great Hall Card----------\n");

    // seed random
    srand(time(NULL));

    // runs 1000 random tests
    for(l = 0; l < 1000; l++) {
        check = 0;

        struct gameState g;

        int possibleCards[8] = {copper, silver, gold, village, tribute, embargo, cutpurse, smithy};


        // ------------ Set random data ---------

        // choose random number of players
        int players = (rand() % 3) + 2;

        // initialize game
        initializeGame(players, cards, rand()%9999999 + 1, &g);

        // choose random starting decks (including hand and discard)
        for(i = 0; i < players; i++){
            g.handCount[i] = rand() % 7;
            g.discardCount[i] = rand() % 7;
            g.deckCount[i] = rand() % 7;
            for(j = 0; j < g.handCount[i]; j++){
                g.hand[i][j] = possibleCards[rand()%8];
            }
            for(j = 0; j < g.discardCount[i]; j++){
                g.discard[i][j] = possibleCards[rand()%8];
            }
            for(j = 0; j < g.deckCount[i]; j++){
                g.deck[i][j] = possibleCards[rand()%8];
            }
        }

        // choose random player to play card
        g.whoseTurn = rand() % players;

        int handPos = 0;
        // choose random hand position (within limits)
        if(g.handCount[g.whoseTurn] == 0){
            handPos = 0;
            g.handCount[g.whoseTurn] = 1;
        }
        else{
            handPos = rand() % g.handCount[g.whoseTurn];
        }


        // set handPos to great hall
        g.hand[g.whoseTurn][handPos] = great_hall;

        // set random number of actions
        g.numActions = rand() % 5;

        // -------save state of game data (to compare to later)-------


        int numActions = g.numActions;

        int playerCardCount[players]; // save current players card count
        for(k = 0; k < players; k++){
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
            numberOfCards[k] = fullDeckCount(g.whoseTurn, k, &g);
        }

        //---- play card----
        int myReturn = cardEffect(great_hall,0,0,0, &g, handPos, NULL);


        // ------checking results-----

        // checking if cards came from player pile (that total cards of each type are same)
        numberOfCards[great_hall] -= 1; // accounts for played great hall card
        for(k=0; k <= treasure_map; k++){
            if(numberOfCards[k] != fullDeckCount(g.whoseTurn, k, &g)){
                check++;
                playerCardChanged++;
                break;
            }
        }

        // checking if handcount for all players is as expected
        for(k = 0; k < players; k++){
            if(g.handCount[k] != playerCardCount[k]){
                check += 1;
                handcountIncorrect++;
            }
        }

        // checks if supply card piles changed
        for(k=0; k <= treasure_map; k++){
            if(g.supplyCount[k] != supplyCards[k]){
                check++;
                supplyCardsAltered++;
                break;
            }
        }

        // check if number of actions stayed the same (increased by 1 and decreased by one for playing card)
        if(g.numActions != numActions+1){
            incorrectActions++;
            check++;
        }


        if (myReturn == -1){
            check += 1;
            returnedError++;
        }

        if(check != 0){
            totalCheck++;
        }

    }

    if(totalCheck == 0){
        printf(  "All tests passed!\n" );
    }
    else{
        printf("%d test cases failed out of 1000!\n", totalCheck);
        printf( "Player Cards Changed in %d Cases\n" , playerCardChanged);
        printf( "Player Handcount Incorrect in %d Cases\n" , handcountIncorrect);
        printf( "Test Returned Error Code in %d Cases\n" , returnedError);
        printf( "Supply Cards Altered in %d Cases\n" , supplyCardsAltered);
        printf( "Incorrect Number of Actions in %d Cases\n" , incorrectActions);
    }

    return 0;
};
