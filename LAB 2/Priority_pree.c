#include <stdio.h>

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int at;     // Arrival Time
    int pr;     // Priority
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int rt;     // Remaining Time
    int completed;
} Process;

void calculateTimes(Process p[], int n) {
    int currentTime = 0, completed = 0, minPriority;
    int shortest = 0;
    int isCompleted = 0;

    while (completed != n) {
        minPriority = 10000;  // Assuming priority numbers are not greater than 10000
        isCompleted = 0;
        
        // Find process with highest priority (smallest number)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0) {
                if (p[i].pr < minPriority) {
                    minPriority = p[i].pr;
                    shortest = i;
                    isCompleted = 1;
                }
                if (p[i].pr == minPriority) {
                    if (p[i].at < p[shortest].at) {
                        shortest = i;
                        isCompleted = 1;
                    }
                }
            }
        }

        if (isCompleted == 0) {
            currentTime++;
            continue;
        }

        // Execute the process
        p[shortest].rt--;
        currentTime++;

        if (p[shortest].rt == 0) {
            p[shortest].completed = 1;
            completed++;

            p[shortest].tat = currentTime - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
    }
}

void findAverageTime(Process p[], int n) {
    int totalWT = 0, totalTAT = 0;

    // Calculate times for all processes
    calculateTimes(p, n);

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
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    findAverageTime(p, n);

    return 0;
}