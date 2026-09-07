#include <stdio.h>
#include <math.h>

#define MAX 50

/* Matrix Addition */
void matrixAddition(int A[][MAX], int B[][MAX], int C[][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* Matrix Multiplication */
void matrixMultiplication(int A[][MAX], int B[][MAX], int C[][MAX], int n)
{
    int i, j, k;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for(k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Check Zero Matrix */
int isZeroMatrix(int A[][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

/* Check Symmetric Matrix */
int isSymmetric(int A[][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

/* Determinant using Gaussian Elimination */
double determinant(int A[][MAX], int n)
{
    double B[MAX][MAX];
    double det = 1;
    double factor;
    int i, j, k;
    int swap;
    double temp;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            B[i][j] = A[i][j];
    }

    for(i = 0; i < n; i++)
    {
        /* Find non-zero pivot */
        if(fabs(B[i][i]) < 1e-9)
        {
            swap = -1;

            for(k = i + 1; k < n; k++)
            {
                if(fabs(B[k][i]) > 1e-9)
                {
                    swap = k;
                    break;
                }
            }

            if(swap == -1)
                return 0;

            /* Swap rows */
            for(j = 0; j < n; j++)
            {
                temp = B[i][j];
                B[i][j] = B[swap][j];
                B[swap][j] = temp;
            }

            det = -det;
        }

        det *= B[i][i];

        /* Eliminate below pivot */
        for(k = i + 1; k < n; k++)
        {
            factor = B[k][i] / B[i][i];

            for(j = i; j < n; j++)
            {
                B[k][j] -= factor * B[i][j];
            }
        }
    }

    return det;
}

/* In-place Transpose */
void transpose(int A[][MAX], int n)
{
    int i, j, temp;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* Power Method for Dominant Eigenvalue and Eigenvector */
void eigenvalueEigenvector(int A[][MAX], int n)
{
    double x[MAX], y[MAX];
    double eigenvalue = 0;
    double maxValue;
    double error;
    int i, j, iteration;

    /* Initial vector */
    for(i = 0; i < n; i++)
        x[i] = 1.0;

    for(iteration = 0; iteration < 1000; iteration++)
    {
        /* y = A*x */
        for(i = 0; i < n; i++)
        {
            y[i] = 0;

            for(j = 0; j < n; j++)
            {
                y[i] += A[i][j] * x[j];
            }
        }

        /* Find largest absolute value */
        maxValue = fabs(y[0]);

        for(i = 1; i < n; i++)
        {
            if(fabs(y[i]) > maxValue)
                maxValue = fabs(y[i]);
        }

        /* Normalize */
        for(i = 0; i < n; i++)
            y[i] = y[i] / maxValue;

        error = fabs(maxValue - eigenvalue);
        eigenvalue = maxValue;

        for(i = 0; i < n; i++)
            x[i] = y[i];

        if(error < 0.000001)
            break;
    }

    printf("Dominant Eigenvalue = %.6f\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for(i = 0; i < n; i++)
        printf("%.6f\n", x[i]);
}

/* Display Matrix */
void display(int A[][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, i, j;

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter elements of Matrix A:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter elements of Matrix B:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    /* (i) Addition */
    matrixAddition(A, B, C, n);

    printf("\n1. Matrix Addition:\n");
    display(C, n);

    /* (ii) Multiplication */
    matrixMultiplication(A, B, C, n);

    printf("\n2. Matrix Multiplication:\n");
    display(C, n);

    /* (iii) Zero Matrix */
    if(isZeroMatrix(A, n))
        printf("\n3. Matrix A is a Zero Matrix.\n");
    else
        printf("\n3. Matrix A is not a Zero Matrix.\n");

    /* (iv) Symmetric */
    if(isSymmetric(A, n))
        printf("\n4. Matrix A is Symmetric.\n");
    else
        printf("\n4. Matrix A is not Symmetric.\n");

    /* (v) Determinant */
    printf("\n5. Determinant of Matrix A = %.2f\n",
           determinant(A, n));

    /* (vi) Transpose */
    transpose(A, n);

    printf("\n6. Transpose of Matrix A:\n");
    display(A, n);

    /* (vii) Eigenvalue and Eigenvector */
    printf("\n7. Eigenvalue and Eigenvector:\n");
    eigenvalueEigenvector(A, n);

    return 0;
}