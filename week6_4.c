#include <stdio.h>

#define MAX 1000

long long totalCost = 0;
long long reversalCount = 0;

/* Reverse elements from l to r */
void reverseArray(int p[], int l, int r)
{
    int i, j, temp;

    if(l > r)
        return;

    /* Cost of reversal */
    totalCost += (r - l + 1);
    reversalCount++;

    i = l;
    j = r;

    while(i < j)
    {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }
}

/*
   Stable partition:
   Elements satisfying p[i] <= mid
   are placed before elements > mid.

   Returns the number of elements <= mid.
*/
int stablePartition(int p[], int l, int r, int mid)
{
    int m;
    int leftCount, rightCount;
    int leftEnd, rightStart;

    if(r - l == 1)
    {
        if(p[l] <= mid)
            return 1;
        else
            return 0;
    }

    m = (l + r) / 2;

    /* Partition left half */
    leftCount = stablePartition(p, l, m, mid);

    /* Partition right half */
    rightCount = stablePartition(p, m, r, mid);

    /*
       After recursive partition:

       LOW_LEFT HIGH_LEFT LOW_RIGHT HIGH_RIGHT

       We want:

       LOW_LEFT LOW_RIGHT HIGH_LEFT HIGH_RIGHT
    */

    leftEnd = l + leftCount;
    rightStart = m;
    r = m + rightCount;

    /*
       Rotate:
       HIGH_LEFT | LOW_RIGHT

       using three reversals.
    */

    if(leftEnd < m)
        reverseArray(p, leftEnd, m - 1);

    if(m < r)
        reverseArray(p, m, r - 1);

    if(leftEnd < r)
        reverseArray(p, leftEnd, r - 1);

    return leftCount + rightCount;
}

/* Divide and conquer sorting */
void sortPermutation(int p[], int l, int r, int low, int high)
{
    int mid;
    int leftSize;

    /* Only one possible value */
    if(low >= high)
        return;

    mid = (low + high) / 2;

    /*
       Partition values into:

       [low ... mid]
       [mid+1 ... high]
    */

    leftSize = stablePartition(p, l, r, mid);

    /* Sort lower half */
    sortPermutation(p,
                    l,
                    l + leftSize,
                    low,
                    mid);

    /* Sort upper half */
    sortPermutation(p,
                    l + leftSize,
                    r,
                    mid + 1,
                    high);
}

/* Display permutation */
void display(int p[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

int main()
{
    int p[MAX];
    int n;
    int i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter permutation of 1 to %d:\n", n);

    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");
    display(p, n);

    /* Sort using reversal-based divide and conquer */
    sortPermutation(p, 0, n, 1, n);

    printf("\nSorted permutation:\n");
    display(p, n);

    printf("\nNumber of reversals = %lld\n", reversalCount);
    printf("Total reversal cost = %lld\n", totalCost);

    return 0;
}