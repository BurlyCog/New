#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200

// Function to simulate FCFS Disk Scheduling
void fcfs(int requests[], int n, int head) {
    int totalSeekTime = 0;
    int currentPosition = head;

    printf("\nFCFS Disk Scheduling:\n");
    printf("Order of requests: ");
    for (int i = 0; i < n; i++) {
        int seekTime = abs(currentPosition - requests[i]);
        totalSeekTime += seekTime;
        currentPosition = requests[i];
        printf("%d ", requests[i]);
    }
    printf("\nTotal Seek Time (FCFS): %d\n", totalSeekTime);
}

// Function to simulate SCAN Disk Scheduling
void scan(int requests[], int n, int head, int direction) {
    int totalSeekTime = 0;
    int currentPosition = head;
    int seekSequence[MAX_CYLINDERS];
    int seekIndex = 0;

    // Sort the requests array
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Add head to the seek sequence
    if (direction == 1) { // Moving right
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                seekSequence[seekIndex++] = head;
                for (int j = i; j < n; j++) {
                    seekSequence[seekIndex++] = requests[j];
                }
                break;
            }
        }
        // Add the end of the disk
        seekSequence[seekIndex++] = MAX_CYLINDERS - 1;
        // Then move left
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                seekSequence[seekIndex++] = requests[i];
            }
        }
    } else { // Moving left
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                seekSequence[seekIndex++] = head;
                for (int j = i; j >= 0; j--) {
                    seekSequence[seekIndex++] = requests[j];
                }
                break;
            }
        }
        // Add the beginning of the disk
        seekSequence[seekIndex++] = 0;
        // Then move right
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                seekSequence[seekIndex++] = requests[i];
            }
        }
    }

    // Calculate total seek time
    for (int i = 0; i < seekIndex - 1; i++) {
        totalSeekTime += abs(seekSequence[i] - seekSequence[i + 1]);
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seekIndex; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time (SCAN): %d\n", totalSeekTime);
}

// Function to simulate C-SCAN Disk Scheduling
void cscan(int requests[], int n, int head) {
    int totalSeekTime = 0;
    int currentPosition = head;
    int seekSequence[MAX_CYLINDERS];
    int seekIndex = 0;

    // Sort the requests array
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // C-SCAN Algorithm
    seekSequence[seekIndex++] = head;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            seekSequence[seekIndex++] = requests[i];
        }
    }
    // Jump to the end of the disk
    seekSequence[seekIndex++] = MAX_CYLINDERS - 1;
    // Jump to the beginning of the disk
    seekSequence[seekIndex++] = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            seekSequence[seekIndex++] = requests[i];
        }
    }

    // Calculate total seek time
    for (int i = 0; i < seekIndex - 1; i++) {
        totalSeekTime += abs(seekSequence[i] - seekSequence[i + 1]);
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seekIndex; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time (C-SCAN): %d\n", totalSeekTime);
}

int main() {
    int n, head, direction;
    int requests[MAX_CYLINDERS];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    fcfs(requests, n, head);
    scan(requests, n, head, direction);
    cscan(requests, n, head);

    return 0;
}
