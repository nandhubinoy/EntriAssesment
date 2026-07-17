#include <stdio.h>

// Function to check if a number is a Perfect Number
// Returns 1 if perfect, 0 if not
int isPerfectNumber(int num) {
    if (num <= 0) return 0; // Perfect numbers must be positive

    int sumOfDivisors = 0;

    // Find all proper divisors and sum them up
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sumOfDivisors += i;
        }
    }

    // Return whether the sum equals the original number
    return (sumOfDivisors == num);
}

int main() {
    int num;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (isPerfectNumber(num)) {
        printf("%d is a Perfect Number.\n", num);
    } else {
        printf("%d is not a Perfect Number.\n", num);
    }

    return 0;
}