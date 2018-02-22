
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

    int cost[treasure_map+1];
    // array of correct costs
    cost[curse] = 0;
    cost[estate] = 2;
    cost[duchy] = 5;
    cost[province] = 8;
    cost[copper] = 0;
    cost[silver] = 3;
    cost[gold] = 6;
    cost[adventurer] = 6;
    cost[council_room] = 5;
    cost[feast] = 4;
    cost[gardens] = 4;
    cost[mine] = 5;
    cost[remodel] = 4;
    cost[smithy] = 4;
    cost[village] = 3;
    cost[baron] = 4;
    cost[great_hall] = 3;
    cost[minion] = 5;
    cost[steward] = 3;
    cost[tribute] = 5;
    cost[ambassador] = 3;
    cost[cutpurse] = 4;
    cost[embargo] = 2;
    cost[outpost] = 5;
    cost[salvager] = 4;
    cost[sea_hag] = 4;
    cost[treasure_map] = 4;

    printf("--------------------Testing getCost()----------\n");
    int i =0;
    int check = 0;
    // testing all valid cards return correct cost
    for(i=0; i <=treasure_map; i++){
        if(getCost(i) != cost[i]){
            check++;
            printf("Card %d does not return the correct cost!");
            break;
        }
    }

    if(check == 0){
        printf("getCost() returns correct cost for valid cards: Passed!\n");
    }
    else{
        printf("getCost() returns correct cost for valid cards: Failed!\n");
    }

    //testing value less than 0;

    if(getCost(-1) == -1){
        printf("getCost() returns -1 for value less than 0: Passed!\n");
    }
    else {
        printf("getCost() returns -1 for value less than 0: Failed!\n");
    }

    // testing value greater than treasure_map

    if(getCost(treasure_map+1) == -1){
        printf("getCost() returns -1 for value greater than treasure_map: Passed!\n");
    }
    else {
        printf("getCost() returns -1 for value greater than treasure_map: Failed!\n");
    }


}
