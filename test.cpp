#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT 5

int display_ctr = 0;
int time_elapsed = 0;

// for checking...
int max_loop = MAX_INPUT;
int num_input = 0;

//=====================================================================



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

    printf("\n\nFINAL,-->%d", data_input_FCFS[ctr + 1].cpu_burst);
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
    for (int ctr = 0; ctr < display_ctr-1; ctr++)
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

void simulate_FCFS()
{
    int ctr = 0;

    int processing = 0;
    int elapsed_time = 0;
    bool done = false;
    int loop_ctr = 0;
    int min_arrival_time = 0;
    while (!done && num_input >= loop_ctr)
    //remove the num_input >= loop_ctr for final
    {
        loop_ctr++;

        // checking if its done...
        while (data_input_FCFS[ctr].process_number != 0)
        {
            if (data_input_FCFS[ctr].cpu_burst != 0)
            {
                min_arrival_time = data_input_FCFS[ctr].arrival_time ;
                break;
            }
            if (data_input_FCFS[ctr].process_number == 0)
            {
                done = true;
            }
            ctr++;
        }
        
        // reseting
        ctr = 0;
        
        
        // checking what process should be next
        while (data_input_FCFS[ctr].process_number != 0)
        {
        // checks for the next process that has not yet been processed
            if (data_input_FCFS[ctr].cpu_burst != 0 && data_input_FCFS[ctr].arrival_time <= min_arrival_time)
            {
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                // processing = data_input_FCFS[ctr].process_number;
                processing = ctr;
            }
            
            ctr++;
        }
        
        // checking elapsed time if a procces had arrived 
        // adding another process for waiting time
        if(elapsed_time < min_arrival_time ){
            
        
        // process number 100 signifies a waiting time/gap in between processes(if it occurs)
        display[display_ctr].fcfs_data.process_number = 100;
        // it starts at the current elapsed time
        display[display_ctr].from = elapsed_time;
        
        
        // elapsed time added with the process next in line to process to simulate waiting
        // suppose current elapsed time is 0 and next process arrival time is 5, therefore
        // 0 + 5 -> elapsed time = 5 and the next process starts at 5(explained in the next part)
        elapsed_time += elapsed_time + min_arrival_time;
        display[display_ctr].to = elapsed_time;
        
        // for displaying ctr
        display_ctr++;
        }
        


        display[display_ctr].fcfs_data = data_input_FCFS[processing];
        // tracking of what process number is being processed
        display[display_ctr].process_number = data_input_FCFS[processing].process_number;
        
         // simulates doing the process by decrementing the cpu burst of the process into 0
        // elapsed time is then incremented signifying the current time after the processes
        
        // recording from - this is before process is done
        display[display_ctr].from = elapsed_time;
        // recording to - this is after the process is done
        elapsed_time += data_input_FCFS[processing].cpu_burst;
        display[display_ctr].to = elapsed_time;
        // CPU burst is now zero since the process is done
        display[display_ctr].CPU_burst_left = 0;
        data_input_FCFS[ctr].cpu_burst =0;

        // increments display counter to record new process
        display_ctr++;
        
        // full reset
        processing = 0;
        ctr =0;
    }
}

int main()
{
    initialize_input_FCFS();
    simulate_FCFS();
    display_result();
    return 0;
}
