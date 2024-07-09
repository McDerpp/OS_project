#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT 5

int display_ctr = 0;
int time_elapsed = 0;
int num_input = 0;
int ctr = 0;
int processing = 0;
int elapsed_time = 0;
bool done = false;
bool isInitialized = false;
int min_arrival_time = 0;
int preempt = 0;



struct data_FCFS
{
    // process_number -> 100 == waiting
    // process_number -> 0 == done
    int process_number;
    int cpu_burst;
    int arrival_time;

};

struct data_SJF
{
    int process_number;
    int cpu_burst;
    int started_at;
    int ended_at;
};

struct data_PSSJFAT
{
    int process_number;
    int cpu_burst;
    int arrival_time;
    int priority_number;
    int started_at;
    int ended_at;
};


struct data_display
{
    struct data_FCFS fcfs_data;
    int process_number;
    int CPU_burst_left;
    int from;
    int to;
    
    
};

//=====================================================================

struct data_FCFS data_input_FCFS[MAX_INPUT];
struct data_SJF data_input_SJF[MAX_INPUT];
struct data_PSSJFAT data_input_PSSJFAT[MAX_INPUT];

struct data_display display[20];
//=====================================================================

void initialize_input_FCFS()
{

    int ctr = 0;
    printf("Enter number process to input \n");
    scanf("%d", &num_input);

    for (; ctr < num_input; ctr++)
    {
        printf("Proccess %d \n", ctr + 1);
        data_input_FCFS[ctr].process_number = ctr + 1;

        printf("Enter CPU Burst: ");
        scanf("%d", &data_input_FCFS[ctr].cpu_burst);

        printf("Enter Arrival Time: ");
        scanf("%d", &data_input_FCFS[ctr].arrival_time);
        printf("\n");
    }
    data_input_FCFS[ctr + 1].process_number = 0;
    data_input_FCFS[ctr + 1].cpu_burst = 0;
    data_input_FCFS[ctr + 1].arrival_time = 0;
}

void initialize_input_SJF()
{
}

void initialize_input_PSSJFAT()
{
}

void display_result()
{
    // 0 value is waiting time.
    for (int ctr = 0; ctr < display_ctr; ctr++)
    {
       
        printf("\n\n------------------------ Processing[%d]------------------------", ctr);
        if(display[ctr].fcfs_data.process_number != 100){
        printf("\n Process Number-> %d", display[ctr].fcfs_data.process_number);
        printf("\n CPU Burst Time left-> %d", display[ctr].CPU_burst_left);
        }
        else{
           printf("\n Process Number-> Waiting... "); 
           printf("\n CPU Burst Time left->  Waiting..." );
        }
        
        printf("\n Started -> %d", display[ctr].from);
        printf("\n ended --> %d", display[ctr].to);
        

        
    }
}


void get_minimum_AT()
{
    while (data_input_FCFS[ctr].process_number != 0)
    {
        // checks for the next process that has not yet been processed
        if (data_input_FCFS[ctr].cpu_burst != 0 && data_input_FCFS[ctr].arrival_time <= min_arrival_time)
            {
                // initialization  
        if(isInitialized == false){
            isInitialized = true;
            min_arrival_time = data_input_FCFS[ctr].arrival_time;
            processing = ctr;
    
        }
                // if same arrival time, process number takes precedence
        else if(min_arrival_time == data_input_FCFS[ctr].arrival_time && processing>ctr){
        //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
                }
                // under normal cirumstances(arrival time is not the same)
         else if(min_arrival_time != data_input_FCFS[ctr].arrival_time) {
            min_arrival_time = data_input_FCFS[ctr].arrival_time;
            processing = ctr;
                }
            }
            // increment counter to move to check the next process 
            ctr++;
        }
}

void simulate_wait(){
    if(elapsed_time < min_arrival_time ){
        // process number 100 signifies a waiting time/gap in between processes(if it occurs)
        display[display_ctr].fcfs_data.process_number = 100;
        // it starts at the current elapsed time
        display[display_ctr].from = elapsed_time;
        
        // elapsed time added with the process next in line to process to simulate waiting
        // suppose current elapsed time is 0 and next process arrival time is 5, therefore
        // 0 + 5 -> elapsed time = 5 and the next process starts at 5(explained in the next part)
        elapsed_time +=  (min_arrival_time - elapsed_time);
        display[display_ctr].to = elapsed_time;
        // for displaying ctr
        display_ctr++;
        }
}

