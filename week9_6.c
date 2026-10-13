
#include <stdio.h>
#include <string.h>

#define ASCII 256
#define MAXLEN 100005

int main(void) {
    char s[MAXLEN], result[MAXLEN];
    int freq[ASCII] = {0};
    int last[ASCII];

    printf("Enter string (no spaces): ");
    if (scanf("%100000s", s) != 1) return 1;

    int K;
    printf("Enter K: ");
    if (scanf("%d", &K) != 1 || K < 0) return 1;

    int n = (int)strlen(s);

    if (K <= 1) {
        printf("Reorganised string = %s\n", s);
        return 0;
    }

    for (int i = 0; i < ASCII; i++)
        last[i] = -K;

    for (int i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for (int pos = 0; pos < n; pos++) {
        int best = -1;

        for (int c = 0; c < ASCII; c++) {
            if (freq[c] == 0) continue;
            if (pos - last[c] < K) continue;

            if (best == -1 || freq[c] > freq[best])
                best = c;
        }

        if (best == -1) {
            printf("Reorganisation impossible.\n");
            printf("Result = \"\"\n");
            return 0;
        }

        result[pos] = (char)best;
        freq[best]--;
        last[best] = pos;
    }

    result[n] = '\0';
    printf("Reorganised string = %s\n", result);

    return 0;
}
