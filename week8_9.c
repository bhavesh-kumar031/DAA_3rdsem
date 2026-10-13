
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define MAX_INTERVAL 100000

/*
    Returns 1 if the trajectory reaches 1.
    Returns 0 if integer overflow or memory allocation fails.
    The trajectory is stored dynamically using realloc().
*/
int collatz(uint64_t start, int printPath,
            uint64_t *steps, uint64_t *maxValue) {

    uint64_t *path = NULL;
    size_t size = 0, capacity = 0;
    uint64_t n = start;

    *steps = 0;
    *maxValue = start;

    while (1) {
        /* Increase capacity when necessary */
        if (size == capacity) {
            size_t newCapacity;

            if (capacity == 0) {
                newCapacity = 16;
            } else {
                if (capacity > SIZE_MAX / 2 / sizeof(*path)) {
                    free(path);
                    return 0;
                }
                newCapacity = capacity * 2;
            }

            uint64_t *temp = realloc(
                path, newCapacity * sizeof(*path)
            );

            if (temp == NULL) {
                free(path);
                return 0;
            }

            path = temp;
            capacity = newCapacity;
        }

        path[size++] = n;

        if (n == 1)
            break;

        /* Check overflow before calculating 3*n + 1 */
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            if (n > (UINT64_MAX - 1) / 3) {
                free(path);
                return 0;
            }
            n = 3 * n + 1;
        }

        (*steps)++;

        if (n > *maxValue)
            *maxValue = n;
    }

    if (printPath) {
        printf("Trajectory: ");
        for (size_t i = 0; i < size; i++) {
            printf("%" PRIu64, path[i]);

            if (i + 1 < size)
                printf(" -> ");
        }
        printf("\n");
    }

    free(path);
    return 1;
}

int main(void) {
    uint64_t n, a, b;
    uint64_t steps, maxValue;

    printf("Enter starting number n (n >= 1): ");
    if (scanf("%" SCNu64, &n) != 1 || n == 0) {
        printf("Invalid starting number.\n");
        return 1;
    }

    printf("\nAnalysis for n = %" PRIu64 "\n", n);

    if (collatz(n, 1, &steps, &maxValue)) {
        printf("Total steps: %" PRIu64 "\n", steps);
        printf("Maximum value reached: %" PRIu64 "\n",
               maxValue);
    } else {
        printf("Trajectory stopped: overflow or memory failure.\n");
    }

    printf("\nEnter interval [a, b]: ");
    if (scanf("%" SCNu64 " %" SCNu64, &a, &b) != 2 ||
        a == 0 || b < a) {
        printf("Invalid interval.\n");
        return 1;
    }

    if (b - a >= MAX_INTERVAL) {
        printf("Interval too large. Use at most %d values.\n",
               MAX_INTERVAL);
        return 1;
    }

    printf("\nCollatz analysis for [%" PRIu64 ", %" PRIu64 "]\n",
           a, b);

    printf("%-12s %-18s %-20s %-12s\n",
           "Start", "Steps", "Maximum value", "Status");

    for (uint64_t i = a; ; i++) {
        int success = collatz(i, 0, &steps, &maxValue);

        if (success) {
            printf("%-12" PRIu64 " %-18" PRIu64
                   " %-20" PRIu64 " Reached 1\n",
                   i, steps, maxValue);
        } else {
            printf("%-12" PRIu64
                   " Trajectory overflow or memory failure\n", i);
        }

        if (i == b)
            break;
    }

    return 0;
}
