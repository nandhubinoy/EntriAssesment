#include <stdio.h>

int main() {
    int num;
    int isPrime = 1; // Flag to track prime status (1 = true, 0 = false)

    // Prompt user for input
    printf("Enter a number to check if it is prime: ");
    scanf("%d", &num);

    // Numbers less than 2 are not prime
    if (num < 2) {
        isPrime = 0;
    } else {
        // Simple loop to test for divisors
        for (int i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                isPrime = 0; // Found a divisor, not prime
                break;       // No need to check further
            }
        }
    }

    // Conditional statement to print the final result
    if (isPrime) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }

    return 0;
}