
/*
--------------------------------------------------
 Project: CP386-a04
 Title:    Banker's Algorithm
 Authors:  Fatima Omar & Mohammad Al Zouabi
--------------------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

typedef struct banker{
    /* the available amount of each resource */
    int available_resources[NUMBER_OF_RESOURCES];
    /*the maximum demand of each customer */
    int max_required[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    /* the amount currently allocated to each customer */
    int allocated_resources[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    /* the remaining need of each customer */
    int remaining_needed[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
} BANKER;





