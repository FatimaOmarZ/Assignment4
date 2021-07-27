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
#include<pthread.h>
#include<sys/stat.h>

// int n,m;
// int NUMBER_OF_CUSTOMERS= n;
// int NUMBER_OF_RESOURCES= m;

int customer_num= 0, count=0;
pthread_mutex_t mutex;
int num_of_resources = 0, num_of_customers=0;
//from the textbook chapter 8
// typedef struct banker{
/* the available amount of each resource */
int available_resources[];   
/*the maximum demand of each customer */
int max_required[][];
/* the amount currently allocated to each customer */
int allocated_resources[][];
/* the remaining need of each customer */
int remaining_needed[][];



//return 0 if successful and -1 if unsuccessful
int request_resources(int customer_num, int request[]);
//
void print_Curr_State();
int bankers_algo(int customer_number, int request[]);
void release_resources(int customer_num, int release[]);
int safety_algorithm(int processes[], int available_resources[], int max_required[][],int allocated_resources[][]);

int main(int argc, char* argv[]){
    count = argc - 1;
	available_resources = realloc(count+1, sizeof(char));
	// printf("%d\n%d\n",argc,count);
	for (int i=0; i<count; i++){
        available_resources[i]=atoi(argv[i+1]);
        printf("%d\n",available_resources[i]);
	}
    
    num_of_resources= count+1;
   
    printf("enter number of customers: ");
    scanf("%d",(&num_of_customers));

    max_required[num_of_customers][num_of_resources];

    allocated_resources[num_of_customers][num_of_resources];
    /* the remaining need of each customer */
    remaining_needed[num_of_customers][num_of_resources] ;
    
    max_required[num_of_customers][num_of_resources]={{6,4,7,3},
                                                      {4,2,3,2},
                                                      {2,5,3,3},
                                                      {6,3,3,2},
                                                      {5,6,7,5}}

    
	return 0;
}