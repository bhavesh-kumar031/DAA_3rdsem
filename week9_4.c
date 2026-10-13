
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll heap[100005];
int size = 0;

void push(ll x) {
    int i = ++size;

    while (i > 1 && heap[i / 2] > x) {
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
            heap[child + 1] < heap[child])
            child++;

        if (last <= heap[child]) break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0) heap[i] = last;
    return result;
}

int main(void) {
    int n;

    printf("Enter number of sticks: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100000)
        return 1;

    for (int i = 0; i < n; i++) {
        ll length;
        scanf("%lld", &length);

        if (length < 0) return 1;
        push(length);
    }

    ll totalCost = 0;

    while (size > 1) {
        ll x = pop();
        ll y = pop();
        ll combined = x + y;

        totalCost += combined;
        push(combined);
    }

    printf("Minimum total cost = %lld\n", totalCost);
    return 0;
}
