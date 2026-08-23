#include <stdio.h>

struct Item {
    int number;
    char colour;
};

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item red[n], blue[n], yellow[n];

    int r = 0, b = 0, y = 0;

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        int num;
        char colour;

        scanf("%d %c", &num, &colour);

        if (colour == 'R') {
            red[r].number = num;
            red[r].colour = colour;
            r++;
        }
        else if (colour == 'B') {
            blue[b].number = num;
            blue[b].colour = colour;
            b++;
        }
        else if (colour == 'Y') {
            yellow[y].number = num;
            yellow[y].colour = colour;
            y++;
        }
    }

    printf("\nSorted by colour:\n");

    // Print RED
    for (int i = 0; i < r; i++) {
        printf("(%d, %c) ", red[i].number, red[i].colour);
    }

    // Print BLUE
    for (int i = 0; i < b; i++) {
        printf("(%d, %c) ", blue[i].number, blue[i].colour);
    }

    // Print YELLOW
    for (int i = 0; i < y; i++) {
        printf("(%d, %c) ", yellow[i].number, yellow[i].colour);
    }

    printf("\n");

    return 0;
}