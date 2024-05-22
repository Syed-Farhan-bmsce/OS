#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
void findAvgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Process   Burst Time   Waiting Time   Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d         %d             %d                %d\n", processes[i], bt[i], wt[i], tat[i]);
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average waiting time = %f\n", total_wt / n);
    printf("Average turnaround time = %f\n", total_tat / n);
}

int main() {
    int value;
    int process[3];
    int burst_time[3];
    printf("enter the process id:\n");
    for(int i=0;i<3;i++){
        scanf("%d",&value);
        process[i]=value;
    }
     printf("enter the burst time:\n");
    for(int i=0;i<3;i++){
        scanf("%d",&value);
        burst_time[i]=value;
    }
    int n = 3;

    findAvgTime(process, n, burst_time);

    return 0;
}
