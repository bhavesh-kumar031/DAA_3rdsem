#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;
} Event;

/*
   type:
   -1 = death
   +1 = birth
*/

/* Comparator for qsort */
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    /*
       First compare years.
    */
    if (e1->year < e2->year)
        return -1;

    if (e1->year > e2->year)
        return 1;

    /*
       Same year:
       death (-1) must come before birth (+1).
    */
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    Event events[2 * n];

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("\nScientist %d\n", i + 1);

        printf("Enter birth year: ");
        scanf("%d", &birth);

        printf("Enter death year: ");
        scanf("%d", &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    /*
       Sort all events.
    */
    qsort(events,
          2 * n,
          sizeof(Event),
          compareEvents);

    int alive = 0;
    int maximumAlive = 0;
    int bestYear = 0;

    /*
       Process events.
    */
    for (int i = 0; i < 2 * n; i++)
    {
        alive += events[i].type;

        if (alive > maximumAlive)
        {
            maximumAlive = alive;
            bestYear = events[i].year;
        }
    }

    printf("\n-------------------------\n");
    printf("Maximum scientists alive = %d\n",
           maximumAlive);

    printf("Best time/year = %d\n",
           bestYear);
    printf("-------------------------\n");

    return 0;
}