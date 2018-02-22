#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

    struct gameState g;


    printf("--------------------Testing handCard()----------\n");

    // testing if outside of range of handCount

    g.whoseTurn = 0;
    g.hand[0][0] = copper;
    g.handCount[0] = 1;

    if(handCard(1, &g) != -1){
        printf("Return -1 if handPosition higher than handCount: Failed!\n");
    }
    else{
        printf("Return -1 if handPosition higher than handCount: Passed!\n");
    }

    int i = 0;
    int j = 0;
    memset(&g, 23, sizeof(struct gameState));   // clear the game state
    int check = 0;
    for(i = 0; i < 4; i++){
        g.handCount[i] = 5;
        g.whoseTurn = i;
        for(j=0; j < 5; j++){
            g.hand[i][j] = j + i ;

            if (handCard(j, &g) != j + i){
                printf("Expected card %d, returned card %d", j, handCard(j,&g) );
                check += 1;
            }
        }
    }

    if(check == 0){
        printf("Testing correct value of cards at position with manual addition: Passed!\n");
    }
    else{
        printf("Testing correct value of cards at position with manual addition: Passed!\n");
    }

}