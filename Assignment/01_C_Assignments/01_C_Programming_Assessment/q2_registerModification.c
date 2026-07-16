/* Register Modification 
Write a c code with 3 functions to set the 3rd bit, clear the 5th bit and toggle the 2nd bit.
*/
#include<stdio.h>

/*
 * Prints an 8-bit unsigned char in binary format.
 */
void printBinary(unsigned char val) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
        if (i == 4) printf(" "); // Adds a space for readability (e.g., 0010 0100)
    }
}

unsigned char modifyRegister(unsigned char reg) 
{
    // Set the 3rd bit (index 2) using Bitwise OR
    reg = reg | (1 << 2);
    
    // Clear the 6th bit (index 5) using Bitwise AND with a negated mask
    reg = reg & ~(1 << 5);
    
    // Toggle the 1st bit (index 0) using Bitwise XOR
    reg = reg ^ (1 << 0);
    
    return reg;
}

int main ()
{
    int regValue;
    printf("Enter an 8-bit register value (0-255): ");
    scanf("%d", &regValue);
    
    printf("Given register value in Binary: ");
    printBinary((unsigned char)regValue);
    printf("\n");
    
    unsigned char modifiedReg = modifyRegister((unsigned char)regValue);
    printf("Modified register value: ");
    printBinary(modifiedReg);
    printf(", in Decimal:%u\n", modifiedReg); // Print the modified register value in decimal
    
    return 0;
}