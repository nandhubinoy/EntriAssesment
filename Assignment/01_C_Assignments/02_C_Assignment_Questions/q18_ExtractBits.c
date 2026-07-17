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

void extractBitsfromPosition(int number, int position, int numofbits)
{
    number = number >> position;
    unsigned int mask = (1U << numofbits) - 1;
    unsigned int extractedBits = number & mask;
    printf("The extracted bits are: %u-> ", extractedBits);
    printBinary(extractedBits);
}

int main()
{
    int num, pos, n;
    // Prompt the user for input
    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("Enter the starting bit position (0-31, where 0 is rightmost): ");
    scanf("%d", &pos);

    printf("Enter the number of bits to be extracted: ");
    scanf("%d", &n);

    printf("The binary number before extraction: %d-> ", num);
    printBinary(num);

    extractBitsfromPosition(num, pos, n);
    return 0;
}