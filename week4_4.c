

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int binarySearch(int a[], int left, int right, int target) {

    while (left <= right) {

        int mid = (left + right) / 2;

        if (a[mid] == target)
            return 1;

        if (a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}

int solve(int a[], int n, int k, int start, int target) {

    // We need only one element
    if (k == 1) {
        return binarySearch(a, start, n - 1, target);
    }

    for (int i = start; i < n; i++) {

        if (solve(a, n, k - 1,
                  i + 1,
                  target - a[i])) {
            return 1;
        }
    }

    return 0;
}

int main() {

    int n, k, T;

    printf("Enter n: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    qsort(S, n, sizeof(int), compare);

    if (solve(S, n, k, 0, T))
        printf("YES - %d elements add up to %d\n", k, T);
    else
        printf("NO - No such combination exists\n");

    return 0;
}