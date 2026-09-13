#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int maximum(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int eggDrop(int eggs, int floors)
{
    int **dp;

    dp = (int **)malloc((eggs + 1) * sizeof(int *));

    for (int i = 0; i <= eggs; i++)
        dp[i] = (int *)malloc((floors + 1) * sizeof(int));

    /* 0 floors require 0 drops */
    for (int e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    /* 1 floor requires 1 drop */
    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    /* With 1 egg, we must test every floor */
    for (int f = 1; f <= floors; f++)
        dp[1][f] = f;

    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = INF;

            /*
             Try dropping the egg from every floor x.
            */
            for (int x = 1; x <= f; x++)
            {
                /*
                 Egg breaks:
                 We have e-1 eggs and x-1 floors.
                */
                int breakCase = dp[e - 1][x - 1];

                /*
                 Egg doesn't break:
                 We still have e eggs and f-x floors.
                */
                int noBreakCase = dp[e][f - x];

                int drops = 1 + maximum(breakCase,
                                         noBreakCase);

                if (drops < dp[e][f])
                    dp[e][f] = drops;
            }
        }
    }

    int answer = dp[eggs][floors];

    for (int i = 0; i <= eggs; i++)
        free(dp[i]);

    free(dp);

    return answer;
}

int main()
{
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || floors < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("\nMinimum number of droppings = %d\n",
           eggDrop(eggs, floors));

    return 0;
}