
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
bool is_done = false;

int choice = 1;




struct data_input
{
    int process_number;
    int cpu_burst;
    int cpu_burst_ctr;
    int arrival_time;
    int priority;
    int finished_at;
};


// struct data_display
// {
//     struct data_input fcfs_data;
//     int process_number;
//     int cpu_burst_ctr_left;
//     int from;
//     int to;
// };

struct data_input* list = NULL; // Global variable for dynamic array
int list_size = 0;
// struct data_display display[20];

void initialize_input() {
    system("cls");
    int ctr = 0;
    printf_s("CPU SCHEDULING PROJECT\n");
    printf_s("_________________________\n");


    printf_s("1) First Come First Serve \n");
    printf_s("2) Shortest Job First With Arrival Time \n");
    printf_s("3) Shortest Job First with Arrival Time and Priority Number \n");
    printf_s("Choose a mode:");
    scanf_s("%d", &choice);
    system("cls");
    printf_s(" \n");

    if (choice == 1)
        printf_s("First Come First Serve\n");

    else if (choice == 2)
        printf_s("Shortest Job First With Arrival Time\n ");

    else if (choice == 3)
        printf_s("Shortest Job First with Arrival Time and Priority Number\n");



    printf_s("Enter number process to input \n");
    scanf_s("%d", &num_input);

    list = (struct data_input*)malloc(num_input * sizeof(struct data_input));




    for (; ctr < num_input; ctr++)
    {
        printf_s("Proccess %d \n", ctr + 1);
        list[ctr].process_number = ctr + 1;

        printf_s("Enter CPU Burst: ");
        scanf_s("%d", &list[ctr].cpu_burst_ctr);

        list[ctr].cpu_burst = list[ctr].cpu_burst_ctr;

        printf_s("Enter Arrival Time: ");
        scanf_s("%d", &list[ctr].arrival_time);

        if (choice == 3) {
            printf_s("Enter Priority: ");
            scanf_s("%d", &list[ctr].priority);
        }
        printf_s("---------------------------------------------------------\n");
        printf_s("\n");
    }
}


void display_result(int elapsed_time, int cpu_burst_ctr_left, int process_number) {
    if (is_processing == true) {
        printf_s("Process Number -> %d\n", process_number);
        printf_s("CPU Burst left -> %d\n ", cpu_burst_ctr_left);
    }
    else {
        printf_s("---WAITING---\n", process_number);
        printf_s("---WAITING---\n", cpu_burst_ctr_left);
    }
    printf_s("\n-----------------------------------------------[%d]\n", elapsed_time);

}



void get_minimum_AT()
{
    while (num_input != ctr)
    {
        // checks for the next process that has not yet been processed
        if (list[ctr].cpu_burst_ctr != 0) {
            // initialization  
            if (is_initialized == false) {
                is_initialized = true;
                min_arrival_time = list[ctr].arrival_time;
                processing = ctr;
            }
            // if same arrival time, process number takes precedence
            if (min_arrival_time == list[ctr].arrival_time && processing > ctr) {
                //do nothing(skip since its checking process to process therefore it is expected that this has more priority number)
            }
            // under normal cirumstances(arrival time is not the same)
            else if (min_arrival_time > list[ctr].arrival_time) {
                min_arrival_time = list[ctr].arrival_time;
                processing = ctr;
            }

        }
        // increment counter to move to check the next process 
        ctr++;
    }
}

void simulate_wait() {
    //--checks for waiting time--
    //waiting occurs when no process is being executed 
    //elapsed time is less than the min arrival time that has 0 > burst time
    if (elapsed_time < min_arrival_time) {
        // process number 100 signifies a waiting time/gap in between processes(if it occurs)
        // it starts at the current elapsed time

        // elapsed time added with the process next in line to process to simulate waiting
        // suppose current elapsed time is 0 and next process arrival time is 5, therefore
        // 0 + 5 -> elapsed time = 5 and the next process starts at 5(explained in the next part)
        elapsed_time += (min_arrival_time - elapsed_time);
        // for displaying ctr

    }
}


void print_result() {
    int tat = 0;
    int wt = 0;
    double avg_tat = 0;
    double avg_wt = 0;

    for (int ctr = 0; ctr < num_input; ctr++) {
        printf_s("\n---------------Proccess %d --------------------", ctr + 1);
        tat = list[ctr].finished_at - list[ctr].arrival_time;
        wt = tat - list[ctr].cpu_burst;

        avg_tat += tat;
        avg_wt += wt;
        printf_s("\nArrival Time -> %d ", list[ctr].arrival_time);
        printf_s("\nFinished Time -> %d", list[ctr].finished_at);
        printf_s("\nTurnaround Time -> %d", tat);
        printf_s("\nWaiting Time -> %d", wt);
    }
    avg_tat = avg_tat / num_input;
    avg_wt = avg_wt / num_input;
    printf_s("================================================");
    printf_s("\nAverage Turnaround Time -> %.2f", avg_tat);
    printf_s("\nAverage Waiting Time -> %.2f\n\n", avg_wt);

}







