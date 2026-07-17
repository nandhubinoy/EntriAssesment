#include <stdio.h>

int main() {
char str[100];
long long int result = 0;
int i = 0;
int sign = 1;

// Prompt user for a string
printf("Enter a number as a string: ");
fgets(str, sizeof(str), stdin);

// Handle negative numbers if present
if (str[0] == '-') {
    sign = -1;
    i++; // Move to the next character
}

// Process each character
while (str[i] != '\0' && str[i] != '\n') {
    // Check if the character is a valid digit (ASCII '0' to '9')
    if (str[i] >= '0' && str[i] <= '9') {
        // Convert character to integer value by subtracting ASCII '0'
        // Multiply current result by 10 to shift digits left
        result = result * 10 + (str[i] - '0');
    } else {
        // If a non-digit is encountered, stop processing
        printf("Non-digit character encountered. Stopping conversion.\n");
        break;
    }
    i++;
}

// Apply the sign
result = result * sign;

// Display the final integer result
printf("The integer value is: %lld\n", result);

return 0;


}