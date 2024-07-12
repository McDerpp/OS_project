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


int min_arrival_time = 0;

int preempt = NULL;

int preempt_ctr = 0;
int preempt_ctr_2 = 0;

bool is_initialized = false;
bool is_initialized_preempt = false;
bool is_initialized_arrived = false;

bool is_processing = false;
bool is_preempt = false;
bool is_priority = false;
bool is_done = false;



struct data_input
{
    // process_number -> 100 == waiting
    // process_number -> 0 == is_done
    int process_number;
    int cpu_burst;
    int arrival_time;
    int priority;

};


struct data_display
{
    struct data_input fcfs_data;
    int process_number;
    int CPU_burst_left;
    int from;
    int to;
};

struct data_input list[MAX_INPUT];
struct data_display display[20];


void initialize_input_FCFS()
{

    int ctr = 0;
    printf("Enter number process to input \n");
    scanf_s("%d", &num_input);

    for (; ctr < num_input; ctr++)
    {
        printf("Proccess %d \n", ctr + 1);
        list[ctr].process_number = ctr + 1;

        printf("Enter CPU Burst: ");
        scanf_s("%d", &list[ctr].cpu_burst);

        printf_s("Enter Arrival Time: ");
        scanf_s("%d", &list[ctr].arrival_time);

        if(is_priority==true){
            printf_s("Enter Priority: ");
            scanf_s("%d", &list[ctr].priority);
        }
        printf("\n");
    }
    //indicator for the last element or to check if all the process are is_done
    list[ctr + 1].process_number = 0;
    list[ctr + 1].cpu_burst = 0;
    list[ctr + 1].arrival_time = 0;
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
    while (list[ctr].process_number != 0)
    {
        // checks for the next process that has not yet been processed
        if (list[ctr].cpu_burst != 0) {
            // initialization  
            if (is_initialized == false) {
                is_initialized = true;
                min_arrival_time = list[ctr].arrival_time;
                processing = ctr;
            }
            if (list[ctr].arrival_time <= min_arrival_time)
            {
                // if same arrival time, process number takes precedence
                if (min_arrival_time == list[ctr].arrival_time && processing > ctr) {
                    //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
                }
                // under normal cirumstances(arrival time is not the same)
                else if (min_arrival_time != list[ctr].arrival_time) {
                    min_arrival_time = list[ctr].arrival_time;
                    processing = ctr;
                }
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

    }
}


void check_is_done() {
    while (list[ctr].process_number != 0)
    {
        // checking if one of the process still have CPU burst time
        if (list[ctr].cpu_burst != 0) {
            //  min_arrival_time = list[ctr].arrival_time;
              //incrementing to check the process 1 index ahead(this is to check if the end process indicator(process number 0 is next, then it means this is the last process))
            ctr++;
            break;
        }
        ctr++;
    }

    if (list[ctr].process_number == 0)
    {
        is_done = true;
    }
    ctr = 0;
}


void loop_reset() {
    // increments display counter to record new process
    display_ctr++;
    processing = 0;
    ctr = 0;
    is_initialized = false;
    preempt_ctr = 0;
    preempt_ctr_2 = 0;
    is_processing = false;
    is_preempt = false;
    is_initialized_arrived = false;

}

//not efficient, should consider merging the checking of is_done and minimum arrival to have less loops
void simulate_FCFS()
{
    while (!is_done)
    {
        check_is_done();
        get_minimum_AT();
        simulate_wait();

        //specific behavior for First Come First Serve
        display[display_ctr].fcfs_data = list[processing];
        display[display_ctr].process_number = list[processing].process_number;
        display[display_ctr].from = elapsed_time;
        elapsed_time += list[processing].cpu_burst;
        display[display_ctr].to = elapsed_time;
        display[display_ctr].CPU_burst_left = 0;
        list[processing].cpu_burst = 0;


        loop_reset();
    }
}

/*
void check_arrived() {
    //--checking if process had arrived--
    while (list[preempt_ctr].process_number != 0) {
        if (list[preempt_ctr].cpu_burst != 0) {
            //checks if the process is still not is_done executing
            if (elapsed_time >= list[preempt_ctr].arrival_time) {
                //checks if anything had arrived                                    
                   //then checks for the cpu burst

                if (list[processing].cpu_burst > list[preempt_ctr].cpu_burst) {
                    is_processing = true;
                    processing = preempt_ctr;
                }

                if (list[processing].cpu_burst == 0) {
                    is_processing = true;
                    processing = preempt_ctr;
                }

                if (processing == preempt_ctr) {
                    is_processing = true;
                    processing = preempt_ctr;
                }

            }
            printf("now processing -> %d \n", processing);
        }
        preempt_ctr++;
    }
}
*/

void check_arrived() {
    //--checking if process had arrived--
    while (list[preempt_ctr].process_number != 0) {
        if (list[preempt_ctr].cpu_burst != 0) {
            //checks if the process is still not is_done executing
            if (elapsed_time >= list[preempt_ctr].arrival_time) {
                is_processing = true;

                if(is_initialized_arrived == false){
                    is_initialized_arrived = true;
                    processing = preempt_ctr;
                }


                if(is_priority == false)
                    if (list[processing].cpu_burst > list[preempt_ctr].cpu_burst) {                        
                        processing = preempt_ctr;
                    }
                             

                if (is_priority == true) {
                        if (list[processing].priority == list[preempt_ctr].priority)                            
                            if (list[processing].cpu_burst < list[preempt_ctr].cpu_burst) {
                                processing = preempt_ctr;
                            }
                         if (list[processing].priority > list[preempt_ctr].priority)
                                processing = preempt_ctr;                            
                }
            }
            printf("now processing -> %d \n", processing);
        }
        preempt_ctr++;
    }
}



/*
void check_preempt() {
    //--checking for potential preempts---
//preempts process are those that have note arrived yet
//therefore preepmts only occur if one or more process had already arrived
    if (is_processing == true) {
        while (list[preempt_ctr_2].process_number != 0) {
            if (preempt_ctr_2 != processing)
                if (elapsed_time < list[preempt_ctr_2].arrival_time)
                    if (list[preempt].cpu_burst > list[preempt_ctr_2].arrival_time) {
                        preempt = preempt_ctr_2;
                        is_preempt = true;
                        printf("preempting");
                    }
            preempt_ctr_2++;

        }
    }
}
*/

void check_preempt() {
 //--checking for potential preempts---
//preempts process are those that have not arrived yet
//therefore preepmts only occur if more than one process had already arrived
    if (is_processing == true) {
        while (list[preempt_ctr_2].process_number != 0) {

            //--initializing on first loop--
            if (preempt_ctr_2 != processing) {
                if (is_initialized_preempt == false) {
                    is_initialized_preempt = true;
                    preempt = preempt_ctr_2;
                }

                //--without priority--
                if (is_priority = false)
                    if (elapsed_time < list[preempt_ctr_2].arrival_time) // if the process has arrival time less <= elapsed time then it had arrived
                        //--comparing cpu burst--
                        if (list[preempt].cpu_burst > list[preempt_ctr_2].cpu_burst) {
                                preempt = preempt_ctr_2;
                                is_preempt = true;
                                printf("preempting");
                            }

                //--with priority
                if(is_priority=true)
                    //--comparing priority--
                    if (elapsed_time < list[preempt_ctr_2].arrival_time) { // if the process has arrival time less <= elapsed time then it had arrived
                        if (list[preempt_ctr_2].priority < list[preempt].priority) {
                            preempt = preempt_ctr_2;
                            is_preempt = true;
                        }

                        //--comparing cpu burst if same priority--
                        else if (list[preempt_ctr_2].priority == list[preempt].priority)
                            if(list[preempt].cpu_burst > list[preempt_ctr_2].cpu_burst) {
                                preempt = preempt_ctr_2;
                                is_preempt = true;

                        }
                    }

            }
            preempt_ctr_2++;
        }
    }
}
void simulate_SJF()
{
    printf("simulating");
    while (!is_done)
    {
        check_is_done();
        check_arrived();
        check_preempt();

        //--checks for waiting time--
        //waiting occurs when no process is being executed 
        //elapsed time is less than the min arrival time that has 0 > burst time

        display[display_ctr].from = elapsed_time;

        if (is_processing == false)
        {
            get_minimum_AT();
            simulate_wait();
        }

        else if (is_preempt == true) {
            list[processing].cpu_burst -= list[preempt].arrival_time - elapsed_time;
            elapsed_time += list[preempt].arrival_time - elapsed_time;
            display[display_ctr].to = elapsed_time;
        }
        else if (is_preempt == false) {
            elapsed_time += list[processing].cpu_burst;
            list[processing].cpu_burst = 0;
            display[display_ctr].to = elapsed_time;
        }

        if (is_processing == true) {
            display[display_ctr].fcfs_data = list[processing];
            display[display_ctr].process_number = list[processing].process_number;
            display[display_ctr].CPU_burst_left = list[processing].cpu_burst;
            display[display_ctr].to = elapsed_time;
        }
        loop_reset();
    }
}



int main()
{
    initialize_input_FCFS();
    simulate_FCFS();
    simulate_SJF();
    display_result();
    return 0;
}
