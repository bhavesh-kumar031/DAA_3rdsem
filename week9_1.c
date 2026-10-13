
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double value, weight, decay;
} Item;

int main(void) {
    int n;
    double W;

    printf("Enter number of items and capacity: ");
    if (scanf("%d %lf", &n, &W) != 2 || n <= 0 || W < 0)
        return 1;

    Item a[n];

    for (int i = 0; i < n; i++) {
        a[i].id = i + 1;
        printf("Enter value, weight, decay rate for item %d: ", i + 1);
        if (scanf("%lf %lf %lf",
                  &a[i].value, &a[i].weight, &a[i].decay) != 3 ||
            a[i].weight <= 0 || a[i].decay < 0)
            return 1;
    }

    double total = 0, time = 0;
    int used[n];

    for (int i = 0; i < n; i++) used[i] = 0;

    while (W > 1e-9) {
        int best = -1;
        double bestDensity = 0;

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            double density =
                a[i].value / a[i].weight - a[i].decay * time;

            if (best == -1 || density > bestDensity) {
                best = i;
                bestDensity = density;
            }
        }

        if (best == -1 || bestDensity <= 0) break;

        double take = (W < a[best].weight)
                    ? W : a[best].weight;

        double effectiveValue =
            bestDensity * take;

        printf("Item %d: take %.4f units at time %.2f\n",
               a[best].id, take, time);

        total += effectiveValue;
        W -= take;
        used[best] = 1;
        time += 1.0;
    }

    printf("Total value = %.4f\n", total);
    printf("Unused capacity = %.4f\n", W);

    return 0;
}
