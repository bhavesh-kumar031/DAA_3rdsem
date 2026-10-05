#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int main(void) {
    char X[MAX_LEN + 1], Y[MAX_LEN + 1];

    printf("Enter first string: ");
    if (scanf("%1000s", X) != 1)
        return 1;

    printf("Enter second string: ");
    if (scanf("%1000s", Y) != 1)
        return 1;

    int m = (int)strlen(X);
    int n = (int)strlen(Y);
    size_t cols = (size_t)n + 1;

    if ((size_t)(m + 1) > (size_t)-1 / cols / sizeof(int))
        return 1;

    int *dp = calloc((size_t)(m + 1) * cols, sizeof(int));
    if (dp == NULL)
        return 1;

    #define DP(i, j) dp[(size_t)(i) * cols + (j)]

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                DP(i, j) = DP(i - 1, j - 1) + 1;
            else if (DP(i - 1, j) >= DP(i, j - 1))
                DP(i, j) = DP(i - 1, j);
            else
                DP(i, j) = DP(i, j - 1);
        }
    }

    int length = DP(m, n);
    char *lcs = malloc((size_t)length + 1);

    if (lcs == NULL) {
        free(dp);
        return 1;
    }

    lcs[length] = '\0';

    int i = m, j = n, k = length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[k--] = X[i - 1];
            i--;
            j--;
        } else if (DP(i - 1, j) >= DP(i, j - 1)) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS length: %d\n", length);
    printf("Longest Common Subsequence: %s\n", lcs);

    free(lcs);
    free(dp);
    return 0;
}