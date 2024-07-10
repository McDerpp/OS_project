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
bool isInitialized_preempt = false;
int min_arrival_time = 0;

int preempt = NULL;
int preempt_arrival = NULL;




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
    scanf_s("%d", &num_input);

    for (; ctr < num_input; ctr++)
    {
        printf("Proccess %d \n", ctr + 1);
        data_input_FCFS[ctr].process_number = ctr + 1;

        printf("Enter CPU Burst: ");
        scanf_s("%d", &data_input_FCFS[ctr].cpu_burst);

        printf_s("Enter Arrival Time: ");
        scanf_s("%d", &data_input_FCFS[ctr].arrival_time);
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
        if (display[ctr].fcfs_data.process_number != 100) {
            printf("\n Process Number-> %d", display[ctr].fcfs_data.process_number);
            printf("\n CPU Burst Time left-> %d", display[ctr].CPU_burst_left);
        }
        else {
            printf("\n Process Number-> Waiting... ");
            printf("\n CPU Burst Time left->  Waiting...");
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
            if (isInitialized == false) {
                isInitialized = true;
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                processing = ctr;
            }
            // if same arrival time, process number takes precedence
            else if (min_arrival_time == data_input_FCFS[ctr].arrival_time && processing > ctr) {
                //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
            }
            // under normal cirumstances(arrival time is not the same)
            else if (min_arrival_time != data_input_FCFS[ctr].arrival_time) {
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                processing = ctr;
            }
        }
        // increment counter to move to check the next process 
        ctr++;
    }
}

void simulate_wait() {
    if (elapsed_time < min_arrival_time) {
        // process number 100 signifies a waiting time/gap in between processes(if it occurs)
        display[display_ctr].fcfs_data.process_number = 100;
        // it starts at the current elapsed time
        display[display_ctr].from = elapsed_time;

        // elapsed time added with the process next in line to process to simulate waiting
        // suppose current elapsed time is 0 and next process arrival time is 5, therefore
        // 0 + 5 -> elapsed time = 5 and the next process starts at 5(explained in the next part)
        elapsed_time += (min_arrival_time - elapsed_time);
        display[display_ctr].to = elapsed_time;
        // for displaying ctr
        display_ctr++;
    }
}

void check_done() {
    while (data_input_FCFS[ctr].process_number != 0)
    {
        // checking if one of the process still have CPU burst time
        if (data_input_FCFS[ctr].cpu_burst != 0) {
          //  min_arrival_time = data_input_FCFS[ctr].arrival_time;
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

void reset_variables() {
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

void loop_reset() {
    // increments display counter to record new process
    display_ctr++;
    processing = 0;
    ctr = 0;
    isInitialized = false;

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
        data_input_FCFS[processing].cpu_burst = 0;


        loop_reset();
    }
}


void preempt_process() {
    while (data_input_FCFS[ctr].process_number != 0)
    {
        // checks for the next process that has not yet been processed
        if (data_input_FCFS[ctr].cpu_burst != 0)
            if(data_input_FCFS[ctr].arrival_time < min_arrival_time)
        {
            // initialization  
            if (isInitialized == false) {
                isInitialized = true;
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                processing = ctr;
            }
            // if same arrival time, process number takes precedence
            else if (min_arrival_time == data_input_FCFS[ctr].arrival_time && processing > ctr) {
                //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
            }
            // under normal cirumstances(arrival time is not the same)
            else if (min_arrival_time != data_input_FCFS[ctr].arrival_time) {
                min_arrival_time = data_input_FCFS[ctr].arrival_time;
                processing = ctr;
            }
        }
        // increment counter to move to check the next process 
        ctr++;
    }

}





void simulate_SJF()
{
    int preempt_ctr = 0;
    int preempt_ctr_2 = 0;
    int waiting_ctr = 0;
    bool isProcessing = false;
    bool isPreempt = false;


    printf("simulating");
    while (!done)
    {

        check_done();
        //--checking if process had arrived--
        while (data_input_FCFS[preempt_ctr].process_number != 0) {
            if (data_input_FCFS[preempt_ctr].cpu_burst != 0) {
                //checks if the process is still not done executing
                if (elapsed_time >= data_input_FCFS[preempt_ctr].arrival_time) {
                    //checks if anything had arrived                                    
                       //then checks for the cpu burst

                    if (data_input_FCFS[processing].cpu_burst > data_input_FCFS[preempt_ctr].cpu_burst) {
                        isProcessing = true;
                        processing = preempt_ctr;
                    }

                    if (data_input_FCFS[processing].cpu_burst == 0) {
                        isProcessing = true;
                        processing = preempt_ctr;

                    }


                    if (processing == preempt_ctr) {
                        isProcessing = true;
                        processing = preempt_ctr;
                    }

                   



                }
                

                printf("now processing -> %d \n", processing);
            }
            preempt_ctr++;
        }

        //--checking for potential preempts---
        //preempts process are those that have note arrived yet
        //therefore preepmts only occur if one or more process had already arrived
        if (isProcessing == true) {
            while (data_input_FCFS[preempt_ctr_2].process_number != 0) {
                if (preempt_ctr_2 != processing)
                    if (elapsed_time < data_input_FCFS[preempt_ctr_2].arrival_time)
                        if (data_input_FCFS[preempt].cpu_burst > data_input_FCFS[preempt_ctr_2].arrival_time) {
                            preempt = preempt_ctr_2;
                            isPreempt = true;
                            printf("preempting");
                        }
                preempt_ctr_2++;
                
            }
        }

        //--checks for waiting time--
        //waiting occurs when no process is being executed 
        //elapsed time is less than the min arrival time that has 0 > burst time
        if (isProcessing == false)
            while (data_input_FCFS[waiting_ctr].process_number != 0)
            {
                get_minimum_AT();
                simulate_wait();
                waiting_ctr++;
            }

        display[display_ctr].from = elapsed_time;
        display[display_ctr].fcfs_data = data_input_FCFS[processing];
        display[display_ctr].process_number = data_input_FCFS[processing].process_number;

        if(isPreempt == true){
            data_input_FCFS[processing].cpu_burst -= data_input_FCFS[preempt].arrival_time - elapsed_time;
            elapsed_time += data_input_FCFS[preempt].cpu_burst;
        }

        if (isPreempt == false) {
            elapsed_time += data_input_FCFS[processing].cpu_burst;
            data_input_FCFS[processing].cpu_burst =0;            
        }


        display[display_ctr].to = elapsed_time;
        display[display_ctr].CPU_burst_left = data_input_FCFS[processing].cpu_burst;


        loop_reset();
        preempt_ctr = 0;
        preempt_ctr_2 = 0;
        waiting_ctr = 0;
        isProcessing = false;
        isPreempt = false;
    }

}








int main()
{
    initialize_input_FCFS();
    // simulate_FCFS();
    simulate_SJF();
    display_result();
    return 0;
}
