#include <stdio.h>

int main()
{
    int n;
    int totalCoins;
    int minimumMoves;

    printf("Enter number of rows in triangle: ");
    scanf("%d", &n);

    totalCoins = n * (n + 1) / 2;

    minimumMoves = (n * n) / 4;

    printf("\nTotal number of coins = %d\n", totalCoins);
    printf("Minimum number of moves = %d\n", minimumMoves);

    return 0;
}