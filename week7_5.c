#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 0;
    }

    printf("\nGuaranteed shooting sequence:\n");

    for (int i = 1; i <= n; i++)
    {
        /*
           Shoot every position twice.
        */
        printf("%d ", i);
        printf("%d ", i);
    }

    printf("\n");

    printf("\nNumber of shots = %d\n", 2 * n);

    printf("\nThe strategy guarantees a hit.\n");

    return 0;
}