

/* Howard Chen
 * Fuzzy tester for dominion.c: councilRoomEffect()
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

    if(pre.deckCount[player] >= 4) {
        printf("Case 1\n");

        pre.handCount[player] += 4;
        pre.hand[player][pre.handCount[player] - 1] = pre.deck[player][pre.deckCount[player] - 4];
        pre.hand[player][pre.handCount[player] - 2] = pre.deck[player][pre.deckCount[player] - 3];
        pre.hand[player][pre.handCount[player] - 3] = pre.deck[player][pre.deckCount[player] - 2];
        pre.hand[player][pre.handCount[player] - 4] = pre.deck[player][pre.deckCount[player] - 1];
        pre.deckCount[player] -= 4;
        pre.numBuys += 1;

        //Adjust the other player's values
        pre.handCount[otherPlayer] += 1;
        pre.hand[otherPlayer][pre.handCount[otherPlayer] - 1] = pre.deck[otherPlayer][pre.deckCount[otherPlayer] - 1];
        pre.deckCount[otherPlayer] -= 1;

        description = "No other changes have occurred";
        ret = memcpy(&pre, post, sizeof(struct gameState));
        assertEq(0, ret, "memcmp return", description);
    } else if (pre.deckCount[player] + pre.discardCount[player] >= 4) {
        printf("Case 2\n");
        pre.handCount[player] += 4;
        pre.hand[player][pre.handCount[player] - 1] = post->hand[player][post->handCount[player] - 1];
        pre.hand[player][pre.handCount[player] - 2] = post->hand[player][post->handCount[player] - 2];
        pre.hand[player][pre.handCount[player] - 3] = post->hand[player][post->handCount[player] - 3];
        pre.hand[player][pre.handCount[player] - 4] = post->hand[player][post->handCount[player] - 4];
        pre.deckCount[player] = pre.deckCount[player] + pre.discardCount[player] - 4;
        memcpy(pre.deck[player], post->deck[player], pre.deckCount[player] + 4);
        pre.discardCount[player] = post->discardCount[player];
        memcpy(pre.deck[player], post->deck[player], pre.discardCount[player]);

        //Adjust the other player's values
        pre.handCount[otherPlayer] += 1;
        pre.hand[otherPlayer][pre.handCount[otherPlayer] - 1] = pre.deck[otherPlayer][pre.deckCount[otherPlayer] - 1];
        pre.deckCount[otherPlayer] -= 1;


        description = "No other changes were made to game";
        ret= memcmp(&pre, post, sizeof(struct gameState));
        assertEq(0, ret, "memcmp return", description);
    
    } else {
        printf("Case 3: Too few cards. Not interesting\n");
    }


    //Check return value was correct (should always return 0)
    description = "Return was correct"; 
    printf("Starting councilRoomEffect\n");
    fflush(stdout);
    ret = councilRoomEffect(post, player, 0);
    printf("Ending councilRoomEffect\n");
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
    printf ("Testing councilRoomEffect.\n");
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
