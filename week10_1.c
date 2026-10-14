
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int parent[MAX], sz[MAX], parity[MAX];

int find(int x) {
    if (parent[x] == x)
        return x;

    int p = parent[x];
    parent[x] = find(parent[x]);
    parity[x] ^= parity[p];

    return parent[x];
}

int addEdge(int u, int v) {
    int ru = find(u);
    int pu = parity[u];

    int rv = find(v);
    int pv = parity[v];

    // Same component: check if u and v are on opposite sides.
    if (ru == rv)
        return (pu ^ pv) == 1;

    // Merge components with opposite parity constraint.
    if (sz[ru] < sz[rv]) {
        parent[ru] = rv;
        parity[ru] = pu ^ pv ^ 1;
        sz[rv] += sz[ru];
    } else {
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1;
        sz[ru] += sz[rv];
    }

    return 1;
}

int main(void) {
    int V, E, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        sz[i] = 1;
        parity[i] = 0;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);

        if (addEdge(u, v))
            printf("Edge (%d, %d) accepted\n", u, v);
        else
            printf("Edge (%d, %d) rejected: graph is not bipartite\n",
                   u, v);
    }

    return 0;
}
