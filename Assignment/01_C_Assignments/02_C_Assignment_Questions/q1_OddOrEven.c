#include <stdio.h>

int main() {
    int num;

    // Prompt the user to enter a whole number
    printf("Enter a whole number: ");
    scanf("%d", &num);

    // Check if the number is perfectly divisible by 2
    if (num % 2 == 0) {
        printf("%d is an even number.\n", num);
    } else {
        printf("%d is an odd number.\n", num);
    }

    return 0;
}