#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;

    long long *a = malloc((size_t)n * sizeof(long long));
    long long *dp = malloc((size_t)n * sizeof(long long));

    if (a == NULL || dp == NULL) {
        free(a);
        free(dp);
        return 1;

    }

    printf("Enter positive array elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1 || a[i] <= 0) {
            printf("Elements must be positive integers.\n");
            free(a);
            free(dp);
            return 1;
        }
    }

    long long maximum = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = a[i];

        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] &&
                dp[j] <= 9223372036854775807LL - a[i] &&
                dp[j] + a[i] > dp[i]) {
                dp[i] = dp[j] + a[i];
            }
        }

        if (dp[i] > maximum)
            maximum = dp[i];
    }

    printf("Maximum sum of increasing subsequence: %lld\n",
           maximum);

    free(a);
    free(dp);
    return 0;
}