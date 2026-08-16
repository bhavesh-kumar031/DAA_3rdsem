#include <stdio.h>

void selectionSort(int arr[], int n, int *comparisons)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            (*comparisons)++;

            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        // Exchange arr[i] and arr[minIndex]
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
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

    int comparisons = 0;

    selectionSort(arr, n, &comparisons);

    printf("\nSorted array:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n\nNumber of comparisons: %d\n", comparisons);

    printf("Expected comparisons = %d\n",
           n * (n - 1) / 2);

    if (comparisons == n * (n - 1) / 2)
    {
        printf("Validation: Comparisons are proportional to n^2.\n");
        printf("Therefore, running time is Theta(n^2).\n");
    }

    return 0;
}