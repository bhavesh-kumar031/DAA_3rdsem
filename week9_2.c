
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct {
    long long freq;
    int left, right, symbol;
} Node;

typedef struct {
    unsigned char symbol;
    int length;
} SymbolCode;

Node tree[2 * MAX];
int nodeCount = 0;

int newNode(long long freq, int left, int right, int symbol) {
    int id = nodeCount++;
    tree[id] = (Node){freq, left, right, symbol};
    return id;
}

int compareSymbol(const void *a, const void *b) {
    const SymbolCode *x = a, *y = b;

    if (x->length != y->length)
        return x->length - y->length;

    return (int)x->symbol - (int)y->symbol;
}

void getLengths(int node, int depth, int lengths[]) {
    if (tree[node].symbol >= 0) {
        lengths[tree[node].symbol] = depth ? depth : 1;
        return;
    }

    getLengths(tree[node].left, depth + 1, lengths);
    getLengths(tree[node].right, depth + 1, lengths);
}

int main(void) {
    int n;
    long long freq[MAX];
    int active[2 * MAX] = {0};
    int lengths[MAX] = {0};

    printf("Enter number of symbols (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
        return 1;

    for (int i = 0; i < n; i++) {
        printf("Enter frequency of symbol %c: ", i + 1);
        if (scanf("%lld", &freq[i]) != 1 || freq[i] <= 0)
            return 1;

        active[i] = 1;
        newNode(freq[i], -1, -1, i);
    }

    int remaining = n;

    while (remaining > 1) {
        int first = -1, second = -1;

        for (int i = 0; i < nodeCount; i++) {
            if (!active[i]) continue;

            if (first == -1 || tree[i].freq < tree[first].freq) {
                second = first;
                first = i;
            } else if (second == -1 ||
                       tree[i].freq < tree[second].freq) {
                second = i;
            }
        }

        active[first] = active[second] = 0;

        int parent = newNode(tree[first].freq + tree[second].freq,
                             first, second, -1);

        active[parent] = 1;
        remaining--;
    }

    int root = nodeCount - 1;
    getLengths(root, 0, lengths);

    SymbolCode codes[MAX];

    for (int i = 0; i < n; i++) {
        codes[i].symbol = (unsigned char)i;
        codes[i].length = lengths[i];
    }

    qsort(codes, n, sizeof(SymbolCode), compareSymbol);

    unsigned long long code = 0;
    int previousLength = codes[0].length;

    printf("\nCanonical Huffman Codebook:\n");

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            code++;
            code <<= codes[i].length - previousLength;
        }

        printf("Symbol %c | Frequency %lld | Code ",
               codes[i].symbol + 1, freq[codes[i].symbol]);

        for (int bit = codes[i].length - 1; bit >= 0; bit--)
            printf("%d", (int)((code >> bit) & 1ULL));

        printf("\n");
        previousLength = codes[i].length;
    }

    return 0;
}
