#include <stdio.h>

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int at;     // Arrival Time
    int pr;     // Priority
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int completed;
} Process;

void sortProcessesByArrival(Process p[], int n) {
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void findWaitingTime(Process p[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        int idx = -1;
        int minPriority = 10000;
        
        // Find the process with highest priority that has arrived and is not completed
        for (int j = 0; j < n; j++) {
            if (p[j].at <= currentTime && p[j].completed == 0) {
                if (p[j].pr < minPriority) {
                    minPriority = p[j].pr;
                    idx = j;
                }
            }
        }
        
        if (idx != -1) {
            p[idx].wt = currentTime - p[idx].at;
            p[idx].tat = p[idx].wt + p[idx].bt;
            currentTime += p[idx].bt;
            p[idx].completed = 1;
        } else {
            currentTime++;
            i--;
        }
    }
}

void findAverageTime(Process p[], int n) {
    int totalWT = 0, totalTAT = 0;

    // Calculate waiting time for all processes
    findWaitingTime(p, n);

    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    // Display processes along with all details
    printf("\nProcesses    Burst Time    Arrival Time    Priority    Waiting Time    Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].at, p[i].pr, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d\n", i + 1);
        p[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].completed = 0;
    }

    // Sort processes by arrival time
    sortProcessesByArrival(p, n);

    findAverageTime(p, n);

    return 0;
}