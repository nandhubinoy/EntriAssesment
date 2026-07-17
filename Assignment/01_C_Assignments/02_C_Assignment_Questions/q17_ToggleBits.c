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

void toggleBitsfromPosition(unsigned int number, int position, int numofbits)
{
    for(int i=0; i < numofbits; i++)
    {
        if(position + i < 32)
        {
            number = number^(1 << (position + i));
        }
    }
    printf("The binary number after toggling: %u-> ", number);
    printBinary(number);
}

int main()
{
    unsigned int num;
    int pos, n;
    // Prompt the user for input
    printf("Enter a positive integer: ");
    scanf("%u", &num);

    printf("Enter the starting bit position (0-31, where 0 is rightmost): ");
    scanf("%d", &pos);

    printf("Enter the number of bits to toggle: ");
    scanf("%d", &n);

    printf("The binary number before toggling: %u-> ", num);
    printBinary(num);

    toggleBitsfromPosition(num, pos, n);

    return 0;
}