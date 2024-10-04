#include <stdio.h>

struct Process {
    int id;         
    int burstTime;  
    int remainingTime; 
};

void roundRobin(struct Process proc[], int n, int timeQuantum) {
    int time = 0;
    int completed = 0;
    int waitTime[n];
    int turnaroundTime[n];

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }

    while (completed < n) {
        int doneInThisCycle = 0;

        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                if (proc[i].remainingTime > timeQuantum) {
                    time += timeQuantum;
                    proc[i].remainingTime -= timeQuantum;
                } else {
                    time += proc[i].remainingTime;
                    waitTime[i] = time - proc[i].burstTime;
                    turnaroundTime[i] = time;
                    proc[i].remainingTime = 0;
                    completed++;
                    doneInThisCycle = 1;
                }
            }
        }

 
        if (!doneInThisCycle) break;
    }


    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitTime[i] + proc[i].burstTime;
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, waitTime[i], turnaroundTime[i]);
    }
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(proc, n, timeQuantum);

    return 0;
}

