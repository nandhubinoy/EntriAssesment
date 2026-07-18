#include<stdio.h>
/* Function to reverse a portion of the array... */
// Using the array reversal algorithm to rotate with O(1) extra space
void reverseArray(int arr[], int start, int end) 
{
    while (start < end) 
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() 
{
    int arr[100];
    int size, n;
    char direction;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) 
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter number of positions to rotate (n): ");
    scanf("%d", &n);

    printf("Enter direction ('L' for left, 'R' for right): ");
    scanf(" %c", &direction); // Leading space to catch newline

    // Normalize n to handle cases where n > size
    n = n % size;

    if (n < 0) n = n + size; // Handle negative inputs safely

    // If n is 0 after modulus, no rotation is needed
if (n != 0) 
{
    if (direction == 'L' || direction == 'l') 
    {
        // Left Rotation Logic
        reverseArray(arr, 0, n - 1);         // Reverse first n elements
        reverseArray(arr, n, size - 1);      // Reverse remaining elements
        reverseArray(arr, 0, size - 1);      // Reverse entire array
    } 
    else 
    if (direction == 'R' || direction == 'r') 
    {
        // Right Rotation Logic
        reverseArray(arr, size - n, size - 1); // Reverse last n elements
        reverseArray(arr, 0, size - n - 1);    // Reverse remaining elements
        reverseArray(arr, 0, size - 1);        // Reverse entire array
    } 
    else 
    {
        printf("Invalid direction entered.\n");
        return 1;
    }
}

printf("\nRotated Array:\n");
for (int i = 0; i < size; i++) 
{
    printf("%d ", arr[i]);
}
printf("\n");

return 0;
}