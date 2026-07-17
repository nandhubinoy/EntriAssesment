#include <stdio.h>

int main() {
    int num;
    unsigned long long factorial = 1; // Use unsigned long long to handle large results

    // Prompt the user
    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Error: Factorial of a negative number is not defined.\n");
    } else {
        // Calculate factorial using a loop
        for (int i = 1; i <= num; i++) {
            factorial *= i;
        }
        
        // Final result displayed clearly (handles 0! = 1 naturally)
        printf("The factorial of %d is %llu\n", num, factorial);
    }

    return 0;
}