
#include <stdio.h>

#define MAX 100

double e[MAX + 2][MAX + 1];
double w[MAX + 2][MAX + 1];
int root[MAX + 2][MAX + 1];

void printTree(int i, int j) {
    if (i > j) {
        printf("d%d", j);
        return;
    }

    int r = root[i][j];

    printf("k%d(", r);
    printTree(i, r - 1);
    printf(", ");
    printTree(r + 1, j);
    printf(")");
}

int main(void) {
    int n;
    double p[MAX + 1], q[MAX + 1];

    printf("Enter number of keys (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of keys.\n");
        return 1;
    }

    printf("Enter successful search probabilities p[1..n]:\n");
    for (int i = 1; i <= n; i++) {
        if (scanf("%lf", &p[i]) != 1 ||
            p[i] < 0.0 || p[i] > 1.0) {
            printf("Invalid probability.\n");
            return 1;
        }
    }

    printf("Enter unsuccessful search probabilities q[0..n]:\n");
    for (int i = 0; i <= n; i++) {
        if (scanf("%lf", &q[i]) != 1 ||
            q[i] < 0.0 || q[i] > 1.0) {
            printf("Invalid probability.\n");
            return 1;
        }
    }

    /* Empty subtrees */
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* Build optimal subtrees of increasing length */
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            w[i][j] = w[i][j - 1] + p[j] + q[j];
            e[i][j] = 1e100;

            for (int r = i; r <= j; r++) {
                double cost = e[i][r - 1]
                            + e[r + 1][j]
                            + w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost = %.6f\n",
           e[1][n]);

    printf("Optimal BST structure:\n");
    printTree(1, n);
    printf("\n");

    return 0;
}
