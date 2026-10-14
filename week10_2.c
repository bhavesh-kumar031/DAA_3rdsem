
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

int parent[MAX], sz[MAX], land[MAX];

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (sz[a] < sz[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    sz[a] += sz[b];

    return 1;
}

int main(void) {
    int R, C, K;
    int r, c, components = 0;

    printf("Enter rows, columns and number of operations: ");
    scanf("%d %d %d", &R, &C, &K);

    int total = R * C;

    for (int i = 0; i < total; i++) {
        parent[i] = i;
        sz[i] = 1;
        land[i] = 0;
    }

    // Up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter land positions (row column), using 0-based indexing:\n");

    for (int i = 0; i < K; i++) {
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid position\n");
            continue;
        }

        int id = r * C + c;

        // Duplicate land addition does not change component count.
        if (land[id]) {
            printf("%d\n", components);
            continue;
        }

        land[id] = 1;
        components++;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < R &&
                nc >= 0 && nc < C) {

                int nid = nr * C + nc;

                if (land[nid] && unite(id, nid))
                    components--;
            }
        }

        printf("%d\n", components);
    }

    return 0;
}
