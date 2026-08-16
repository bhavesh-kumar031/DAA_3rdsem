#include <stdio.h>

int binarySearch(int arr[], int n, int x, int *comparisons)
{
    int start = 0;
    int end = n - 1;

    while (start <= end)
    {
        int mid = (start + end) / 2;

        (*comparisons)++;

        if (arr[mid] == x)
            return mid;

        (*comparisons)++;

        if (arr[mid] < x)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return -1;
}

int ternarySearch(int arr[], int n, int x, int *comparisons)
{
    int start = 0;
    int end = n - 1;

    while (start <= end)
    {
        int third = (end - start) / 3;

        int mid1 = start + third;
        int mid2 = end - third;

        (*comparisons)++;

        if (arr[mid1] == x)
            return mid1;

        (*comparisons)++;

        if (arr[mid2] == x)
            return mid2;

        (*comparisons)++;

        if (x < arr[mid1])
        {
            end = mid1 - 1;
        }
        else
        {
            (*comparisons)++;

            if (x > arr[mid2])
                start = mid2 + 1;
            else
            {
                start = mid1 + 1;
                end = mid2 - 1;
            }
        }
    }

    return -1;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements in sorted order:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int totalBinaryComparisons = 0;
    int totalTernaryComparisons = 0;

    printf("\nComparison for each element:\n");

    printf("\nElement\tBinary\tTernary\n");

    for (int i = 0; i < n; i++)
    {
        int binaryComparisons = 0;
        int ternaryComparisons = 0;

        binarySearch(arr, n, arr[i], &binaryComparisons);
        ternarySearch(arr, n, arr[i], &ternaryComparisons);

        totalBinaryComparisons += binaryComparisons;
        totalTernaryComparisons += ternaryComparisons;

        printf("%d\t%d\t%d\n",
               arr[i],
               binaryComparisons,
               ternaryComparisons);
    }

    double averageBinary =
        (double)totalBinaryComparisons / n;

    double averageTernary =
        (double)totalTernaryComparisons / n;

    printf("\n--- Overall Result ---\n");

    printf("Total Binary Search comparisons  : %d\n",
           totalBinaryComparisons);

    printf("Total Ternary Search comparisons : %d\n",
           totalTernaryComparisons);

    printf("Average Binary Search comparisons  : %.2f\n",
           averageBinary);

    printf("Average Ternary Search comparisons : %.2f\n",
           averageTernary);

    if (totalBinaryComparisons < totalTernaryComparisons)
    {
        printf("\nConclusion: Binary Search is more efficient overall.\n");
    }
    else if (totalTernaryComparisons < totalBinaryComparisons)
    {
        printf("\nConclusion: Ternary Search is more efficient overall for this input.\n");
    }
    else
    {
        printf("\nConclusion: Both have the same overall performance.\n");
    }

    return 0;
}