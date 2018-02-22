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
    printf("--------------------Testing Great Hall Card----------\n");
    // set player decks


// set all players initial hands and discard piles
    for(i = 0; i < 4; i++){
        g.handCount[i] = 5;
        g.hand[i][0] = great_hall;
        g.discardCount[i] = 3;
        for(k=1; k<5; k++){
            g.hand[i][k] = village;
            g.discard[i][k] = copper;
        }
    }

    // set player 1 to have 1 in deck
    g.deckCount[0] = 1;
    g.deck[0][0] = gold;


    // set deck player 2 to have 2 in deck
    g.deckCount[1] = 2;
    for(int i = 0; i < 2; i++){
        g.deck[1][i] = gold;
    }

    // set player 3 0 in deck
    g.deckCount[2] = 0;
    for(int i = 0; i < 8; i++){
        g.deck[0][i] = -1;
    }

    // set player 4 to have 3 in deck
    g.deckCount[3] = 3;
    for(int i = 0; i < 3; i++){
       g.deck[3][i] = copper;
    }

    // loop through test decks (players)
    for(i = 0; i < 4; i++){
        check = 0;
        g.whoseTurn = i;

        int numActions = g.numActions;

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
            numberOfCards[k] = fullDeckCount(i, k, &g);
        }

        cardEffect(great_hall, 0, 0, 0, &g, 0, 0);

        // checking if cards came from player pile (that total cards of each type are same)
        numberOfCards[great_hall] -= 1; // accounts for played great hall card
        for(k=0; k <= treasure_map; k++){
            if(numberOfCards[k] != fullDeckCount(i, k, &g)){
                check++;
                printf("player cards changed\n");
                break;
            }
        }

        // checking if handcount for all players is as expected
        for(k = 0; k < 4; k++){
            if(g.handCount[k] != playerCardCount[k]){
                    check += 1;
                    printf("Expected %d cards in player %d hand got %d!\n",playerCardCount[k], k, g.handCount[k]);
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

        // check if number of actions stayed the same (increased by 1 and decreased by one for playing card)
        if(g.numActions != numActions+1){
            printf("Number of actions not correct\n");
            check++;
        }

        if(check != 0){
            printf("Deck Configuration %d tests: Failed! (%d tests failed)\n", i, check);
        }
        else{
            printf("Deck Configuration %d tests: Passed!\n", i);
        }
    }
}
