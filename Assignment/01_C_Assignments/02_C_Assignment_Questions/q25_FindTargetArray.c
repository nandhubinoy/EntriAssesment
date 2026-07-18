#include <stdio.h>

int main() 
{
int arr[100];
int size, target;
int pairFound = 0; // Flag to track if at least one pair was found

/* STREAMING_CHUNK: Reading array and target sum... */
printf("Enter the size of the array: ");
scanf("%d", &size);

printf("Enter %d elements:\n", size);
for (int i = 0; i < size; i++) 
{
    scanf("%d", &arr[i]);
}

printf("Enter the target sum: ");
scanf("%d", &target);

/* STREAMING_CHUNK: Nested loops to find pairs matching the target sum... */
printf("\nPairs with sum %d:\n", target);

// Outer loop picks the first element of the pair
for (int i = 0; i < size; i++) 
{
    // Inner loop starts from i+1 to avoid pairing an element with itself
    // and to avoid printing reverse pairs (e.g., printing both 3+4 and 4+3)
    for (int j = i + 1; j < size; j++) 
    {
        
        // Check if the sum matches the target
        if (arr[i] + arr[j] == target) 
        {
            printf("(%d, %d)\n", arr[i], arr[j]);
            pairFound = 1;
        }
    }
}

/* STREAMING_CHUNK: Final status check... */
if (!pairFound) 
{
    printf("No such pairs exist in the array.\n");
}

return 0;
}