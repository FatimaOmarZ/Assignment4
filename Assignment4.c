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
int remaining_needed[] ;



//return 0 if successful and -1 if unsuccessful
int request_resources(int customer_num, int request[]);
//prints the current state of the arrays
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
    
    printf("enter number of resources: ");
    scanf("%d",(&num_of_resources));
    printf("enter number of customers: ");
    scanf("%d",(&num_of_customers));
    int max_required[num_][];
    char line[128][10];
    FILE *Streamin = fopen("sample4_in.txt", "r");
	if(!Streamin)
	{
		printf("Error in opening input file...exiting with error code -1\n");
		return -1;
	}
    int i=0,totalx=0,totaly=0, x=0,y=0;
    int num;
	while(fscanf(Streamin, "%d", &num) == 1) {
        i++;
        max_required[i]=num;
       
    }
    fclose(Streamin);
    totalx= i;
    totaly= y;
    for (i=0;i<totalx;i++)
{    printf("%d",max_required[x]);
}   
    printf("\n");
	return 0;
}
