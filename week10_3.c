
#include <stdio.h>

#define MAX 100005

int parent[MAX], sz[MAX];
long long weight[MAX];

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
    weight[u] += weight[v];
}

long long getMaximum(int n, int K) {
    long long maximum = -1LL;

    for (int i = 1; i <= n; i++) {
        if (parent[i] == i && sz[i] <= K) {
            if (weight[i] > maximum)
                maximum = weight[i];
        }
    }

    return maximum;
}

int main(void) {
    int n, m, K, u, v;
    long long w;

    printf("Enter vertices, edges and size limit K: ");
    scanf("%d %d %d", &n, &m, &K);

    printf("Enter vertex weights:\n");

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w);
        parent[i] = i;
        sz[i] = 1;
        weight[i] = w;
    }

    printf("Enter edges in the order they are added:\n");

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);

        unite(u, v);

        long long ans = getMaximum(n, K);

        if (ans == -1LL)
            printf("No eligible component\n");
        else
            printf("Maximum eligible component weight: %lld\n", ans);
    }

    return 0;
}
