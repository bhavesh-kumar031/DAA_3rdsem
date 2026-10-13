
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fuel;
} Station;

int maxHeap[100005];
int heapSize = 0;

void push(int x) {
    int i = ++heapSize;

    while (i > 1 && maxHeap[i / 2] < x) {
        maxHeap[i] = maxHeap[i / 2];
        i /= 2;
    }

    maxHeap[i] = x;
}

int pop(void) {
    int result = maxHeap[1];
    int last = maxHeap[heapSize--];

    int i = 1, child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            maxHeap[child + 1] > maxHeap[child])
            child++;

        if (last >= maxHeap[child]) break;

        maxHeap[i] = maxHeap[child];
        i = child;
    }

    if (heapSize > 0) maxHeap[i] = last;

    return result;
}

int main(void) {
    int n, D, F;

    printf("Enter target distance, initial fuel, station count: ");
    if (scanf("%d %d %d", &D, &F, &n) != 3 ||
        D < 0 || F < 0 || n < 0 || n > 100000)
        return 1;

    Station s[n + 1];

    for (int i = 0; i < n; i++) {
        printf("Enter station distance and fuel: ");
        if (scanf("%d %d", &s[i].distance, &s[i].fuel) != 2 ||
            s[i].distance < 0 || s[i].fuel < 0)
            return 1;
    }

    // Add the destination as a station with zero fuel.
    s[n] = (Station){D, 0};
    n++;

    // Sort stations by distance.
    for (int i = 1; i < n; i++) {
        Station key = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].distance > key.distance) {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = key;
    }

    int current = 0, stops = 0, reachable = F;

    for (int i = 0; i < n; i++) {
        int gap = s[i].distance - current;

        while (reachable < gap) {
            if (heapSize == 0) {
                printf("Destination unreachable.\n");
                return 0;
            }

            reachable += pop();
            stops++;
        }

        reachable -= gap;
        current = s[i].distance;

        if (i < n - 1) push(s[i].fuel);
    }

    printf("Minimum refuelling stops = %d\n", stops);
    return 0;
}
