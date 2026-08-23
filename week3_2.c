#include <stdio.h>

/*
    Returns:
    -1 : left group is lighter
     0 : both groups have equal weight
     1 : right group is lighter
*/
int weigh(int coins[], int leftStart, int leftEnd,
          int rightStart, int rightEnd)
{
    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = leftStart; i <= leftEnd; i++)
        leftWeight += coins[i];

    for (int i = rightStart; i <= rightEnd; i++)
        rightWeight += coins[i];

    if (leftWeight < rightWeight)
        return -1;

    if (leftWeight > rightWeight)
        return 1;

    return 0;
}

int findDefectiveCoin(int coins[], int n)
{
    int start = 0;
    int end = n - 1;

    while (start < end)
    {
        int size = end - start + 1;

        int mid = start + size / 2 - 1;

        int result = weigh(coins,
                           start, mid,
                           mid + 1, end);

        if (result == -1)
        {
            // Left half is lighter
            end = mid;
        }
        else if (result == 1)
        {
            // Right half is lighter
            start = mid + 1;
        }
        else
        {
            // Both halves have equal weight.
            // Therefore, no defective coin exists.
            return -1;
        }
    }

    /*
       Only one coin remains.
       It is a possible defective coin.

       We need to verify whether it is actually lighter.
    */

    if (n == 1)
        return -1;

    int normalWeight = coins[0];

    if (coins[start] < normalWeight)
        return start;

    return -1;
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of the coins:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    int defective = findDefectiveCoin(coins, n);

    if (defective == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf("Defective coin found at position %d.\n",
               defective + 1);

        printf("Weight of defective coin = %d\n",
               coins[defective]);
    }

    return 0;
}