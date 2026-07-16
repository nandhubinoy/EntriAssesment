/*

*/
#include<stdio.h>
void printPyramid(int n) {
    // Loop through each row
    for (int i = 1; i <= n; i++) {
        
        // Print leading spaces (n - i spaces per row)
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        
        // Print stars (2*i - 1 stars per row to ensure odd numbers: 1, 3, 5...)
        for (int k = 1; k <= (2 * i - 1); k++) {
            printf("*");
        }
        
        // Move to the next line after finishing the row
        printf("\n");
    }
}
int main() 
{
    int n;
    printf("Enter the number of rows for the pyramid: ");
    scanf("%d", &n);
    printPyramid(n); 
    return 0;
}