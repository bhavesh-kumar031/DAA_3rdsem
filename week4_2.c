#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, x;

    printf("Enter size of sets: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter x: ");
    scanf("%d", &x);

    // Sort both sets
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);

    int i = 0;
    int j = n - 1;
    int found = 0;

    // Two-pointer approach
    while (i < n && j >= 0) {

        int sum = S1[i] + S2[j];

        if (sum == x) {
            printf("YES\n");
            printf("Pair found: %d + %d = %d\n",
                   S1[i], S2[j], x);
            found = 1;
            break;
        }
        else if (sum < x) {
            i++;
        }
        else {
            j--;
        }
    }

    if (!found) {
        printf("NO\n");
    }

    return 0;
}