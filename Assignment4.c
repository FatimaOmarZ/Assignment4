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

//Constants number of resources and number of customers
#define NUM_OF_CUSTOMERS 5
#define NUM_OF_RESOURCES 4

int count=0;
pthread_mutex_t mutex;

//from the textbook chapter 8
/* array that contains the available amount of each resource */
int available_resources[NUM_OF_RESOURCES];   
/*2d array that represents the maximum required resource of each customer */
int max_required[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES]={
                            {6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };
/* 2d array that represents the allocated resources for each customer */
int allocated_resources[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES];
/* 2d array that represents the remaining need for each customer
*/
int remaining_needed[NUM_OF_CUSTOMERS][NUM_OF_RESOURCES]={{6,4,7,3}, 
                            {4,2,3,2},
                            {2,5,3,3}, 
                            {6,3,3,2}, 
                            {5,5,7,5}
                            };

// request resources function for safety algorithm returns 1 if successful else returns 0
//also prints required print statements for the output
int request_resources2(int customer_num, int request[]);

//request resource function for when the user inputs a list of request for a specific customer
//returns 1 if successful else 0
int request_resources(int customer_num, int request[]);

//prints the current state of all the matrices
void print_Curr_State();

/*releases resources used when the user inputs list of resources it wants to be released
 for a specific customer, returns 1 if successful and 0 if unsuccessful 
 its also used by the safety algorithm which is used for when the Run command is given by the user
*/
int release_resources(int customer, int request[]);
/* works out the safe sequence and then executes those threads in order of the safe sequence
also contains required print statements
*/
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
   //printing out the maximum required resources 2d array given
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
    char flush;
    
    //loop that keeps asking user for a command and exits only when 'Exit' entered
    while(1) {
        
        printf("\nEnter Command: ");
        fgets(check,sizeof(check),stdin);

        //checks if the user entered 'Exit' if true then exit the loop        
        if (strncmp(check, "Exit", 4) == 0) {
            break; //exit the loop
        }
        
        //checks if the user entered a string starting with RQ 
        //if yes then separate the requested resources and customer id
        //& convert the string to int and pass them to the request_resources funtion
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
                printf("\nState is unsafe, and request is unsatisfied");
            }
            else if(value==1){
                 printf("\nState is safe, and request is satisfied");
            }
           while ((flush = getchar()) != '\n' && flush != EOF);
        }

        //checks if the user entered a string starting with RL
        //if yes then separate the requested resources and customer id
        //& convert the string to int and pass them to the release_resources function
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
            while ((flush = getchar()) != '\n' && flush != EOF);
            //release resources
        }
        //checks if user entered a string 'Status' and if true then 
        //call the print_Curr_State function and print all the arrays
        else if(strncmp(check,"Status",6)==0){
            print_Curr_State();
            //print all the arrays
            printf(" ");
            
        }
        //checks if user entered a string 'Run' and if true then 
        //call the safety_algorithm function that first finds the safe sequence and then 
        // executes all the processes in order of the safe sequence
        else if(strncmp(check,"Run",3)==0){
            safety_algorithm();
            //run all processes using safety algorithm
            printf(" ");
        }
    }
	return 0;
}

/*releases resources used in main when the user inputs list of resources it wants to be released
 for a specific customer, returns 1 if successful and 0 if unsuccessful 
 its also used by the safety algorithm which is used for when the Run command is given by the user
*/
int release_resources(int customer,int request[]){

    for (int i=0; i!=NUM_OF_RESOURCES;i++){    
        int allocated=allocated_resources[customer][i];

        if(request[i]>allocated){
            
            return 0;

        }
    }
    for (int i=0; i!=NUM_OF_RESOURCES;i++){
        available_resources[i]= available_resources[i]+request[i];
        allocated_resources[customer][i]=allocated_resources[customer][i]-request[i];
    }
    
    return 1;

}

/* separate request resources function for safety algorithm returns 1 if successful else returns 0
also prints the required statements for the output*/
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
    printf("\n--> Customer/Thread %d",customer_num);
    int allo[4]={0,0,0,0};
    printf("\n    Allocated Resources: ");
    for(int x=0;x<NUM_OF_RESOURCES;x++){
        allo[x]= allocated_resources[customer_num][x];
        printf("%d ",allo[x]);
    }
    printf("\n    Remaining Resources: ");
    for(int x=0;x<NUM_OF_RESOURCES;x++){
        allo[x]= remaining_needed[customer_num][x];
        printf("%d ",allo[x]);
    }

    printf("\n    Available Resources: ");
    for(int x=0;x<NUM_OF_RESOURCES;x++){
        allo[x]= available_resources[x];
        printf("%d ",allo[x]);
    }
    printf("\n    Thread has started");
        
    for(int i=0;i!=NUM_OF_RESOURCES;i++){
        available_resources[i]= available_resources[i]-request[i];
        allocated_resources[customer_num][i]=allocated_resources[customer_num][i]+request[i];
        remaining_needed[customer_num][i]=remaining_needed[customer_num][i]-request[i];    
    }
return 1;
}

/*request resource function used in main for when the user inputs a
 list of request for a specific customer
 returns 1 if successful else 0
*/
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
        available_resources[i]= available_resources[i]-request[i];
        allocated_resources[customer_num][i]=allocated_resources[customer_num][i]+request[i];
        remaining_needed[customer_num][i]=remaining_needed[customer_num][i]-request[i];    
    }
return 1;
}

//prints all the current values of all the matrices
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

/* works out the safe sequence and then executes those threads in order of the safe sequence
also contains required print statements
*/
int safety_algorithm(){
    int safeseq[5]={0,0,0,0,0}, seq=0,check=0,finish[5]={0,0,0,0,0};
    int inc=0;

    //**Prints the safe sequence before the processes are executed**
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
        for(int i=0;i<NUM_OF_CUSTOMERS;i++)printf("%d ",safeseq[i]);
    }

    //**Execution of processes after the safe sequence has been identified**
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
                
                value= request_resources2(customer_num,request);

            }
            
            if(value==1){
                int allocated[4]={0,0,0,0};
                int allo[4]={0,0,0,0};
                for(int x=0;x<NUM_OF_RESOURCES;x++){
                    allocated[x]= allocated_resources[customer_num][x];
                }
                 printf("\n    Thread has finished");
                release_resources(customer_num,allocated);
                printf("\n    Thread is releasing resources");

                printf("\n    New Available: ");
                for(int x=0;x!=4;x++){
                    allo[x]= available_resources[x];
                    printf("%d ",allo[x]);
                }
                printf("\n-----------------------------------\n");
                
                count++;
            }
        }
        if(count==0)break;
    }
    return 0;
}


