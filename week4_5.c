#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start;
    int end;
};

// Compare intervals according to starting point
int compare(const void *a, const void *b) {
    struct Interval *x = (struct Interval *)a;
    struct Interval *y = (struct Interval *)b;

    return x->start - y->start;
}

int main() {

    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval arr[n];

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    // Sort intervals by starting point
    qsort(arr, n, sizeof(struct Interval), compare);

    struct Interval result[n];

    int count = 0;

    // Start with the first interval
    result[0] = arr[0];
    count = 1;

    for (int i = 1; i < n; i++) {

        // If current interval overlaps with last interval
        if (arr[i].start <= result[count - 1].end) {

            // Extend the ending point if necessary
            if (arr[i].end > result[count - 1].end) {
                result[count - 1].end = arr[i].end;
            }
        }
        else {
            // No overlap, add new interval
            result[count] = arr[i];
            count++;
        }
    }

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", result[i].start, result[i].end);
    }

    printf("\n");

    return 0;
}