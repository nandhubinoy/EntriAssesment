#if 0
#include <stdio.h>
int main()
{
    int *ptr;
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    ptr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    int value = 0;
    for(int i = 0; i<n; i++)
    {
        scanf("\n",&ptr[i]);
    }

    return 0;
}
#endif

#if 0
#include <stdio.h>
void printBinary(int *number)
{    
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (*number & (1U << i)) ? 1 : 0);
        if((i%4)==0)
        {
            printf(" ");
        }
    }
    printf("\n");
}
void setBit(int number, int position)
{
    number |= (1U<<position-1);
    printBinary(&number);
}
void clearBit(int number, int position)
{
    number &= ~(1<<position-1);
    printBinary(&number);
}
void toggleBit(int number, int position)
{
    number ^= (1<<position-1);
    printBinary(&number);
}
int main()
{
    int num=0;
    printf("Enter the number: ");
    scanf("%d", &num);

        printf("Binary format of the number: ");
        printBinary(&num);
        printf("\nSet 3rd bit of the number: ");
        setBit(num, 3);
        printf("\nClear 5th bit of the number: ");
        clearBit(num,5);
        printf("\nToggle 2nd bit of the number: ");
        toggleBit(num, 2);

    return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
    int count = 5;
    for (int i = 0; i < count; i++)
    {
        for ( int j = 0; j < 2*(count-i-1); j++)
            printf(" ");

            for (int k = 0; k < 2*i+1; k++)
                printf("*");
            printf("\n");
        
    }
    
}
#endif

#if 1
#endif
#include <stdio.h>

int main() {
    int n = 5;

    // Outer loop to print all rows
    for (int i = 0; i < n; i++) {

        // First inner loop to print leading white spaces
        for (int j = 0; j < 2 * (n - i - 1); j++)
            printf(" ");

        // Second inner loop to print star * character
        for (int k = 0; k < 2 * i + 1; k++)
            printf("* ");
        printf("\n");
    }
    return 0;
}