#include <stdio.h>

void addMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void specialMultiply(int n, int A[n][n], int B[n][n], int C[n][n])
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int size = n / 2;

    /*
       A =
       A11 A12
       A12 A11

       B =
       B11 B12
       B12 B11
    */

    int A11[size][size];
    int A12[size][size];

    int B11[size][size];
    int B12[size][size];

    // Extract the two unique blocks of A and B
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + size];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + size];
        }
    }

    /*
       P = (A11 + A12)(B11 + B12)
       Q = (A11 - A12)(B11 - B12)
    */

    int Aplus[size][size];
    int Aminus[size][size];

    int Bplus[size][size];
    int Bminus[size][size];

    int P[size][size];
    int Q[size][size];

    addMatrix(size, A11, A12, Aplus);
    subtractMatrix(size, A11, A12, Aminus);

    addMatrix(size, B11, B12, Bplus);
    subtractMatrix(size, B11, B12, Bminus);

    // Two recursive multiplications
    specialMultiply(size, Aplus, Bplus, P);
    specialMultiply(size, Aminus, Bminus, Q);

    /*
       C11 = (P + Q) / 2
       C12 = (P - Q) / 2

       C =
       C11 C12
       C12 C11
    */

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int diagonal = (P[i][j] + Q[i][j]) / 2;
            int offDiagonal = (P[i][j] - Q[i][j]) / 2;

            C[i][j] = diagonal;
            C[i][j + size] = offDiagonal;

            C[i + size][j] = offDiagonal;
            C[i + size][j + size] = diagonal;
        }
    }
}

int main()
{
    int n;

    printf("Enter size of matrix (power of 2): ");
    scanf("%d", &n);

    int A[n][n];
    int B[n][n];
    int C[n][n];

    printf("Enter elements of first matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    specialMultiply(n, A, B, C);

    printf("\nResultant Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }

        printf("\n");
    }

    return 0;
}