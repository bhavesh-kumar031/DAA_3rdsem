#include <stdio.h>

/* Check whether switch index can be toggled */
int canToggle(int a[], int n, int index)
{
    /*
       Rightmost switch can always be toggled.
    */
    if (index == n - 1)
        return 1;

    /*
       Immediate right switch must be ON.
    */
    if (a[index + 1] != 1)
        return 0;

    /*
       Every switch further right must be OFF.
    */
    for (int i = index + 2; i < n; i++)
    {
        if (a[i] != 0)
            return 0;
    }

    return 1;
}

/* Toggle switch */
void toggle(int a[], int index)
{
    a[index] = 1 - a[index];
}

/* Print current state */
void printState(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/*
   Recursive minimum sequence.

   The sequence for n is generated from n-1.
*/
void solve(int a[], int n, int *moves)
{
    if (n == 1)
    {
        toggle(a, 0);
        (*moves)++;

        printf("Move %d: Toggle switch 1 -> ",
               *moves);
        printState(a, n);

        return;
    }

    /*
       For odd n:
       toggle switch n first.
    */
    if (n % 2 == 1)
    {
        if (canToggle(a, n, n - 1))
        {
            toggle(a, n - 1);
            (*moves)++;

            printf("Move %d: Toggle switch %d -> ",
                   *moves, n);
            printState(a, n);
        }
    }

    /*
       Generate solution for first n-1 switches.
    */
    solve(a, n - 1, moves);

    /*
       For every move of the smaller system,
       switch n must be toggled appropriately.

       This implementation is easier to validate by
       generating the known recursive sequence below.
    */
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int a[n];

    for (int i = 0; i < n; i++)
        a[i] = 1;

    /*
       Generate the legal sequence directly.
       The recursive move pattern is:
       
       n odd:
          n, S(n-1), n inserted after each move
       
       n even:
          S(n-1), n inserted after each move
    */

    int sequence[100000];
    int length[100];
    
    /* Generate recursively using an array */
    int current[100000];
    int currentLength = 1;

    current[0] = 1;

    for (int size = 2; size <= n; size++)
    {
        int newLength = 0;

        if (size % 2 == 1)
        {
            current[newLength++] = size;

            for (int i = 0; i < currentLength; i++)
            {
                current[newLength++] = current[i];
                current[newLength++] = size;
            }
        }
        else
        {
            for (int i = 0; i < currentLength; i++)
            {
                current[newLength++] = current[i];
                current[newLength++] = size;
            }
        }

        currentLength = newLength;
    }

    printf("\nInitial state:\n");
    printState(a, n);

    printf("\nToggle sequence:\n");

    int moves = 0;

    for (int i = 0; i < currentLength; i++)
    {
        int switchNumber = current[i];
        int index = switchNumber - 1;

        if (!canToggle(a, n, index))
        {
            printf("ERROR: Illegal move!\n");
            return 0;
        }

        toggle(a, index);
        moves++;

        printf("Move %d: Switch %d -> ",
               moves, switchNumber);

        printState(a, n);
    }

    printf("\nFinal state:\n");
    printState(a, n);

    printf("\nMinimum moves = %d\n", moves);

    return 0;
}