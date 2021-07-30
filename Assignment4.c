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
#include <ctype.h>



#define NUM_OF_CUSTOMERS 5
#define NUM_OF_RESOURCES 4
int count=0;
pthread_mutex_t mutex;

//from the textbook chapter 8
/* the available amount of each resource */
int available_resources[NUM_OF_RESOURCES];   
/*the maximum demand of each customer */
int max_required[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES] ={
                            {6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };
/* the amount currently allocated to each customer */
int allocated_resources[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];
/* the remaining need of each customer */
int remaining_needed[5][4]= {
                            {6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };
int request_resources2(int customer_num, int request[]);
int request_resources(int customer_num, int request[]);
// int extract_customer(char str[]);
// int* extract_array(char str[]);
void print_Curr_State();
// int bankers_algo(int customer_number, int request);
int release_resources(int customer, int request[]);
int safety_algorithm();

int main(int argc, char* argv[]){
    count = argc - 1;
	
    printf("Currently available resources: ");
	for (int i=0; i<count; i++){
        available_resources[i]=atoi(argv[i+1]);
        printf("%d ",available_resources[i]);
	}
    printf("\n");
    

    int i=0,j=0;
   
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
    
    char check[13]={'\0'};
    char *test;
   
    test = check;
    while(1) {
        
        printf("Enter Command: \n");
        fgets(check,sizeof(check),stdin);
        // puts(check);
        
        if (strncmp(check, "Exit", 4) == 0) {
            break; //exit the loop
        }
       

        else if(strncmp(check,"RQ",2)==0){
           
            int array[10],customer_id;
    		i = 0, j=0;
            int arr[10]={0,0,0,0,0,0,0,0,0,0};
            int request[4]={0,0,0,0};
            for(i=2;i<sizeof(check);i++){
                if(isdigit(check[i])){
                    // printf("\n%c",check[i]);
                    // if(i-2==1)
                    array[i-2]=(int)(check[i]-'0');
                    // int i = (int)(c - '/0')
                //    sscanf(check[i], "%d", &array[i-2]);
                //    printf("%d\n",array[i-2]);
                    // if(i-2>=1){
                        arr[i-2]=array[i-2];
                        
                    // }
                    // else if(i-2==0){
                        // customer_id=array[i-2];
                    // }
                    j++;
                    
                }
                
            }
            customer_id=arr[1];
            // printf("customer_id: %d\n",customer_id);
            // printf("j= %d\n",j);
            j=0;
            // int arr[4]={0,0,0,0};
            for(i=3;i<10;i+=2){
                // arr[i]=array[i+1];
                // printf("%d\n",arr[i]);
                request[j]=arr[i];
                
                j++;
            }
            // printf("request array:");
            // for(i=0;i<4;i++){
            //     // arr[i]=array[i+1];
            //     printf("%d\n",request[i]);
            // }
            int value= request_resources(customer_id,request);
            if(value==0){
                printf("\nState is unsafe, and request is unsatisfied\n");
            }
            else if(value==1){
                 printf("\nState is safe, and request is satisfied\n");
            }
            
        }
        else if(strncmp(check,"RL",2)==0){
            int array[10],customer_id;
    		i = 0, j=0;
            int arr[10]={0,0,0,0,0,0,0,0,0,0};
            int request[4]={0,0,0,0};
            for(i=2;i<sizeof(check);i++){
                if(isdigit(check[i])){
                    // printf("\n%c",check[i]);
                    // if(i-2==1)
                    array[i-2]=(int)(check[i]-'0');
                    // int i = (int)(c - '/0')
                //    sscanf(check[i], "%d", &array[i-2]);
                //    printf("%d\n",array[i-2]);
                    // if(i-2>=1){
                        arr[i-2]=array[i-2];
                        
                    // }
                    // else if(i-2==0){
                        // customer_id=array[i-2];
                    // }
                    j++;
                    
                }
                
            }
            customer_id=arr[1];
            // printf("customer_id: %d\n",customer_id);
            // printf("j= %d\n",j);
            j=0;
            // int arr[4]={0,0,0,0};
            for(i=3;i<10;i+=2){
                // arr[i]=array[i+1];
                // printf("%d\n",arr[i]);
                request[j]=arr[i];
                
                j++;
            }
            int value= release_resources(customer_id,request);
             if(value==0){
               printf("Incorrect number of resources given.");
            }
            else if(value==1){
                printf("Resources released.");
               
            }
            //release resources
        }
        else if(strncmp(check,"Status",6)==0){
            print_Curr_State();
            //print all the arrays
        }
        else if(strncmp(check,"Run",3)==0){
            safety_algorithm();
            //run all processes using safety algo
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
                printf("State is safe, and request is satisfied");
            }
        }else{
            printf("State is unsafe, and request is unsatisfied");
            return 0;
        }
    }
return 0;
}

void print_Curr_State(){
    int i=0,j=0;
    printf("\nAvailable Resources:\n");
    for(j=0;j<count;j++){
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