#include <stdio.h>

int main() {
    int n;
    unsigned long long t1 = 0, t2 = 1, nextTerm;

    printf("Enter the number of terms (n) for the Fibonacci sequence: ");
    scanf("%d", &n);

    if (n <= 0) 
    {
        printf("Please enter a positive integer.\n");
    } else 
    {
        printf("Fibonacci Series up to %d terms: ", n);

        for (int i = 1; i <= n; i++) 
        {
            printf("%llu", t1);
            
            // Format output with commas
            if (i != n) 
            {
                printf(", ");
            }

            // Calculate the next term
            nextTerm = t1 + t2;
            t1 = t2;
            t2 = nextTerm;
        }
        printf("\n");
    }

    return 0;
}