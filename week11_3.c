
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100001
#define MAXL 10
#define HASH_SIZE 262144

char words[MAXN][MAXL + 1];
int hashTable[HASH_SIZE];
int distA[MAXN], distB[MAXN];
int queueA[MAXN], queueB[MAXN];

unsigned long long hashWord(const char *s) {
    unsigned long long h = 1469598103934665603ULL;

    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }

    return h;
}

int findWord(const char *s) {
    int pos = (int)(hashWord(s) & (HASH_SIZE - 1));

    while (hashTable[pos] != 0) {
        int id = hashTable[pos] - 1;

        if (strcmp(words[id], s) == 0)
            return id;

        pos = (pos + 1) & (HASH_SIZE - 1);
    }

    return -1;
}

void insertWord(int id) {
    int pos = (int)(hashWord(words[id]) & (HASH_SIZE - 1));

    while (hashTable[pos] != 0)
        pos = (pos + 1) & (HASH_SIZE - 1);

    hashTable[pos] = id + 1;
}

int expandLevel(int *queue, int *head, int *tail,
                int *here, int *other, int L) {
    int levelEnd = *tail;

    while (*head < levelEnd) {
        int u = queue[(*head)++];

        for (int j = 0; j < L; j++) {
            char original = words[u][j];

            for (char c = 'a'; c <= 'z'; c++) {
                if (c == original)
                    continue;

                words[u][j] = c;
                int v = findWord(words[u]);
                words[u][j] = original;

                if (v == -1)
                    continue;

                if (here[v] == -1) {
                    here[v] = here[u] + 1;
                    queue[(*tail)++] = v;
                }

                if (other[v] != -1)
                    return here[v] + other[v];
            }
        }
    }

    return -1;
}

int main(void) {
    int N;

    printf("Enter number of dictionary words: ");

    if (scanf("%d", &N) != 1 || N <= 0 || N > 100000) {
        printf("Invalid input.\n");
        return 1;
    }

    int L = 0;

    printf("Enter %d dictionary words:\n", N);

    for (int i = 0; i < N; i++) {
        if (scanf("%10s", words[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        int len = (int)strlen(words[i]);

        if (len < 1 || len > MAXL ||
            (i > 0 && len != L)) {
            printf("Invalid word length.\n");
            return 1;
        }

        L = len;

        for (int j = 0; j < len; j++) {
            if (words[i][j] < 'a' || words[i][j] > 'z') {
                printf("Use lowercase English letters only.\n");
                return 1;
            }
        }

        if (findWord(words[i]) != -1) {
            printf("Dictionary words must be unique.\n");
            return 1;
        }

        insertWord(i);
    }

    char A[MAXL + 1], B[MAXL + 1];

    printf("Enter starting word A and target word B: ");

    if (scanf("%10s %10s", A, B) != 2 ||
        (int)strlen(A) != L || (int)strlen(B) != L) {
        printf("Invalid input or word length.\n");
        return 1;
    }

    for (int i = 0; i < L; i++) {
        if (A[i] < 'a' || A[i] > 'z' ||
            B[i] < 'a' || B[i] > 'z') {
            printf("Use lowercase English letters only.\n");
            return 1;
        }
    }

    int start = findWord(A);
    int target = findWord(B);

    if (target == -1) {
        printf("Target word must be in the dictionary.\n");
        return 1;
    }

    if (strcmp(A, B) == 0) {
        printf("Minimum mutations: 0\n");
        return 0;
    }

    /* The starting word need not be in the dictionary. */
    if (start == -1) {
        start = N;
        strcpy(words[N], A);
        insertWord(N);
        N++;
    }

    for (int i = 0; i < N; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    int headA = 0, tailA = 0;
    int headB = 0, tailB = 0;

    queueA[tailA++] = start;
    queueB[tailB++] = target;

    distA[start] = 0;
    distB[target] = 0;

    while (headA < tailA && headB < tailB) {
        int answer;

        if (tailA - headA <= tailB - headB) {
            answer = expandLevel(
                queueA, &headA, &tailA,
                distA, distB, L
            );
        } else {
            answer = expandLevel(
                queueB, &headB, &tailB,
                distB, distA, L
            );
        }

        if (answer != -1) {
            printf("Minimum mutations: %d\n", answer);
            return 0;
        }
    }

    printf("Minimum mutations: -1\n");
    return 0;
}