void check_done(){
    while (data_input_FCFS[ctr].process_number != 0)
        {
            // checking if one of the process still have CPU burst time
        if (data_input_FCFS[ctr].cpu_burst != 0){
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                //incrementing to check the process 1 index ahead(this is to check if the end process indicator(process number 0 is next, then it means this is the last process))
            ctr++;
            break;
            }
            ctr++;
        }
        
        if (data_input_FCFS[ctr].process_number == 0)
            {
                done = true;
            }
            ctr = 0;
}

void check_preepmt(){
    
    int preempt_min_arrival = 0;
    while (data_input_FCFS[ctr].process_number != 0){
        
        //conditions
        //must not be the min_arrival_time
        //cpu burst time is not 0
        //arrival time is less than the preempt min arrival time(next minimum arrival time next to the actual one)
        if(ctr!=processing && data_input_FCFS[ctr].cpu_burst != 0 && data_input_FCFS[ctr].arrival_time <= preempt_min_arrival){
            
             // initialization  
        if(isInitialized == false){
            isInitialized = true;
            preempt_min_arrival = data_input_FCFS[ctr].arrival_time;
            preempt = ctr;
    
        }
                // if same arrival time, process number takes precedence
        else if(preempt_min_arrival == data_input_FCFS[ctr].arrival_time && preempt>ctr){
        //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
                }
                // under normal cirumstances(arrival time is not the same)
         else if(preempt_min_arrival != data_input_FCFS[ctr].arrival_time) {
            preempt_min_arrival = data_input_FCFS[ctr].arrival_time;
            preempt = ctr;
                }
            
            
            
            
            
            
            
            
            
            
            
            if(elapsed_time + data_input_FCFS[processing].cpu_burst){
            
            }
        }
        }
}

void reset_variables(){
    display_ctr = 0;
    time_elapsed = 0;
    num_input = 0;
    ctr = 0;
    processing = 0;
    elapsed_time = 0;
    done = false;
    isInitialized = false;
    min_arrival_time = 0;
}

void loop_reset(){
     // increments display counter to record new process
    display_ctr++;
    processing = 0;
    ctr =0;
    isInitialized = false;
    preempt = 0;
}

//not efficient, should consider merging the checking of done and minimum arrival to have less loops
void simulate_FCFS()
{
    while (!done)
    {
        check_done();
        get_minimum_AT();
        simulate_wait();
        
        //specific behavior for First Come First Serve
        display[display_ctr].fcfs_data = data_input_FCFS[processing];
        display[display_ctr].process_number = data_input_FCFS[processing].process_number;
        display[display_ctr].from = elapsed_time;
        elapsed_time += data_input_FCFS[processing].cpu_burst;
        display[display_ctr].to = elapsed_time;
        display[display_ctr].CPU_burst_left = 0;
        data_input_FCFS[processing].cpu_burst =0;
        

        loop_reset();
    }
}




// check for process with minimum arrival time
// execute process up until to the next minimum arrival time
//CPU burst time of the current process being executed will be deducted to the time elapsed up until the next minimum arrival time.
// check for the process of minimum arrival
// this scenario may print mulitple display of certain process consecutively if no other process arrived or no CPU burst less than the process currently executed.
// to solve this issue, consecutive occurance of process will be merged, the next display in queue will be checked if the process number is the same, if so it will be merged.
//hiearchy of variables to consider arrival_time > CPU_burst_time > process_number
// therefore i would be comparing the arrival time with elapsed time
//if more than 1 process has arrival_time<elapsed_time then we compare for the CPU_burst_time
//this will determine the next process to be executed.
//if they both have the same CPU_burst_time then we compare for the process_number
//
void simulate_SJF()
{
       while (!done)
    {
        check_done();
        get_minimum_AT();
        simulate_wait();
        
        display[display_ctr].fcfs_data = data_input_FCFS[processing];
        display[display_ctr].process_number = data_input_FCFS[processing].process_number;
        display[display_ctr].from = elapsed_time;
        elapsed_time += data_input_FCFS[processing].cpu_burst;
        display[display_ctr].to = elapsed_time;
        display[display_ctr].CPU_burst_left = 0;
        data_input_FCFS[processing].cpu_burst =0;
        

        // increments display counter to record new process
        display_ctr++;
        
        // full reset
        processing = 0;
        ctr =0;
        isInitialized = false;
    }
}










int main()
{
    initialize_input_FCFS();
    simulate_FCFS();
    display_result();
    return 0;
}
