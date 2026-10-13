
#include <stdio.h>
#include <limits.h>

#define MAX 505

typedef long long ll;

ll w[MAX], prefix[MAX];
ll dp[MAX][MAX];
int split[MAX][MAX];

void printTree(int i, int j) {
    if (i == j) {
        printf("Leaf(%d)", i + 1);
        return;
    }

    int k = split[i][j];

    printf("(");
    printTree(i, k);
    printf(", ");
    printTree(k + 1, j);
    printf(")");
}

int main(void) {
    int n;

    printf("Enter number of weights (1-%d): ", MAX - 1);
    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX)
        return 1;

    prefix[0] = 0;

    for (int i = 1; i <= n; i++) {
        printf("Enter weight %d: ", i);

        if (scanf("%lld", &w[i]) != 1 || w[i] < 0)
            return 1;

        prefix[i] = prefix[i - 1] + w[i];
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;

            ll sum = prefix[j] - prefix[i - 1];
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                ll cost = dp[i][k] + dp[k + 1][j] + sum;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("Minimum weighted path length = %lld\n", dp[1][n]);

    printf("Optimal alphabetic tree structure:\n");
    printTree(1, n);
    printf("\n");

    return 0;
}
