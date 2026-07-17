#include <stdio.h>

// Function to count digit frequency, using Pass by Reference for the array
void countDigitFrequency(long long int number, int freqArray[]) {
    // Handle negative numbers by making them positive
    if (number < 0) {
        number = -number;
    }

    // Special case for 0
    if (number == 0) {
        freqArray[0]++;
        return;
    }

    // Extract each digit and update the array directly
    while (number > 0) {
        int digit = number % 10;
        freqArray[digit]++;
        number /= 10;
    }
}

int main() {
    long long int num;
    int frequency[10] = {0}; // Initialize array to store frequencies of 0-9

    printf("Enter an integer: ");
    scanf("%lld", &num);

    // Pass the number and the frequency array to the function
    countDigitFrequency(num, frequency);

    // Print the results
    printf("Digit Frequencies in %lld:\n", num);
    for (int i = 0; i < 10; i++) {
        if (frequency[i] > 0) {
            printf("Digit %d appears %d time(s)\n", i, frequency[i]);
        }
    }

    return 0;
}