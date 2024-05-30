#include<stdio.h>
#include<stdlib.h>

#define MAX 100

// Structure to represent a process
struct process {
    int id;
    int arrival_time;
    int burst_time;
};

// Function to sort processes based on arrival time
void sort_processes(struct process *arr, int n) {
    struct process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i].arrival_time > arr[j].arrival_time) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to perform FCFS scheduling
void fcfs(struct process *arr, int n) {
    int current_time = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < arr[i].arrival_time)
            current_time = arr[i].arrival_time;
        printf("Process %d is executing from time %d to %d\n", arr[i].id, current_time, current_time + arr[i].burst_time);
        current_time += arr[i].burst_time;
    }
}

int main() {
    int n, i, system_count = 0, user_count = 0;
    struct process *system_processes, *user_processes;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    system_processes = (struct process *) malloc(n * sizeof(struct process));
    user_processes = (struct process *) malloc(n * sizeof(struct process));

    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        struct process p;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p.arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p.burst_time);
        p.id = i + 1;
        if(p.arrival_time < 0 || p.burst_time <= 0) {
            printf("Invalid arrival time or burst time. Exiting.\n");
            exit(1);
        }
        if(p.arrival_time < 10)
            system_processes[system_count++] = p;
        else
            user_processes[user_count++] = p;
    }

    // Sort processes based on arrival time
    sort_processes(system_processes, system_count);
    sort_processes(user_processes, user_count);

    printf("\nExecuting system processes:\n");
    fcfs(system_processes, system_count);

    printf("\nExecuting user processes:\n");
    fcfs(user_processes, user_count);

    free(system_processes);
    free(user_processes);

    return 0;
}
