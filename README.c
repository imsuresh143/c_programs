#include <stdio.h>
int main() {
int a[30], number, i, j, temp;

    printf("Please enter the total number of elements:");
    scanf("%d", &number);

    printf("Please enter the array elements:\n");

    for (i = 0; i < number; i++) {
        scanf("%d", &a[i]);
    }

    // Selection Sort algorithm
    for (i = 0; i < number; i++) {
        for (j = i + 1; j < number; j++) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("\nSelection sort result:\n");

    for (i = 0; i < number; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
