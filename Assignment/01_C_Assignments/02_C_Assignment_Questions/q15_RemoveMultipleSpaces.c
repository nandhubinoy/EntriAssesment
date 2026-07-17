#include <stdio.h>

int main() {
char str[500];
char cleanStr[500];
int i = 0, j = 0;
int spaceFound = 0; // Flag to track consecutive spaces

printf("Enter a sentence with multiple spaces: ");
fgets(str, sizeof(str), stdin);

// Loop through the original string
while (str[i] != '\0') 
{
    if (str[i] == ' ') 
    {
        // If it's the first space we see, add it to the clean string
        if (spaceFound == 0) 
        {
            cleanStr[j++] = str[i];
            spaceFound = 1; // Mark that a space was just added
        }
    } 
    else 
    {
        // If it's not a space, add it and reset the space flag
        cleanStr[j++] = str[i];
        spaceFound = 0;
    }
    i++;
}

// Null terminate the new string
cleanStr[j] = '\0';

printf("Cleaned string: %s\n", cleanStr);

return 0;


}