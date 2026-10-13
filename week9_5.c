
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of children: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 1000000)
        return 1;

    int rating[n], candy[n];

    printf("Enter ratings:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) return 1;
        candy[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1])
            candy[i] = candy[i + 1] + 1;
    }

    long long total = 0;

    printf("Candy distribution:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", candy[i]);
        total += candy[i];
    }

    printf("\nMinimum candies required = %lld\n", total);
    return 0;
}
