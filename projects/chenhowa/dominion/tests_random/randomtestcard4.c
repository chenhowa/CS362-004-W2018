


/* Howard Chen
 * Fuzzy tester for dominion.c: minionEffect()
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

int checkCouncilRoomEffect(struct gameState* post, int player, int iteration) {

    struct gameState pre;
    int ret;
    char* description;
    int otherPlayer = (player + 1) % 2;

    //Save the state for later comparison
    memcpy(&pre, post, sizeof(struct gameState));

    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting minionEffect\n");
    fflush(stdout);
    ret = minionEffect(post, player, 0);
    printf("Ending minionEffect\n");
    fflush(stdout);
    assertEq(0, ret, "return", description);




    fflush(stdout);


    return 0;

}





int main() {
    int numTests = 2000;
    // Most of this code is taken from testDrawCard.c.
    // It sets up the random tests as demonstrated in the video lecture
    int i, n, p;
    int otherPlayer;
    struct gameState G;
    printf ("Testing minionEffect.\n");
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
        G.numPlayers = 2; //Set standard value of 2 to avoid any issues.
        G.deckCount[p] = floor(Random() * (MAX_DECK));
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


        //REPEAT FOR THE SECOND PLAYER
        otherPlayer = (p + 1) % 2;
        otherPlayer = floor(Random() * 2);
        G.deckCount[otherPlayer] = floor(Random() * (MAX_DECK));
        G.discardCount[otherPlayer] = floor(Random() * (MAX_DECK - 5 - G.deckCount[otherPlayer])); 
        G.handCount[otherPlayer] = floor(Random() * (MAX_HAND - 5)); 
        for(i = 0; i < G.deckCount[otherPlayer]; i++) {
            G.deck[otherPlayer][i] = floor(Random() * treasure_map); 
        }
        for(i = 0; i < G.discardCount[otherPlayer]; i++) {
            G.discard[otherPlayer][i] = floor(Random() * treasure_map); 
        }
        G.playedCardCount = floor(Random() * (MAX_DECK - 5));



        checkCouncilRoomEffect(&G, p, n);
    }

    printf ("ALL TESTS OK\n");



    return 0;
}
