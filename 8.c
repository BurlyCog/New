#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0; 

    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
  
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}
void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }
    int avg_wt = 0;
    for(int i = 0; i < n; i++){
    	avg_wt+=wt[i];
    }
    int avg_tat = 0;
    for(int i = 0; i < n; i++){
    	avg_tat+=tat[i];
    }
    printf("\n\nAvg WT: %d", avg_wt/n);
    printf("\nAvg TAT: %d", avg_tat/n);
}

int main() {
    int n; 
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n]; 

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; 
        printf("Enter burst time for process %d: ", processes[i]);
        scanf("%d", &bt[i]);
    }

    findavgTime(processes, n, bt);

    return 0;
}

