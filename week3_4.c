#include <stdio.h>
#include <stdlib.h>

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

void strassen(int n, int A[n][n], int B[n][n], int C[n][n])
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    int A11[newSize][newSize];
    int A12[newSize][newSize];
    int A21[newSize][newSize];
    int A22[newSize][newSize];

    int B11[newSize][newSize];
    int B12[newSize][newSize];
    int B21[newSize][newSize];
    int B22[newSize][newSize];

    int M1[newSize][newSize];
    int M2[newSize][newSize];
    int M3[newSize][newSize];
    int M4[newSize][newSize];
    int M5[newSize][newSize];
    int M6[newSize][newSize];
    int M7[newSize][newSize];

    int temp1[newSize][newSize];
    int temp2[newSize][newSize];

    // Divide matrices into four submatrices

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)

    addMatrix(newSize, A11, A22, temp1);
    addMatrix(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1);

    // M2 = (A21 + A22)B11

    addMatrix(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2);

    // M3 = A11(B12 - B22)

    subtractMatrix(newSize, B12, B22, temp1);
    strassen(newSize, A11, temp1, M3);

    // M4 = A22(B21 - B11)

    subtractMatrix(newSize, B21, B11, temp1);
    strassen(newSize, A22, temp1, M4);

    // M5 = (A11 + A12)B22

    addMatrix(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5);

    // M6 = (A21 - A11)(B11 + B12)

    subtractMatrix(newSize, A21, A11, temp1);
    addMatrix(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6);

    // M7 = (A12 - A22)(B21 + B22)

    subtractMatrix(newSize, A12, A22, temp1);
    addMatrix(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i][j] = M1[i][j]
                    + M4[i][j]
                    - M5[i][j]
                    + M7[i][j];
        }
    }

    // C12 = M3 + M5

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i][j + newSize] = M3[i][j] + M5[i][j];
        }
    }

    // C21 = M2 + M4

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i + newSize][j] = M2[i][j] + M4[i][j];
        }
    }

    // C22 = M1 - M2 + M3 + M6

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i + newSize][j + newSize] =
                M1[i][j]
                - M2[i][j]
                + M3[i][j]
                + M6[i][j];
        }
    }
}

int main()
{
    int n;

    printf("Enter size of square matrices: ");
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

    strassen(n, A, B, C);

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