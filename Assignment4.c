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
int max_required[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES]={
                            {6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };
/* the amount currently allocated to each customer */
int allocated_resources[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];
/* the remaining need of each customer */
int remaining_needed[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES]={{6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };
int request_resources2(int customer_num, int request[]);
int request_resources(int customer_num, int request[]);

void print_Curr_State();

int release_resources(int customer, int request[]);
int safety_algorithm();

int main(int argc, char* argv[]){
    count = argc - 1;
	printf("Number of Customers: 5");
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
    // remaining_needed[NUM_OF_CUSTOMERS][NUM_OF_CUSTOMERS]= 
    char flush;
    // 
    
    // printf("\n");
    while(1) {
        // fflush(stdin);
        printf("\nEnter Command: ");
        
        fgets(check,sizeof(check),stdin);
        // puts(check);
        fflush(stdin);
        // while ((flush = getchar()) != '\n' && flush != EOF);
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
                   
                    array[i-2]=(int)(check[i]-'0');
               
                        arr[i-2]=array[i-2];
                     
                    j++;
                    
                }
                
            }
            customer_id=arr[1];
           
            j=0;
           
            for(i=3;i<10;i+=2){
                
                request[j]=arr[i];
                
                j++;
            }
          
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
                    array[i-2]=(int)(check[i]-'0');
                    arr[i-2]=array[i-2];
                    j++;
                }
            }
            customer_id=arr[1];
            j=0;
            for(i=3;i<10;i+=2){
                request[j]=arr[i];
                j++;
            }
            int value= release_resources(customer_id,request);
             if(value==0){
               printf("\nIncorrect number of resources given.");
            }
            else if(value==1){
                printf("\nResources released.");
            }
            //Release Resources
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

int release_resources(int customer,int request[]){

    for (int i=0; i!=NUM_OF_RESOURCES;i++){    
        int allocated=allocated_resources[customer][i];

        if(request[i]>allocated){
            
            return 0;

        }
    }
    for (int i=0; i!=NUM_OF_RESOURCES;i++){
        int allocated=allocated_resources[customer][i];
        available_resources[i]= available_resources[i]+request[i];
        allocated_resources[customer][i]=allocated_resources[customer][i]-request[i];
    }
    
    return 1;

}

int request_resources2(int customer_num, int request[]){
    for (int i=0; i!=NUM_OF_RESOURCES;i++){
        int req=remaining_needed[customer_num][i];
        if(request[i]<=req){
            if(request[i]>available_resources[i]){
                return 0;
            }
        }else{
            return 0;
        }
    }
    for(int i=0;i!=NUM_OF_RESOURCES;i++){
        int req=remaining_needed[customer_num][i];
        available_resources[i]= available_resources[i]-request[i];
        allocated_resources[customer_num][i]=allocated_resources[customer_num][i]+request[i];
        remaining_needed[customer_num][i]=remaining_needed[customer_num][i]-request[i];    
    }
return 1;
}
int request_resources(int customer_num, int request[]){
    for (int i=0; i!=NUM_OF_RESOURCES;i++){
        int req=remaining_needed[customer_num][i];
        if(request[i]<=req){
            if(request[i]>available_resources[i]){
                return 0;
            }
        }else{
            return 0;
        }
    }
    for(int i=0;i!=NUM_OF_RESOURCES;i++){
        int req=remaining_needed[customer_num][i];
        available_resources[i]= available_resources[i]-request[i];
        allocated_resources[customer_num][i]=allocated_resources[customer_num][i]+request[i];
        remaining_needed[customer_num][i]=remaining_needed[customer_num][i]-request[i];    
    }
return 1;
}

void print_Curr_State(){
    int i=0,j=0;
    printf("Available Resources:\n");
    for(j=0;j<count;j++){
        printf("%d ",available_resources[j]);
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

int safety_algorithm(){
    int safeseq[5]={0,0,0,0,0}, seq=0,check=0,finish[5]={0,0,0,0,0};
    int z=0, flag=0,inc=0;
    int work[NUM_OF_RESOURCES];
    for(int i=0;i<NUM_OF_RESOURCES;i++){
       work[i]=available_resources[i];
    }
    int k=0;
    while(k<NUM_OF_CUSTOMERS){
        for(int i=0;i<NUM_OF_CUSTOMERS;i++){
            check=0;
            for(int j=0;j<NUM_OF_RESOURCES;j++){
                if(finish[i]==0){
                    if(remaining_needed[i][j]<=work[j])check++;
                }
                if(check==NUM_OF_RESOURCES){
                    for(int j=0;j<NUM_OF_RESOURCES;j++){
                        work[j]=work[j]+allocated_resources[i][j];
                        finish[i]=1;
                    }
                    safeseq[seq]=i;
                    seq++;
                    k++;
                }
            }
        }
    }

    for(int i=0;i<NUM_OF_CUSTOMERS;i++){
        if(finish[i]==1)inc++;
    }
    if(inc>=NUM_OF_CUSTOMERS){
        for(int i=0;i<NUM_OF_CUSTOMERS;i++)printf("%d",safeseq[i]);
    }
    while(1){

        int count=0;
        int customer_num=0;
        for(int i=0; i<NUM_OF_CUSTOMERS;i++){
            int counter=0;
            customer_num=i;
            int request[4]={0,0,0,0};
            for(int j=0;j<4;j++){
                request[j]=remaining_needed[customer_num][j];
                if(request[j]==0){
                    counter++;
                }
            }
            int value=0;
            if(counter==4) {
                value=0;
                counter=0;
            }else{
                
                value= request_resources(customer_num,request);

            }
            
            if(value==1){
                safeseq[z]=customer_num;
                z++;
                
                int allocated[4]={0,0,0,0};
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allocated[x]= allocated_resources[customer_num][x];
                }
                 printf("\n--> Customer/Thread %d",i);
                int allo[4]={0,0,0,0};
                printf("\n     Allocated Resources: ");
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allo[x]= allocated_resources[customer_num][x];
                    printf("%d ",allo[x]);
                }
                printf("\n     Remaining Resources: ");
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allo[x]= remaining_needed[customer_num][x];
                    printf("%d ",allo[x]);
                }

                printf("\n     Available Resources: ");
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allo[x]= available_resources[x];
                    printf("%d ",allo[x]);
                }
                printf("\n     Thread has started");
                  printf("\n     Thread has finished");
                release_resources(customer_num,allocated);
                printf("\n     Thread is releasing resources");

                printf("\n     New Available: ");
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allo[x]= available_resources[x];
                    printf("%d ",allo[x]);
                }
                printf("\n------------------------------\n");
                count++;
            }
// Customer/Thread 1
//  Allocated resources: 1 1 1 1
//  Needed: 3 1 2 1
//  Available: 4 1 3 3
//  Thread has started
//  Thread has finished
//  Thread is releasing resources
//  New Available: 5 2 4 4
            
        }
        if(count==0)break;
    }
    // printf("\nSafe Squence is: ");
    // for(int i= 0; i<5;i++){
    //     printf("%d->",safeseq[i]);
    // }
    printf("\nFinished\n");
    return 0;
}
