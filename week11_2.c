
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

int main(void) {
    int V, E, K, R;

    printf("Enter V E K R: ");

    if (scanf("%d %d %d %d", &V, &E, &K, &R) != 4 ||
        V <= 0 || E < 0 || K <= 0 || K > V || R < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Edge **graph = calloc((size_t)V, sizeof(Edge *));
    int *dist = malloc((size_t)V * sizeof(int));
    int *owner = malloc((size_t)V * sizeof(int));
    int *queue = malloc((size_t)V * sizeof(int));
    int *isHub = calloc((size_t)V, sizeof(int));

    if (!graph || !dist || !owner || !queue || !isHub) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d undirected edges (u v):\n", E);

    for (int i = 0; i < E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid edge input.\n");
            return 1;
        }

        Edge *a = malloc(sizeof(Edge));
        Edge *b = malloc(sizeof(Edge));

        if (!a || !b) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        a->to = v;
        a->next = graph[u];
        graph[u] = a;

        b->to = u;
        b->next = graph[v];
        graph[v] = b;
    }

    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }

    int front = 0, rear = 0;

    printf("Enter %d hub vertices in index order:\n", K);

    for (int i = 1; i <= K; i++) {
        int h;

        if (scanf("%d", &h) != 1 ||
            h < 0 || h >= V || isHub[h]) {
            printf("Invalid or duplicate hub vertex.\n");
            return 1;
        }

        isHub[h] = 1;
        dist[h] = 0;
        owner[h] = i;
        queue[rear++] = h;
    }

    while (front < rear) {
        int u = queue[front++];

        if (dist[u] >= R)
            continue;

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[rear++] = v;
            }
        }
    }

    printf("\nVertex\tOwner\tDistance\n");

    for (int v = 0; v < V; v++) {
        printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
    }

    for (int i = 0; i < V; i++) {
        Edge *e = graph[i];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    free(dist);
    free(owner);
    free(queue);
    free(isHub);

    return 0;
}