void check_done() {
    while (num_input != ctr)
    {
        // checking if one of the process still have CPU burst time
        if (list[ctr].cpu_burst_ctr != 0) {
            //  min_arrival_time = list[ctr].arrival_time;
              //incrementing to check the process 1 index ahead(this is to check if the end process indicator(process number 0 is next, then it means this is the last process))

            break;
        }
        ctr++;
    }
    if (num_input == ctr)
    {
        is_done = true;
        print_result();
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


void check_arrived() {
    //--checking if process had arrived--
    while (num_input != preempt_ctr) {
        if (list[preempt_ctr].cpu_burst_ctr != 0) {
            //checks if the process is still not is_done executing
            if (elapsed_time >= list[preempt_ctr].arrival_time) {
                is_processing = true;
                if (is_initialized_arrived == false) {
                    is_initialized_arrived = true;
                    processing = preempt_ctr;
                }
                if (choice != 3)
                    if (list[processing].cpu_burst_ctr > list[preempt_ctr].cpu_burst_ctr) {
                        processing = preempt_ctr;
                    }
                if (choice == 3) {
                    if (list[processing].priority > list[preempt_ctr].priority)
                        processing = preempt_ctr;

                    else if (list[processing].priority == list[preempt_ctr].priority){
                        if (list[processing].cpu_burst_ctr > list[preempt_ctr].cpu_burst_ctr)
                            processing = preempt_ctr;

                        else if (list[processing].cpu_burst_ctr == list[preempt_ctr].cpu_burst_ctr)
                            if (list[processing].arrival_time > list[preempt_ctr].arrival_time)
                                processing = preempt_ctr;


                    }

                }
            }
        }
        preempt_ctr++;
    }
}

void check_preempt() {
    //--checking for potential preempts---
   //preempts process are those that have not arrived yet
   //therefore preepmts only occur if more than one process had already arrived
    if (is_processing == true) {
        while (num_input != preempt_ctr_2) {

            //--initializing on first loop--
            if (list[preempt_ctr_2].cpu_burst_ctr != 0)
                if (list[processing].cpu_burst_ctr + elapsed_time > list[preempt_ctr_2].arrival_time)
                    if (elapsed_time < list[preempt_ctr_2].arrival_time)
                        if (preempt_ctr_2 != processing) {
                            if (is_preempt == false) {
                                is_preempt = true;
                                preempt = preempt_ctr_2;
                            }
                            if (is_preempt == true) {
                                if (list[preempt_ctr_2].arrival_time < list[preempt].arrival_time) {
                                    //--without priority--
                                    if (choice != 3)
                                        if (list[preempt].cpu_burst_ctr > list[preempt_ctr_2].cpu_burst_ctr)
                                            preempt = preempt_ctr_2;
                                    //--with priority
                                    if (choice == 3) {
                                        //--comparing priority--
                                                            // if the process has arrival time less <= elapsed time then it had arrived
                                        if (list[preempt_ctr_2].priority < list[preempt].priority) 
                                            preempt = preempt_ctr_2;
                                            //is_preempt = true;
                                            // 
                                        //--comparing cpu burst if same priority--
                                        else if (list[preempt_ctr_2].priority == list[preempt].priority){
                                            if (list[preempt].cpu_burst_ctr > list[preempt_ctr_2].cpu_burst_ctr) 
                                                preempt = preempt_ctr_2;

                                            else if(list[preempt].cpu_burst_ctr == list[preempt_ctr_2].cpu_burst_ctr)
                                                 if(list[preempt].process_number > list[preempt_ctr_2].process_number)
                                                    preempt = preempt_ctr_2;

                                        }

                                            
                                    }
                                }
                            }
                        }
            preempt_ctr_2++;
        }
    }
}



void simulate_CPU_scheduling() {

    printf_s("\n\n\n");
    printf_s("\n-----------------------------------------------[%d]\n", elapsed_time);

    while (!is_done)
    {
        check_done();
        check_arrived();
        // in FCFS no need to preempt
        if (choice != 1) {
            check_preempt();
        }
        if (is_processing == false)
        {
            get_minimum_AT();
            simulate_wait();
        }

        else if (is_preempt == true) {
            list[processing].cpu_burst_ctr -= list[preempt].arrival_time - elapsed_time;
            elapsed_time += list[preempt].arrival_time - elapsed_time;
        }

        else if (is_preempt == false) {
            elapsed_time += list[processing].cpu_burst_ctr;
            list[processing].cpu_burst_ctr = 0;
        }

        if (list[processing].cpu_burst_ctr == 0) {
            list[processing].finished_at = elapsed_time;
        }


        display_result(elapsed_time, list[processing].cpu_burst_ctr, list[processing].process_number);
        loop_reset();

    }
}


int main()
{
    int* list_size = (int*)malloc(sizeof(int));
    int again = 1;



    while (again == 1) {
        initialize_input();
        simulate_CPU_scheduling();
        printf_s("\ninput again? \n 1) Input again \n 2)End process\n");
        scanf_s("%d", &again);
    }
    return 0;
}




