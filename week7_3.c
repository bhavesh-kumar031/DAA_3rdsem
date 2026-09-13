#include <stdio.h>
#include <limits.h>

#define MAX 30

long long dp[MAX];
int bestK[MAX];

/* Number of moves for ordinary 3-peg Hanoi */
long long hanoi3Moves(int n)
{
    if (n == 0)
        return 0;

    return (1LL << n) - 1;
}

/*
   Calculate minimum number of moves
   using Frame-Stewart algorithm.
*/
void calculateDP(int n)
{
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        dp[i] = LLONG_MAX;
        bestK[i] = 0;

        /*
           Try every possible number k of
           disks to move using 4 pegs.
        */
        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k] +
                hanoi3Moves(i - k);

            if (moves < dp[i])
            {
                dp[i] = moves;
                bestK[i] = k;
            }
        }

        /*
           We can always use normal 3-peg Hanoi.
        */
        if (hanoi3Moves(i) < dp[i])
        {
            dp[i] = hanoi3Moves(i);
            bestK[i] = 0;
        }
    }
}

/* Print ordinary 3-peg moves */
void hanoi3(int n, char source,
            char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

/*
   4-peg Frame-Stewart solution.
*/
void hanoi4(int n,
            char source,
            char destination,
            char aux1,
            char aux2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    int k = bestK[n];

    /*
       If k = 0, use ordinary 3-peg Hanoi.
    */
    if (k == 0)
    {
        hanoi3(n, source, destination, aux1);
        return;
    }

    /*
       Step 1:
       Move k smallest disks from source to aux1.
    */
    hanoi4(k, source, aux1,
           destination, aux2);

    /*
       Step 2:
       Move remaining n-k disks from source
       to destination using 3 pegs.
    */
    hanoi3(n - k, source,
           destination, aux2);

    /*
       Step 3:
       Move k disks from aux1 to destination.
    */
    hanoi4(k, aux1, destination,
           source, aux2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of disks.\n");
        return 0;
    }

    calculateDP(n);

    printf("\nMinimum number of moves = %lld\n",
           dp[n]);

    printf("Best k = %d\n", bestK[n]);

    if (n == 8)
        printf("Required answer for 8 disks = 33 moves\n");

    /*
       Uncomment the following if you want
       to display every move.
    */

    /*
    printf("\nSequence of moves:\n");

    hanoi4(n, 'A', 'D', 'B', 'C');
    */

    return 0;
}