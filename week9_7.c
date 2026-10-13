
#include <stdio.h>

typedef long long ll;

#define MAX 100005

ll heap[MAX];
int size = 0;

void push(ll x) {
    int i = ++size;

    while (i > 1 && heap[i / 2] < x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = x;
}

ll pop(void) {
    ll result = heap[1];
    ll last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;

        if (child + 1 <= size &&
            heap[child + 1] > heap[child])
            child++;

        if (last >= heap[child]) break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0) heap[i] = last;
    return result;
}

ll top(void) {
    return heap[1];
}

int main(void) {
    int n;
    ll minimum = 0;

    printf("Enter array size: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX)
        return 1;

    for (int i = 0; i < n; i++) {
        ll x;

        if (scanf("%lld", &x) != 1 || x <= 0)
            return 1;

        if (x % 2 == 1) x *= 2;

        push(x);

        if (i == 0 || x < minimum)
            minimum = x;
    }

    ll answer = top() - minimum;

    while (top() % 2 == 0) {
        ll maximum = pop();
        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        push(maximum);

        ll deviation = top() - minimum;

        if (deviation < answer)
            answer = deviation;
    }

    printf("Minimum deviation = %lld\n", answer);
    return 0;
}
