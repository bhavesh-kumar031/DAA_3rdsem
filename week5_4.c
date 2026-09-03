#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    int largest, left, right, temp;

    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int i, temp;

    /* Build max heap */
    for(i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Extract elements */
    for(i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main()
{
    int a[100], n, i;
    FILE *fp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));

    /* Store random elements in file */
    fp = fopen("numbers.txt", "w");

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    /* Read elements from file */
    fp = fopen("numbers.txt", "r");

    for(i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    printf("Before sorting:\n");
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    heapSort(a, n);

    printf("\nAfter sorting:\n");
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}