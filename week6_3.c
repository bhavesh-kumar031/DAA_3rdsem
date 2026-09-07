#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1.0)

/* FFT function */
void FFT(complex double a[], int n, int invert)
{
    int i, j, len;
    complex double w, u, v, temp;

    /* Bit reversal */
    for(i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;

        while(j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if(i < j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    /* Divide and conquer */
    for(len = 2; len <= n; len <<= 1)
    {
        double angle = 2 * PI / len;

        if(invert)
            angle = -angle;

        w = cos(angle) + I * sin(angle);

        for(i = 0; i < n; i += len)
        {
            complex double current_w = 1.0;

            for(j = 0; j < len / 2; j++)
            {
                u = a[i + j];
                v = a[i + j + len / 2] * current_w;

                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;

                current_w *= w;
            }
        }
    }

    /* For inverse FFT */
    if(invert)
    {
        for(i = 0; i < n; i++)
            a[i] /= n;
    }
}

/* Convolution function */
void convolution(int A[], int m, int B[], int n)
{
    int size = 1;
    int i;

    /* Find power of 2 >= m+n-1 */
    while(size < m + n - 1)
        size *= 2;

    complex double *fa;
    complex double *fb;

    fa = calloc(size, sizeof(complex double));
    fb = calloc(size, sizeof(complex double));

    /* Copy input arrays */
    for(i = 0; i < m; i++)
        fa[i] = A[i];

    for(i = 0; i < n; i++)
        fb[i] = B[i];

    /* FFT */
    FFT(fa, size, 0);
    FFT(fb, size, 0);

    /* Point-wise multiplication */
    for(i = 0; i < size; i++)
        fa[i] *= fb[i];

    /* Inverse FFT */
    FFT(fa, size, 1);

    /* Print result */
    printf("\nConvolution:\n");

    for(i = 0; i < m + n - 1; i++)
        printf("%.0f ", creal(fa[i]));

    printf("\n");

    free(fa);
    free(fb);
}

int main()
{
    int A[100], B[100];
    int m, n, i;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter elements of A:\n");

    for(i = 0; i < m; i++)
        scanf("%d", &A[i]);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    printf("Enter elements of B:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &B[i]);

    if(n < m)
    {
        printf("Condition n >= m is required.\n");
        return 0;
    }

    convolution(A, m, B, n);

    return 0;
}