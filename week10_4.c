
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005
#define MAXE 200005

int parent[MAX], sz[MAX], active[MAX];
long long value[MAX], sum[MAX], answer[MAX];

int head[MAX], to[2 * MAXE], nextEdge[2 * MAXE];
int edgeCount = 0;

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
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
    sum[u] += sum[v];
}

int main(void) {
    int n, m, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        parent[i] = i;
        sz[i] = 1;
        active[i] = 0;
        sum[i] = 0;
    }

    printf("Enter vertex values:\n");
    for (int i = 1; i <= n; i++)
        scanf("%lld", &value[i]);

    printf("Enter graph edges:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    int *p = malloc((n + 1) * sizeof(int));

    if (p == NULL)
        return 1;

    printf("Enter deletion order:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    // After all deletions, no vertices remain.
    long long maximum = 0;

    for (int i = n; i >= 1; i--) {
        // State immediately after deletion p[i].
        answer[i] = maximum;

        int x = p[i];
        active[x] = 1;
        parent[x] = x;
        sz[x] = 1;
        sum[x] = value[x];

        if (sum[x] > maximum)
            maximum = sum[x];

        for (int e = head[x]; e != -1; e = nextEdge[e]) {
            int y = to[e];

            if (active[y]) {
                unite(x, y);
                int root = find(x);

                if (sum[root] > maximum)
                    maximum = sum[root];
            }
        }
    }

    printf("Maximum component sum after each deletion:\n");

    for (int i = 1; i <= n; i++)
        printf("%lld\n", answer[i]);

    free(p);
    return 0;
}
