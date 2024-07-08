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

struct data_display
{
    int process_number;
    int from;
    int to;
};

struct data_FCFS
{
    int process_number;
    int cpu_burst;
    int arrival_time;
    int started_at;
    int ended_at;
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


        data_input_FCFS[ctr].started_at = 0;
        data_input_FCFS[ctr].ended_at = 0;
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
        printf("\n Process --> %d", display[ctr].process_number);
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

        // resetting
 
        

        // simulates doing the process by decrementing the cpu burst of the process into 0
        // elapsed time is then incremented signifying the current time after the processes
     
        display[display_ctr].process_number = data_input_FCFS[processing].process_number;
 
        // recording from - this is before process is done
        display[display_ctr].from = elapsed_time;
        // recording to - this is after the process is done
        elapsed_time += data_input_FCFS[processing].cpu_burst;
        display[display_ctr].to = elapsed_time;
        // CPU burst is now zero since the process is done
        data_input_FCFS[processing].cpu_burst = 0;

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
