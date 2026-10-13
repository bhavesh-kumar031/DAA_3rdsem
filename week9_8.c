
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Meeting;

int compareMeeting(const void *a, const void *b) {
    const Meeting *x = a, *y = b;
    return (x->start > y->start) - (x->start < y->start);
}

int compareInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int n;

    printf("Enter number of meetings: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100000)
        return 1;

    if (n == 0) {
        printf("Minimum rooms required = 0\n");
        return 0;
    }

    Meeting meetings[n];
    int starts[n], ends[n];

    for (int i = 0; i < n; i++) {
        printf("Enter start and end time: ");

        if (scanf("%d %d", &meetings[i].start,
                  &meetings[i].end) != 2 ||
            meetings[i].start >= meetings[i].end)
            return 1;

        starts[i] = meetings[i].start;
        ends[i] = meetings[i].end;
    }

    qsort(meetings, n, sizeof(Meeting), compareMeeting);
    qsort(starts, n, sizeof(int), compareInt);
    qsort(ends, n, sizeof(int), compareInt);

    int i = 0, j = 0;
    int active = 0, maximum = 0;

    while (i < n) {
        if (j < n && starts[i] < ends[j]) {
            active++;
            if (active > maximum)
                maximum = active;
            i++;
        } else {
            active--;
            j++;
        }
    }

    printf("Minimum rooms required = %d\n", maximum);
    return 0;
}
