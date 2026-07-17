#include <stdio.h>
#include <string.h>

// Helper function to reverse a string
void reverseString(char* str) {
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to convert decimal to target base
void convertToBase(long long int decimalNumber, int targetBase, char* result) {
    int index = 0;
    int isNegative = 0;

    if (decimalNumber < 0) {
        isNegative = 1;
        decimalNumber = -decimalNumber;
    }

    if (decimalNumber == 0) {
        result[index++] = '0';
        result[index] = '\0';
        return;
    }

    // Repeated division method
    while (decimalNumber > 0) {
        int remainder = decimalNumber % targetBase;

        // Character handling for bases above 9
        if (remainder < 10) {
            result[index++] = remainder + '0'; 
        } else {
            result[index++] = (remainder - 10) + 'A'; 
        }
        decimalNumber /= targetBase;
    }

    if (isNegative) {
        result[index++] = '-';
    }
    
    result[index] = '\0'; // Null terminate
    reverseString(result); // Build result in correct order
}

int main() {
    long long int decimalNumber;
    int targetBase;
    char convertedValue[100] = {0};

    printf("Enter a decimal number: ");
    scanf("%lld", &decimalNumber);
    printf("Enter a target base (2 to 16): ");
    scanf("%d", &targetBase);

    if (targetBase < 2 || targetBase > 16) {
        printf("Error: Base must be between 2 and 16.\n");
        return 1;
    }

    convertToBase(decimalNumber, targetBase, convertedValue);
    printf("The decimal number %lld in base %d is: %s\n", decimalNumber, targetBase, convertedValue);

    return 0;
}