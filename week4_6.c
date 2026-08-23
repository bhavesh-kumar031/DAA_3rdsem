#include <stdio.h>
#include <stdlib.h>

struct Event {
    int point;
    int type;
};

// Sort by point.
// If points are equal, START (+1) comes before END (-1).
int compare(const void *a, const void *b) {

    struct Event *x = (struct Event *)a;
    struct Event *y = (struct Event *)b;

    if (x->point != y->point)
        return x->point - y->point;

    return y->type - x->type;
}

int main() {

    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter intervals (left right):\n");

    for (int i = 0; i < n; i++) {

        int l, r;
        scanf("%d %d", &l, &r);

        // Start event
        events[2 * i].point = l;
        events[2 * i].type = 1;

        // End event
        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int active = 0;
    int maximum = 0;
    int answer = 0;

    for (int i = 0; i < 2 * n; i++) {

        active += events[i].type;

        if (active > maximum) {
            maximum = active;
            answer = events[i].point;
        }
    }

    printf("\nPoint with maximum overlapping intervals: %d\n", answer);
    printf("Maximum number of intervals: %d\n", maximum);

    return 0;
}