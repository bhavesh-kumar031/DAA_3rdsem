
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int parent[MAX], sz[MAX];
int A[MAX];

typedef struct {
    int root;
    int value;
} Pair;

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    parent[v] = u;
    sz[u] += sz[v];
}

int comparePairs(const void *a, const void *b) {
    const Pair *p = (const Pair *)a;
    const Pair *q = (const Pair *)b;

    if (p->root != q->root)
        return (p->root > q->root) - (p->root < q->root);

    return (p->value > q->value) - (p->value < q->value);
}

int main(void) {
    int n, m, u, v;

    printf("Enter n and number of edges: ");
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter permutation:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);

    printf("Enter allowed swap edges:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    Pair *pairs = malloc(n * sizeof(Pair));

    if (pairs == NULL)
        return 1;

    // Group values according to their component.
    for (int i = 1; i <= n; i++) {
        pairs[i - 1].root = find(i);
        pairs[i - 1].value = A[i];
    }

    qsort(pairs, n, sizeof(Pair), comparePairs);

    // Each component's values are now sorted.
    // Assign them to its positions in increasing index order.
    int *next = calloc(n + 1, sizeof(int));

    if (next == NULL) {
        free(pairs);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int root = pairs[i].root;

        while (next[root] < n && pairs[next[root]].root != root) {
            next[root]++;
        }

        // This branch is not needed for valid grouped pairs,
        // because values of each component are contiguous.
        A[1] = A[1];  // No operation; keeps the code standard C.
    }

    // Use a component cursor to distribute sorted values.
    int *cursor = calloc(n + 1, sizeof(int));

    if (cursor == NULL) {
        free(next);
        free(pairs);
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        int root = find(i);

        while (cursor[root] < n &&
               pairs[cursor[root]].root != root) {
            cursor[root]++;
        }

        if (cursor[root] < n) {
            A[i] = pairs[cursor[root]].value;
            cursor[root]++;
        }
    }

    printf("Lexicographically smallest permutation:\n");

    for (int i = 1; i <= n; i++)
        printf("%d ", A[i]);

    printf("\n");

    free(cursor);
    free(next);
    free(pairs);

    return 0;
}
