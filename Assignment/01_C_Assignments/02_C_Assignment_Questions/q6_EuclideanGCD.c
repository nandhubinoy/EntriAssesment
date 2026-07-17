/*  The algorithm is based on the below facts. 
 *  If we subtract a smaller number from a larger one (we reduce a larger number), GCD doesn't change. 
 *  So if we keep subtracting repeatedly the larger of two, we end up with GCD.
 *  Now instead of subtraction, if we divide the larger number, the algorithm stops when we find the remainder 0.
*/

#include <stdio.h>

// Recursive function using the Euclidean algorithm
int findGCD(int a, int b) {
    // Base case: if remainder is zero, the other number is the GCD
    if (b == 0) {
        return a;
    }
    // Recursive step: replace larger with remainder
    return findGCD(b, a % b);
}

int main() {
    int num1, num2, gcd;

    printf("Enter two positive integers to find their GCD: ");
    scanf("%d %d", &num1, &num2);

    // Call the recursive function
    gcd = findGCD(num1, num2);

    printf("The GCD of %d and %d is %d\n", num1, num2, gcd);

    return 0;
}