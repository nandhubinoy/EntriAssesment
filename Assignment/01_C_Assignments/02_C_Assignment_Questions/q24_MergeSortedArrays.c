#include <stdio.h>

int main() {
int arr1[100], arr2[100], merged[200];
int size1, size2;

/* STREAMING_CHUNK: Reading the two sorted arrays... */
printf("Enter the size of the FIRST sorted array: ");
scanf("%d", &size1);
printf("Enter %d sorted elements for array 1:\n", size1);
for (int i = 0; i < size1; i++) {
    scanf("%d", &arr1[i]);
}

printf("\nEnter the size of the SECOND sorted array: ");
scanf("%d", &size2);
printf("Enter %d sorted elements for array 2:\n", size2);
for (int i = 0; i < size2; i++) {
    scanf("%d", &arr2[i]);
}

/* STREAMING_CHUNK: Merging process using two pointers... */
int i = 0; // Pointer for arr1
int j = 0; // Pointer for arr2
int k = 0; // Pointer for merged array

// Compare elements from both arrays and insert the smaller one
while (i < size1 && j < size2) {
    if (arr1[i] <= arr2[j]) {
        merged[k] = arr1[i];
        i++;
    } else {
        merged[k] = arr2[j];
        j++;
    }
    k++;
}

/* STREAMING_CHUNK: Appending remaining elements... */
// If there are remaining elements in arr1, copy them
while (i < size1) {
    merged[k] = arr1[i];
    i++;
    k++;
}

// If there are remaining elements in arr2, copy them
while (j < size2) {
    merged[k] = arr2[j];
    j++;
    k++;
}

/* STREAMING_CHUNK: Printing the merged array... */
printf("\nMerged Sorted Array:\n");
for (int m = 0; m < size1 + size2; m++) {
    printf("%d ", merged[m]);
}
printf("\n");

return 0;


}