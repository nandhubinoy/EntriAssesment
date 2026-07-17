#include <stdio.h>
#include <string.h>

int main() 
{
    char str[200];
    int isPalindrome = 1; // Flag (1 = True, 0 = False)

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove the trailing newline character left by fgets
    str[strcspn(str, "\n")] = 0; 

    int start = 0;
    int end = strlen(str) - 1;

// Loop to compare characters from both ends moving towards the center
while (start < end) 
{
    if (str[start] != str[end]) {
        isPalindrome = 0; // Mismatch found, not a palindrome
        break;
    }
    start++;
    end--;
}

// Print result
if (isPalindrome) 
{
    printf("The string is a palindrome.\n");
} else 
{
    printf("The string is NOT a palindrome.\n");
}

return 0;


}