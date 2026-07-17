/*
    A pangram (from the Greek pan meaning "all" and gramma meaning "letter") 
    is a sentence or phrase that uses every letter of the alphabet at least once
*/
#include <stdio.h>
#include <string.h>

int main() {
char str[500];
int letters[26] = {0}; // Array to track presence of 'a' through 'z'
int isPangram = 1;

printf("Enter a sentence to check for Pangram: ");
fgets(str, sizeof(str), stdin);

// Loop through the string and mark found letters
for (int i = 0; str[i] != '\0'; i++) {
    // If character is uppercase, map to index 0-25
    if (str[i] >= 'A' && str[i] <= 'Z') {
        letters[str[i] - 'A'] = 1;
    }
    // If character is lowercase, map to index 0-25
    else if (str[i] >= 'a' && str[i] <= 'z') {
        letters[str[i] - 'a'] = 1;
    }
}

// Verify if all 26 letters were found
for (int i = 0; i < 26; i++) {
    if (letters[i] == 0) {
        isPangram = 0; // Found a missing letter
        break;
    }
}

if (isPangram) {
    printf("The input string IS a pangram.\n");
} else {
    printf("The input string is NOT a pangram.\n");
}

return 0;


}