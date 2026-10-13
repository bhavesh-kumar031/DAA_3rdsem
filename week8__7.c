#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter rod length: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid rod length.\n");
        return 1;
    }

    int *price = malloc((n + 1) * sizeof(int));
    int *dp = malloc((n + 1) * sizeof(int));
    int *firstCut = malloc((n + 1) * sizeof(int));

    if (price == NULL || dp == NULL || firstCut == NULL) {
        printf("Memory allocation failed.\n");
        free(price);
        free(dp);
        free(firstCut);
        return 1;
    }

    printf("Enter prices for lengths 1 to %d:\n", n);
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &price[i]) != 1) {
            printf("Invalid price input.\n");
            free(price);
            free(dp);
            free(firstCut);
            return 1;
        }
    }

    dp[0] = 0;
    firstCut[0] = 0;

    for (int len = 1; len <= n; len++) {
        dp[len] = price[len];
        firstCut[len] = len;

        for (int cut = 1; cut < len; cut++) {
            int revenue = price[cut] + dp[len - cut];

            if (revenue > dp[len]) {
                dp[len] = revenue;
                firstCut[len] = cut;
            }
        }
    }

    printf("\nMaximum revenue = %d\n", dp[n]);
    printf("Optimal piece lengths: ");

    int remaining = n;
    while (remaining > 0) {
        int cut = firstCut[remaining];
        printf("%d ", cut);
        remaining -= cut;
    }

    printf("\n");

    free(price);
    free(dp);
    free(firstCut);

    return 0;
}
