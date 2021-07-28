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
// #define num_of_customers 5
// #define num_of_resources 4
int customer_num= 0, count=0;
pthread_mutex_t mutex;
int num_of_resources, num_of_customers;
//from the textbook chapter 8
// typedef struct banker{
/* the available amount of each resource */
//int available_resources;   
/*the maximum demand of each customer */
// int *max_required[][num_of_resources];
/* the amount currently allocated to each customer */
int *allocated_resources;
/* the remaining need of each customer */
int *remaining_needed;



//return 0 if successful and -1 if unsuccessful
int request_resources(int customer_num, int request);
//
void print_Curr_State();
int bankers_algo(int customer_number, int request);
void release_resources(int customer_num, int release);
int safety_algorithm(int processes, int available_resources, int max_required,int allocated_resources);

int main(int argc, char* argv[]){
    count = argc - 1;
	int *available_resources =(int*) calloc(count+1,sizeof (int));
	// printf("%d\n%d\n",argc,count);
    printf("Currently available resources: ");
	for (int i=0; i<count; i++){
        available_resources[i]=atoi(argv[i+1]);
        printf("%d ",available_resources[i]);
	}
    printf("\n");
    num_of_resources= count;
    
    printf("Enter number of customers: ");
    scanf("%d",(&num_of_customers));
    // printf("%d",num_of_resources);
    // max_required[][]=(int*)realloc(max_required, (sizeof(int));

    int i=0,j=0;

    int *allocated_resources [num_of_customers][num_of_resources];
    //=(int*) malloc (sizeof (int)*num_of_customers*num_of_resources);
    int *remaining_needed [num_of_customers][num_of_resources];
    //= (int*) malloc (sizeof (int)*num_of_customers*num_of_resources);
    //int *max_required [num_of_customers][num_of_resources];
    //= (int*) malloc (sizeof (int)*num_of_customers*num_of_resources);
    
 
       
    // allocated_resources[num_of_customers][num_of_resources];
    // /* the remaining need of each customer */
    // remaining_needed[num_of_customers][num_of_resources] ;
    for(i=0 ;i<num_of_customers;i++){
        for(j=0;j<num_of_resources;j++){
           // max_required[i][j]=0;
            remaining_needed[i][j]=0;
            allocated_resources[i][j]=0;
        }
    }
    int max_required[5][4] ={{6,4,7,3}, 
                             {4,2,3,2},
                             {2,5,3,3}, 
                             {6,3,3,2}, 
                             {5,5,7,5}
                             };
    
   
    printf("Maximum resources from file:\n");
    for(i=0 ;i<5;i++){
        int n=0;
        for(j=0;j<4;j++){
            printf("%d ",max_required[i][j]);
            n++;
            if(n==4){
                printf("\n");
            }
        }

    }
    char str[20];
    do{
        printf("Enter Command: ");
        scanf("%s", str);
        // char *token = strtok(str, " ");
        // if(strcmp(str,))
        // printf("%c",str[2]);
        if(strcmp(str, ""))
            
    }while(strcmp(str,"Exit")!=0);
	return 0;
}