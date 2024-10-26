#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void findWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0; // First process has 0 waiting time

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void findTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void findAvgTime(struct Process processes[], int n) {
    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].id,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].waitingTime,
            processes[i].turnaroundTime);
        
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process IDs start from 1
        printf("Enter arrival time for Process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", processes[i].id);
        scanf("%d", &processes[i].burstTime);
    }

    // Sort processes by arrival time (FCFS requirement)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    findAvgTime(processes, n);
    return 0;
}

