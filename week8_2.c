#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int n, V;

    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;

    int *coin = malloc((size_t)n * sizeof(int));
    if (coin == NULL)
        return 1;

    printf("Enter distinct coin denominations: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &coin[i]) != 1 || coin[i] <= 0) {
            printf("Invalid denomination.\n");
            free(coin);
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (coin[i] == coin[j]) {
                printf("Denominations must be distinct.\n");
                free(coin);
                return 1;
            }
        }
    }

    printf("Enter target amount: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid target amount.\n");
        free(coin);
        return 1;
    }

    unsigned long long *dp =
        calloc((size_t)V + 1, sizeof(unsigned long long));

    if (dp == NULL) {
        free(coin);
        return 1;
    }

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int amount = coin[i]; amount <= V; amount++) {
            if (ULLONG_MAX - dp[amount] < dp[amount - coin[i]]) {
                printf("Number of ways exceeds the supported range.\n");
                free(dp);
                free(coin);
                return 1;
            }

            dp[amount] += dp[amount - coin[i]];
        }
    }

    printf("Total number of ways: %llu\n", dp[V]);

    free(dp);
    free(coin);
    return 0;
}