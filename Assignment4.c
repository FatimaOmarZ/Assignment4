
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

int customer_num= 0, count=0;

//from the textbook chapter 8
/* the available amount of each resource */
int available_resources[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int max_required[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocated_resources[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int remaining_needed[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];


int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);

int main(int argc, char* argv[]){
    count = argc - 1;
	int *array = (int*) calloc(count+1, sizeof(int));
	// printf("%d\n%d\n",argc,count);
	for (int i=0; i<count; i++){
        array[i]=atoi(argv[i+1]);
        // printf("%d\n",array[i]);
	}

}





