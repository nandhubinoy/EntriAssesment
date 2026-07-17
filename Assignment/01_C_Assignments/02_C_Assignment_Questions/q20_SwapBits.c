#include <stdio.h>

void printBinary(unsigned int val)
{
    // Print 32-bit integer in binary format
    for(int i = 31; i >= 0; i--)
    {
        printf("%u",((val >> i) & 1U));
        if(i % 8 == 0) printf(" ");
    }
    printf("\n");
}

// STREAMING_CHUNK: Initialization and input
int main() {
unsigned int num1, num2;
int pos, n;

printf("Enter the first integer: ");
scanf("%u", &num1);

printf("Enter the second integer: ");
scanf("%u", &num2);

printf("Enter the starting bit position (0-31): ");
scanf("%d", &pos);

printf("Enter the number of bits (n) to swap: ");
scanf("%d", &n);

printf("\n--- BEFORE SWAP ---\n");
printf("Num1: %10u -> ", num1); printBinary(num1);
printf("Num2: %10u -> ", num2); printBinary(num2);

// STREAMING_CHUNK: Swap loop satisfying assignment prerequisites
// We use a loop to iterate through the 'n' bits one by one.
for (int i = 0; i < n; i++) {
    int currentPos = pos + i;
    
    // Ensure we do not exceed 32 bits
    if (currentPos < 32) {
        // Extract the specific bit from both numbers
        int bit1 = (num1 >> currentPos) & 1;
        int bit2 = (num2 >> currentPos) & 1;
        
        // If the bits are different, we need to swap them.
        // Swapping a bit when they are different is the same as toggling it!
        if (bit1 != bit2) {
            num1 = num1 ^ (1U << currentPos); // Toggle bit in num1
            num2 = num2 ^ (1U << currentPos); // Toggle bit in num2
        }
    }
}

// STREAMING_CHUNK: Final output
printf("\n--- AFTER SWAP ---\n");
printf("Num1: %10u -> ", num1); printBinary(num1);
printf("Num2: %10u -> ", num2); printBinary(num2);

return 0;


}