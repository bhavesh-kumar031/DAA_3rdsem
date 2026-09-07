#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Function to print array */
void display(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/* (i) Find Maximum */
int findMaximum(int a[], int n)
{
    int max = a[0];
    int i;

    for(i = 1; i < n; i++)
    {
        if(a[i] > max)
            max = a[i];
    }

    return max;
}

/* (ii) Find First and Second Largest */
void findLargestTwo(int a[], int n)
{
    int largest, second;
    int i;

    if(a[0] > a[1])
    {
        largest = a[0];
        second = a[1];
    }
    else
    {
        largest = a[1];
        second = a[0];
    }

    for(i = 2; i < n; i++)
    {
        if(a[i] > largest)
        {
            second = largest;
            largest = a[i];
        }
        else if(a[i] > second)
        {
            second = a[i];
        }
    }

    printf("Largest = %d\n", largest);
    printf("Second Largest = %d\n", second);
}

/* (iii) Find Mean */
double findMean(int a[], int n)
{
    long long sum = 0;
    int i;

    for(i = 0; i < n; i++)
        sum += a[i];

    return (double)sum / n;
}

/* Compare function for qsort */
int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/* (iv) Find Median */
double findMedian(int a[], int n)
{
    int *b;
    double median;

    b = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
        b[i] = a[i];

    qsort(b, n, sizeof(int), compare);

    if(n % 2 == 0)
        median = (b[n / 2 - 1] + b[n / 2]) / 2.0;
    else
        median = b[n / 2];

    free(b);

    return median;
}

/* (v) Find Standard Deviation */
double findStandardDeviation(int a[], int n)
{
    double mean;
    double sum = 0;
    double variance;
    int i;

    mean = findMean(a, n);

    for(i = 0; i < n; i++)
    {
        sum += (a[i] - mean) * (a[i] - mean);
    }

    variance = sum / n;

    return sqrt(variance);
}

/* (vi) Find Mode */
int findMode(int a[], int n)
{
    int mode = a[0];
    int maxCount = 1;
    int i, j, count;

    for(i = 0; i < n; i++)
    {
        count = 0;

        for(j = 0; j < n; j++)
        {
            if(a[i] == a[j])
                count++;
        }

        if(count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

/* (vii) Remove Duplicates */
int removeDuplicates(int a[], int n)
{
    int i, j, k;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(a[i] == a[j])
            {
                for(k = j; k < n - 1; k++)
                    a[k] = a[k + 1];

                n--;
                j--;
            }
        }
    }

    return n;
}

/* (viii) Reverse Array */
void reverseArray(int a[], int n)
{
    int i, j, temp;

    i = 0;
    j = n - 1;

    while(i < j)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}

/* (ix) Partition with respect to pivot */
void partitionArray(int a[], int n, int pivot)
{
    int i, j, temp;

    i = 0;

    for(j = 0; j < n; j++)
    {
        if(a[j] < pivot)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
        }
    }
}

int main()
{
    int a[1000];
    int n, i;
    int pivot;
    double mean, median, sd;
    int mode;
    int newSize;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d unsorted elements:\n", n);

    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nOriginal Array:\n");
    display(a, n);

    /* (i) Maximum */
    printf("\n1. Maximum Element = %d\n", findMaximum(a, n));

    /* (ii) First and Second Largest */
    printf("\n2. First and Second Largest:\n");
    findLargestTwo(a, n);

    /* (iii) Mean */
    mean = findMean(a, n);
    printf("\n3. Mean = %.2f\n", mean);

    /* (iv) Median */
    median = findMedian(a, n);
    printf("\n4. Median = %.2f\n", median);

    /* (v) Standard Deviation */
    sd = findStandardDeviation(a, n);
    printf("\n5. Standard Deviation = %.2f\n", sd);

    /* (vi) Mode */
    mode = findMode(a, n);
    printf("\n6. Mode = %d\n", mode);

    /* (vii) Remove Duplicates */
    {
        int b[1000];

        for(i = 0; i < n; i++)
            b[i] = a[i];

        newSize = removeDuplicates(b, n);

        printf("\n7. Array after removing duplicates:\n");
        display(b, newSize);
    }

    /* (viii) Reverse */
    {
        int b[1000];

        for(i = 0; i < n; i++)
            b[i] = a[i];

        reverseArray(b, n);

        printf("\n8. Reversed Array:\n");
        display(b, n);
    }

    /* (ix) Partition */
    printf("\nEnter pivot element: ");
    scanf("%d", &pivot);

    {
        int b[1000];

        for(i = 0; i < n; i++)
            b[i] = a[i];

        partitionArray(b, n, pivot);

        printf("9. Partitioned Array:\n");
        display(b, n);
    }

    return 0;
}