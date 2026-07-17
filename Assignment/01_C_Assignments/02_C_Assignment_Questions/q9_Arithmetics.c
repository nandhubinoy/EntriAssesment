#include <stdio.h>

// Separate functions for each operation
float addition(float a, float b) {
    return a + b;
}

float subtraction(float a, float b) {
    return a - b;
}

float multiplication(float a, float b) {
    return a * b;
}

float division(float a, float b) {
    // Error Handling: Division by zero is handled gracefully
    if (b == 0) {
        printf("\nError: Division by zero is undefined!\n");
        return 0.0;
    }
    return a / b;
}

// Selector function using Switch/Conditionals
float calculate(char operator, float num1, float num2) {
    switch (operator) {
        case '+': 
            return addition(num1, num2);
        case '-': 
            return subtraction(num1, num2);
        case '*': 
            return multiplication(num1, num2);
        case '/': 
            return division(num1, num2);
        default: 
            printf("\nError: WRONG FUNCTION SELECTION\n");
            return 0.0;
    }
}

int main() {
    float frstValue, secValue, result;
    char operator;

    printf("Enter two floating-point numbers: ");
    scanf("%f %f", &frstValue, &secValue);
    
    printf("Enter the operation symbol (+, -, *, /): ");
    scanf(" %c", &operator); // Note the space before %c to catch any trailing newline

    // Call the selector function
    result = calculate(operator, frstValue, secValue);

    // Only print the result if it was a valid operation and not a div-by-zero error
    if ((operator == '+' || operator == '-' || operator == '*' || operator == '/') && 
        !(operator == '/' && secValue == 0)) {
        printf("RESULT: %.2f %c %.2f = %.2f\n", frstValue, operator, secValue, result);
    }

    return 0;
}