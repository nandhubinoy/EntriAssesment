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

// STREAMING_CHUNK: User input collection
int main() {
unsigned int num1, num2;
int pos, n;

printf("Enter the FIRST positive integer (target): ");
scanf("%u", &num1);

printf("Enter the SECOND positive integer (source): ");
scanf("%u", &num2);

printf("Enter the starting bit position (0-31): ");
scanf("%d", &pos);

printf("Enter the number of bits (n) to replace: ");
scanf("%d", &n);

printf("\nOriginal First  : %10u -> ", num1);
printBinary(num1);
printf("Original Second : %10u -> ", num2);
printBinary(num2);

// STREAMING_CHUNK: Core bitwise replacement logic
// 1. Create a mask of 'n' ones (e.g., if n=3, mask = 000...0111)
unsigned int baseMask = (1U << n) - 1;

// 2. Clear 'n' bits in num1 at the specified position
// We shift the mask to 'pos', invert it (~), and AND it with num1
num1 = num1 & ~(baseMask << pos);

// 3. Extract the lowest 'n' bits from num2
unsigned int extractedBits = num2 & baseMask;

// 4. Shift the extracted bits to the target position and OR them into num1
num1 = num1 | (extractedBits << pos);

printf("\nModified First  : %10u -> ", num1);
printBinary(num1);

return 0;


}