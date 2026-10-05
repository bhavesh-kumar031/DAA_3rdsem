#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, V;

    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;

    int *coin = malloc((size_t)n * sizeof(int));
    if (coin == NULL)
        return 1;

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &coin[i]) != 1 || coin[i] <= 0) {
            printf("Invalid denomination.\n");
            free(coin);
            return 1;
        }
    }

    printf("Enter target amount: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid target amount.\n");
        free(coin);
        return 1;
    }

    int *dp = malloc(((size_t)V + 1) * sizeof(int));
    if (dp == NULL) {
        free(coin);
        return 1;
    }

    for (int i = 0; i <= V; i++)
        dp[i] = V + 1;

    dp[0] = 0;

    for (int amount = 1; amount <= V; amount++) {
        for (int j = 0; j < n; j++) {
            if (coin[j] <= amount &&
                dp[amount - coin[j]] != V + 1) {
                int candidate = dp[amount - coin[j]] + 1;

                if (candidate < dp[amount])
                    dp[amount] = candidate;
            }
        }
    }

    if (dp[V] == V + 1)
        printf("Minimum coins: -1\n");
    else
        printf("Minimum coins: %d\n", dp[V]);

    free(dp);
    free(coin);
    return 0;
}