#include <stdio.h>

int main() {
char str[500];

printf("Enter a string: ");
fgets(str, sizeof(str), stdin);

// Loop through each character
for (int i = 0; str[i] != '\0'; i++) {
    // Check if it is an uppercase letter using ASCII bounds
    if (str[i] >= 'A' && str[i] <= 'Z') {
        // Convert to lowercase by adding 32 (Difference between 'a' and 'A')
        str[i] = str[i] + 32; 
    }
}

printf("Converted string: %s", str);

return 0;
}