
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

int main(void) {
    int V, E, S;
    long long C;

    printf("Enter V E S C: ");

    if (scanf("%d %d %d %lld", &V, &E, &S, &C) != 4) {
        printf("Invalid input format.\n");
        return 1;
    }

    if (V <= 0 || E < 0 || S < 0 || S >= V || C < 0) {
        printf("Invalid input values.\n");
        return 1;
    }

    Edge **graph = calloc((size_t)V, sizeof(Edge *));

    if (graph == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d edges as: u v weight\n", E);

    for (int i = 0; i < E; i++) {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            printf("Invalid edge input.\n");
            return 1;
        }

        if (u < 0 || u >= V || v < 0 || v >= V ||
            (w != 0 && w != 1)) {
            printf("Invalid edge values.\n");
            return 1;
        }

        Edge *e = malloc(sizeof(Edge));

        if (e == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        e->to = v;
        e->weight = w;
        e->next = graph[u];
        graph[u] = e;
    }

    int states = 2 * V;

    long long *dist =
        malloc((size_t)states * sizeof(long long));

    int *visited = calloc((size_t)states, sizeof(int));

    if (dist == NULL || visited == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < states; i++) {
        dist[i] = INF;
    }

    /* Even parity: state 2*v
       Odd parity:  state 2*v+1 */

    dist[2 * S] = 0;

    for (int step = 0; step < states; step++) {
        int u = -1;

        for (int i = 0; i < states; i++) {
            if (!visited[i] &&
                dist[i] != INF &&
                (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        int vertex = u / 2;
        int parity = u % 2;

        for (Edge *e = graph[vertex];
             e != NULL; e = e->next) {

            int nextParity = parity ^ e->weight;
            int nextState = 2 * e->to + nextParity;

            long long newDist = dist[u] + e->weight;

            if (newDist < dist[nextState]) {
                dist[nextState] = newDist;
            }
        }
    }

    printf("\nVertex\tMinimum Cost\n");

    for (int v = 0; v < V; v++) {
        long long evenCost = dist[2 * v];
        long long oddCost = dist[2 * v + 1];

        if (oddCost != INF) {
            oddCost += C;
        }

        long long answer =
            (evenCost < oddCost) ? evenCost : oddCost;

        if (answer == INF) {
            printf("%d\tUnreachable\n", v);
        } else {
            printf("%d\t%lld\n", v, answer);
        }
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
    free(visited);

    return 0;
}
