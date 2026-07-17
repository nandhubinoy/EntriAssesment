#include <stdio.h>
#include <string.h>

int main() {
long long int num; // Using long long to prevent overflow issues
char str[100];
int i = 0;
int isNegative = 0;

printf("Enter a whole number: ");
scanf("%lld", &num);

// Handle 0 explicitly as a special case
if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
} else {
    // Check for negative number
    if (num < 0) {
        isNegative = 1;
        num = -num; // Make it positive for digit extraction
    }

    // Extract digits one by one
    while (num > 0) {
        int digit = num % 10;
        str[i++] = digit + '0'; // Convert integer digit to ASCII character
        num /= 10;
    }

    // Add the negative sign if required
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string because digits were extracted backwards
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

printf("The resulting string is: \"%s\"\n", str);
return 0;
}