#include <stdio.h>

struct Process {
    int id;         
    int burstTime;  
    int priority;   
};

void sortProcesses(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process proc[], int n, int wait[], int turnaround[]) { 
    wait[0] = 0;

    for (int i = 1; i < n; i++) {
        wait[i] = proc[i - 1].burstTime + wait[i - 1]; 
    }

    for (int i = 0; i < n; i++) {
        turnaround[i] = proc[i].burstTime + wait[i];
    }
}

void printResults(struct Process proc[], int n, int wait[], int turnaround[]) {
    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].priority, wait[i], turnaround[i]);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int wait[n], turnaround[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1; 
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].burstTime, &proc[i].priority);
    }


    sortProcesses(proc, n);

    calculateTimes(proc, n, wait, turnaround);

    printResults(proc, n, wait, turnaround);

    return 0;
}

