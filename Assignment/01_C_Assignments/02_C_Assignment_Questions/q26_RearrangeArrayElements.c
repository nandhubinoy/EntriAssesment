#include <stdio.h>

int main() 
{
int inputArray[100];
int temp[100]; // Temporary storage to satisfy assignment pre-requisites
int size;

/* STREAMING_CHUNK: Input collection... */
printf("Enter the size of the inputArray: ");
scanf("%d", &size);

printf("Enter %d elements (mix of positive and negative):\n", size);
for (int i = 0; i < size; i++) 
{
    scanf("%d", &inputArray[i]);
}

/* STREAMING_CHUNK: Temporary storage allocation and separation... */
int tempIndex = 0;

// Step 1: Copy all negative numbers to the temp inputArray first.
// This perfectly preserves their original relative order.
for (int i = 0; i < size; i++) 
{
    if (inputArray[i] < 0) {
        temp[tempIndex++] = inputArray[i];
    }
}

// Step 2: Copy all positive numbers (and zero) to the temp inputArrayay.
// This preserves their relative order, placing them after the negatives.
for (int i = 0; i < size; i++) 
{
    if (inputArray[i] >= 0) {
        temp[tempIndex++] = inputArray[i];
    }
}

/* STREAMING_CHUNK: Merging back to original inputArrayay and printing... */
// Step 3: Copy the reinputArrayanged elements back to the original inputArrayay
for (int i = 0; i < size; i++) 
{
    inputArray[i] = temp[i];
}

// Display the results
printf("\nRearranged inputArrayay (Negatives first, Positives second):\n");
for (int i = 0; i < size; i++) 
{
    printf("%d ", inputArray[i]);
}
printf("\n");
return 0;
}