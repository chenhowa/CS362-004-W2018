

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"



int main(){

    struct gameState g;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
                    smithy, council_room};

    printf("--------------------Testing isGameOver()----------\n");
    initializeGame(2, cards, 150, &g);
    int myReturn = isGameOver(&g);

    // tests that does not return 0 at initialization
    if(myReturn == 0){
        printf("Returns 0 at initialization: Passed\n");
    }
    else{
        printf("Returns 0 at initialization: Failed\n");
    }

    // checking if province supply = 0 triggers endgame
    g.supplyCount[province] = 0;

    myReturn = isGameOver(&g);

    if(myReturn == 1){
        printf("Returns 1 when province supply is 0: Passed\n");
    }
    else{
        printf("Returns 1 when province supply is 0: Failed\n");
    }
    g.supplyCount[province] = 10; // return province supply count


    // check if each card being 0 individually triggers end game
    int i;
    int check = 0;
    for(i = 0; i <= treasure_map; i++){  // loop through all cards and set to 0 then reset
        g.supplyCount[i] = 0;

        myReturn = isGameOver(&g);

        if(myReturn == 1 && i != province){
            check++;
            g.supplyCount[i] = 2;
            break;
        }
        g.supplyCount[i] = 2;
    }

    if(check != 0){
        printf("Return 0 when single supply (not province) is 0: Failed!\n");
    }
    else{
        printf("Return 0 when single supply (not province) is 0: Passed!\n");
    }

    // check if 2 supply piles are empty (not province) returns 0

    initializeGame(2, cards, 150, &g);
    g.supplyCount[adventurer] = 0;
    g.supplyCount[embargo] = 0;

    myReturn = isGameOver(&g);
    if(myReturn == 1){
        printf("Return 0 when two supply piles (not province) are 0: Failed!\n");
    }
    else{
        printf("Return 0 when two supply piles (not province) are 0: Passed!\n");
    }

    // check when last three supply piles are empty returns 1
    int newCardsLast[10] = {sea_hag, treasure_map, salvager, minion, mine, cutpurse, sea_hag, tribute,
                     smithy, council_room};
    initializeGame(2, newCardsLast, 150, &g); // reinitialize game

    g.supplyCount[treasure_map] = 0;
    g.supplyCount[sea_hag] = 0;
    g.supplyCount[salvager] = 0;

    myReturn = isGameOver(&g);

    if(myReturn == 1){
        printf("Returns 1 when final three possible supply piles are 0: Passed\n");
    }
    else{
        printf("Returns 1 when final three possible supply piles are 0: Failed\n");
    }

    // check when first three supply piles are empty returns 1
    initializeGame(2, cards, 150, &g); // reinitialize game
    g.supplyCount[curse] = 0;
    g.supplyCount[estate] = 0;
    g.supplyCount[duchy] = 0;

    myReturn = isGameOver(&g);

    if(myReturn == 1){
        printf("Returns 1 when first three possible supply piles are 0: Passed\n");
    }
    else{
        printf("Returns 1 when first three possible supply piles are 0: Failed\n");
    }

    // check when three random supply piles are empty returns 1
    initializeGame(2, cards, 150, &g); // reinitialize game
    g.supplyCount[village] = 0;
    g.supplyCount[cutpurse] = 0;
    g.supplyCount[duchy] = 0;

    myReturn = isGameOver(&g);

    if(myReturn == 1){
        printf("Returns 1 when first three random supply piles are 0: Passed\n");
    }
    else{
        printf("Returns 1 when first three random supply piles are 0: Failed\n");
    }

    // check whether returns 1 when more than 3 supply piles are 0
    initializeGame(2, cards, 150, &g); // reinitialize game
    g.supplyCount[village] = 0;
    g.supplyCount[cutpurse] = 0;
    g.supplyCount[duchy] = 0;
    g.supplyCount[mine] = 0;

    myReturn = isGameOver(&g);

    if(myReturn == 1){
        printf("Returns 1 when 4 random supply piles are 0: Passed\n");
    }
    else{
        printf("Returns 1 when 4 random supply piles are 0: Failed\n");
    }
}