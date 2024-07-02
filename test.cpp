#include<stdio.h>
#include<stdlib.h>


//
//1. FCFS - with arrival time 
//
//2. Shortest Job FIrst (Pre-emptive)
//
//3. Priority Scheduling with Shortest Job First and Arrival Time (Order of hierarchy)
//


const int max_input = 5;
int time_elapsed = 0;

//=====================================================================

struct data_FCFS{	
	int process_number;
	int cpu_burst;
	int arrival_time;	
	int started_at;
	int ended_at;
};


struct data_SJF{	
	int process_number;
	int cpu_burst;
	int started_at;
	int ended_at;
};

struct data_PSSJFAT{	
	int process_number;
	int cpu_burst;
	int arrival_time;	
	int priority_number;
		int started_a;
	int ended_at;	
};

//=====================================================================

struct data_FCFS data_input_FCFS[max_input];
struct data_SJF data_input_SJF [max_input];
struct data_SJF data_input_PSSJFAT[max_input];

//=====================================================================


void initialize_input_FCFS(){
	int num_input=0;
	int temp;
	int ctr = 0;
	printf("Enter number process to input \n");
	scanf("%d",&num_input);
	
	
	for(; ctr<num_input;ctr++){		
		printf("Proccess %d \n",ctr+1);
		data_input_FCFS[ctr].process_number = ctr+1;
		
		printf("Enter CPU Burst: ");
 		scanf("%d",&data_input_FCFS[ctr].cpu_burst);
		 		  	
		printf("Enter Arrival Time: ");	
 		scanf("%d",&data_input_FCFS[ctr].arrival_time); 		
		printf("\n");	
		
		data_input_FCFS[ctr].started_at = 0;
		data_input_FCFS[ctr].ended_at = 0;	
	}
	
		data_input_FCFS[ctr].process_number = 0;
		data_input_FCFS[ctr].cpu_burst = 0;
		data_input_FCFS[ctr].arrival_time = 0;	
		
	
}

void initialize_input_SJF(){
	
}


void initialize_input_PSSJFAT(){
	
	
}



void simulate_FCFS(){
	int ctr = 0;
	int num_input = 0;
	int processing = 0;
	bool done = false;


//checking max input
	while(data_input_FCFS[ctr].process_number!=0){	
		ctr++;
	}
	
	num_input = ctr;	
	ctr =0;
	
	
	while(done!=true){
		
//checking if its done...
		for(int ctr3=0;ctr3<num_input;ctr3++){
			if(data_input_FCFS[ctr].cpu_burst != 0){
				break;
			}
			else if(ctr3 == num_input){
				done = true;
				
			}			
		}
		
		
//checking what process should be next
		while(data_input_FCFS[ctr].process_number!=0){			
			if(data_input_FCFS[ctr].cpu_burst != 0){
				
			}
			
			ctr++;
		}
	
		
	


		time_elapsed++;
		ctr++;
		
	}
	
}











int main(){
	
	printf("test");
	initialize_input_FCFS();
	simulate_FCFS();
return 0;	
	
}
