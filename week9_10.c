
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define MAXLEN 10005

int overlap(const char *a, const char *b) {
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    int limit = la < lb ? la : lb;

    for (int k = limit; k > 0; k--) {
        if (strncmp(a + la - k, b, k) == 0)
            return k;
    }

    return 0;
}

int main(void) {
    int n;
    char *s[MAXN];

    printf("Enter number of strings (1-%d): ", MAXN - 1);

    if (scanf("%d", &n) != 1 || n < 1 || n >= MAXN)
        return 1;

    for (int i = 0; i < n; i++) {
        char buffer[MAXLEN];

        printf("Enter string %d: ", i + 1);

        if (scanf("%10000s", buffer) != 1)
            return 1;

        s[i] = malloc(strlen(buffer) + 1);

        if (s[i] == NULL) return 1;

        strcpy(s[i], buffer);
    }

    // Remove strings already contained in another string.
    for (int i = 0; i < n; i++) {
        if (s[i] == NULL) continue;

        for (int j = 0; j < n; j++) {
            if (i == j || s[j] == NULL) continue;

            if (strstr(s[j], s[i]) != NULL) {
                free(s[i]);
                s[i] = NULL;
                break;
            }
        }
    }

    while (1) {
        int bestI = -1, bestJ = -1, bestOverlap = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == NULL) continue;

            for (int j = 0; j < n; j++) {
                if (i == j || s[j] == NULL) continue;

                int ov = overlap(s[i], s[j]);

                if (ov > bestOverlap) {
                    bestOverlap = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI == -1)
            break;

        size_t la = strlen(s[bestI]);
        size_t lb = strlen(s[bestJ]);

        char *merged = malloc(la + lb - bestOverlap + 1);

        if (merged == NULL) return 1;

        strcpy(merged, s[bestI]);
        strcat(merged, s[bestJ] + bestOverlap);

        free(s[bestI]);
        free(s[bestJ]);

        s[bestI] = merged;
        s[bestJ] = NULL;
    }

    printf("Greedy superstring = ");

    for (int i = 0; i < n; i++) {
        if (s[i] != NULL) {
            printf("%s\n", s[i]);
            free(s[i]);
        }
    }

    return 0;
}
