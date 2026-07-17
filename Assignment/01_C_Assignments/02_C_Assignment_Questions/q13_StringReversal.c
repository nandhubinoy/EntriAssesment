#include <stdio.h>
#include <string.h>

int main() {
    char str[200];

    printf("Enter a string to reverse: ");
    fgets(str, sizeof(str), stdin);

    // Find the actual length of the string ignoring '\n' and '\0'
    int len = 0;
    while (str[len] != '\n' && str[len] != '\0') {
        len++;
    }

    int start = 0;
    int end = len - 1; // Reverse only the active characters

    // Iterative approach to swap characters
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        
        start++;
        end--;
    }

    // Output the reversed string (the original \0 at the end remains untouched)
    printf("Reversed string: %s\n", str);

    return 0;
}
