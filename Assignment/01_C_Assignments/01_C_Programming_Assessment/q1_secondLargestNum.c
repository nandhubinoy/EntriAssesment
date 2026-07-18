/*
1) Create an array of size 'n', and find the 2nd largest element in that array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findSecondLargest(int arr[], int size) 
{
    if (size < 2) return -1; // Or handle as an error

    int first, second;

    // Initialize based on the first two elements
    if (arr[0] > arr[1]) 
    {
        first = arr[0];
        second = arr[1];
    } 
    else 
    {
        first = arr[1];
        second = arr[0];
    }

    // Start loop from the third element
    for (int i = 2; i < size; i++) {
        if (arr[i] > first) 
        {
            second = first;
            first = arr[i];
        } 
        else 
        if (arr[i] > second && arr[i] != first) 
        {
            second = arr[i];
        }
    }

    return second;
}

int main() {
    int sizeofArray;

    printf("Enter the size of the array: ");
    scanf("%d", &sizeofArray);

    if (sizeofArray < 2) {
        printf("Array size must be at least 2 to find the second largest element.\n");
        return 1;
    }

    int arr[sizeofArray];
    printf("Enter %d elements:\n", sizeofArray);
    for (int i = 0; i < sizeofArray; i++) {
        scanf("%d", &arr[i]);
    }

    // FIX: Passed sizeofArray instead of n
    int secondLargest = findSecondLargest(arr, sizeofArray); 
    
    if (secondLargest == -1) {
        printf("There is no second largest element.\n");
    } else {
        printf("The second largest element is: %d\n", secondLargest);
    }

    return 0;
}