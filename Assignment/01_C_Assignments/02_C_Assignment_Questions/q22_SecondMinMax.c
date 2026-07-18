    #include <stdio.h>
    #include <limits.h>

    int main() 
    {
    int arr[100];
    int size;

    /* Prompt the user to enter the size of the array */
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    if (size < 2) {
        printf("Array must have at least 2 elements to find the second largest/smallest.\n");
        return 1;
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    /* STREAMING_CHUNK: Finding distinct largest and smallest elements... */
    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    // Single pass to find the first and second largest/smallest
    for (int i = 0; i < size; i++) 
    {
        // Update largest and second largest
        if (arr[i] > max1) 
        {
            max2 = max1;
            max1 = arr[i];
        } 
        else 
        if (arr[i] > max2 && arr[i] != max1) 
        {
            max2 = arr[i];
        }

        // Update smallest and second smallest
        if (arr[i] < min1) 
        {
            min2 = min1;
            min1 = arr[i];
        } 
        else 
        if (arr[i] < min2 && arr[i] != min1) 
        {
            min2 = arr[i];
        }
    }

    /* STREAMING_CHUNK: Displaying results with duplicate handling... */
    printf("\n--- Results ---\n");

    if (max2 == INT_MIN || min2 == INT_MAX) {
        printf("All elements in the array are identical. No second largest or second smallest exists.\n");
    } else {
        printf("Second Largest Element : %d\n", max2);
        printf("Second Smallest Element: %d\n", min2);
    }

    return 0;


    }