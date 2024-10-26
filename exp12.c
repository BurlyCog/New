#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50
#define FRAME_SIZE 5

// FIFO Page Replacement
void fifo(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1};
    int pageFaults = 0, index = 0;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = page;
            index = (index + 1) % FRAME_SIZE;
            pageFaults++;
        }

        printf("Page: %d | Frames: ", page);
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement
void lru(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1};
    int pageFaults = 0;
    int timestamps[MAX_PAGES] = {0};

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                found = 1;
                timestamps[j] = i; // Update timestamp
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < FRAME_SIZE; j++) {
                if (timestamps[j] < timestamps[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = page;
            timestamps[lruIndex] = i;
            pageFaults++;
        }

        printf("Page: %d | Frames: ", page);
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

// LFU Page Replacement
void lfu(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1};
    int freq[MAX_PAGES] = {0};
    int pageFaults = 0;

    printf("\nLFU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                found = 1;
                freq[page]++; // Increment frequency
                break;
            }
        }

        if (!found) {
            int lfuIndex = 0, minFreq = freq[frames[0]];

            for (int j = 1; j < FRAME_SIZE; j++) {
                if (freq[frames[j]] < minFreq || frames[j] == -1) {
                    lfuIndex = j;
                    minFreq = freq[frames[j]];
                }
            }
            frames[lfuIndex] = page;
            freq[page] = 1; // Set frequency for new page
            pageFaults++;
        }

        printf("Page: %d | Frames: ", page);
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (LFU): %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], n;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page numbers (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, n);
    lru(pages, n);
    lfu(pages, n);

    return 0;
}
