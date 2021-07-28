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


#define NUM_OF_CUSTOMERS 5
#define NUM_OF_RESOURCES 4
int customer_num= 0, count=0;
pthread_mutex_t mutex;
int NUM_OF_RESOURCES, NUM_OF_CUSTOMERS;
//from the textbook chapter 8

/* the available amount of each resource */
int available_resources[NUM_OF_RESOURCES];   
/*the maximum demand of each customer */
int max_required[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocated_resources[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];
/* the remaining need of each customer */
int remaining_needed[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];



//return 0 if successful and -1 if unsuccessful
int request_resources(int customer_num, int request);
int extract_customer(char str[]);
int* extract_array(char str[]);
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
    // num_of_resources= count;
    
    // printf("Enter number of customers: ");
    // scanf("%d",(&num_of_customers));
    

    int i=0,j=0;

   
    int max_required[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES] ={{6,4,7,3}, 
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
    
    int ch;
    char check[20]={'\0'};
   
    while((ch = getchar()) != '\n' && ch != EOF);
    
    while(1) {
        
        printf("Enter Command: \n");
        fgets(check,sizeof(check),stdin);
        // puts(check);
        
        if (strncmp(check, "Exit", 4) == 0) {
            break;
        }
        
        else if(strncmp(check,"RQ",2)==0){
           
            int strsize = strlen(check);
            char delimiter[] = " ";
            char array[6]={0,0,0,0,0,0};
            int x=0;
            char *ptr = strtok(check, delimiter);
            while(ptr != NULL)
            {
                printf("%s\n", ptr);
                ptr = strtok(NULL, delimiter);
                
            }
            request_resources(customer,request);

            
        }
        else if(strncmp(check,"RL",2)==0){
            printf("its rl");
        }
        else if(strncmp(check,"Status",6)==0){
            printf("its status");
        }
        else if(strncmp(check,"Run",3)==0){
            printf("its run");
        }
        
        
    }
	return 0;
}

int request_resources(int customer_num, int request[]){
    
    for (int i=0; i!=NUM_OF_RESOURCES;i++){
        if(request[i]<=remaining_needed[customer_num+1][i]){
            if(request[i]<=available_resources[i]){
                available_resources[i]= available_resources[i]-request[i];
                allocated_resources[customer_num+1][i]=allocated_resources[customer_num+1][i]+request[i];
                remaining_needed[customer_num+1][i]=remaining_needed[customer_num+1][i]+request[i];
                printf("State is safe, and request is satisfied")
            }
        }else{
            printf("State is unsafe, and request is unsatisfied");
            return 0;
        }
    }
return 0;
}

void print_Curr_State(){
    int i,j;
    printf("\nAvailable Resources:\n");
    for(j=0;j<4;j++){
        printf("%d ",available_resources[i]);
        
    }
    printf("\nMaximum Resources:\n");
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

     printf("\nAllocated Resources:\n");
    for(i=0 ;i<5;i++){
        int n=0;
        for(j=0;j<4;j++){
            printf("%d ",allocated_resources[i][j]);
            n++;
            if(n==4){
                printf("\n");
            }
        }
    }
    printf("\nNeed Resources:\n");
    for(i=0 ;i<5;i++){
        int n=0;
        for(j=0;j<4;j++){
            printf("%d ",remaining_needed[i][j]);
            n++;
            if(n==4){
                printf("\n");
            }
        }

    }
}
