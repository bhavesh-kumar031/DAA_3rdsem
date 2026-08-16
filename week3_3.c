#include <stdio.h>

typedef struct
{
    int min;
    int max;
} Result;

int comparisons = 0;

Result findMinMax(int arr[], int start, int end)
{
    Result result;
    Result leftResult, rightResult;

    // Only one element
    if (start == end)
    {
        result.min = arr[start];
        result.max = arr[start];

        return result;
    }

    // Two elements
    if (end == start + 1)
    {
        comparisons++;

        if (arr[start] < arr[end])
        {
            result.min = arr[start];
            result.max = arr[end];
        }
        else
        {
            result.min = arr[end];
            result.max = arr[start];
        }

        return result;
    }

    // Divide
    int mid = (start + end) / 2;

    // Conquer
    leftResult = findMinMax(arr, start, mid);
    rightResult = findMinMax(arr, mid + 1, end);

    // Combine: compare minimums
    comparisons++;

    if (leftResult.min < rightResult.min)
        result.min = leftResult.min;
    else
        result.min = rightResult.min;

    // Combine: compare maximums
    comparisons++;

    if (leftResult.max > rightResult.max)
        result.max = leftResult.max;
    else
        result.max = rightResult.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Result answer = findMinMax(arr, 0, n - 1);

    printf("\nMinimum element = %d\n", answer.min);
    printf("Maximum element = %d\n", answer.max);

    printf("Number of comparisons = %d\n", comparisons);

    printf("3n/2 = %.1f\n", 1.5 * n);

    if (comparisons <= 1.5 * n)
        printf("Result: Number of comparisons is within 3n/2.\n");
    else
        printf("Result: Number of comparisons exceeds 3n/2.\n");

    return 0;
}