#include <stdio.h>
#include <limits.h>

#define MAX 100

long long dp[MAX][MAX];
int split[MAX][MAX];

/*
   Print optimal parenthesization.
*/
void printOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOrder(i, split[i][j]);

    printf(" x ");

    printOrder(split[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;
    int p[MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of matrices.\n");
        return 0;
    }

    /*
       If there are n matrices,
       there are n+1 dimensions.
    */

    printf("\nEnter dimensions of matrices:\n");

    for (int i = 1; i <= n; i++)
    {
        int rows, cols;

        printf("A%d (rows columns): ",
               i);

        scanf("%d %d",
              &rows,
              &cols);

        /*
           First matrix gives p[0] and p[1].
        */
        if (i == 1)
        {
            p[0] = rows;
            p[1] = cols;
        }
        else
        {
            /*
               Number of rows of current matrix
               must equal number of columns of
               previous matrix.
            */
            if (rows != p[i - 1])
            {
                printf("\nInvalid matrix dimensions!\n");
                printf("A%d cannot be multiplied with A%d.\n",
                       i - 1, i);
                return 0;
            }

            p[i] = cols;
        }
    }

    /*
       A single matrix requires 0 multiplications.
    */
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    /*
       length = number of matrices in chain.
    */
    for (int length = 2;
         length <= n;
         length++)
    {
        for (int i = 1;
             i <= n - length + 1;
             i++)
        {
            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            /*
               Try every possible split.
            */
            for (int k = i;
                 k < j;
                 k++)
            {
                long long cost =
                    dp[i][k]
                    + dp[k + 1][j]
                    + (long long)p[i - 1]
                    * p[k]
                    * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\n================================\n");

    printf("Minimum scalar multiplications = %lld\n",
           dp[1][n]);

    printf("\nOptimal ordering:\n");

    printOrder(1, n);

    printf("\n================================\n");

    return 0;
}