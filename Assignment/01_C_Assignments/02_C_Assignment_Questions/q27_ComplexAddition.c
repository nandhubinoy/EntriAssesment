#include <stdio.h>

/* STREAMING_CHUNK: Structure definition... */
// Define the structure for a Complex number
typedef struct 
{
float real;
float imaginary;
} Complex;

/* Function definitions... */
// Function to add two complex numbers
Complex addComplex(Complex c1, Complex c2) 
{
Complex sum;
sum.real = c1.real + c2.real;
sum.imaginary = c1.imaginary + c2.imaginary;
return sum;
}

// Function to display a complex number in a readable format
void displayComplex(Complex c) 
{
    // Handle negative imaginary parts gracefully (e.g., 'a - bi' instead of 'a + -bi')
    if (c.imaginary < 0) 
    {
        printf("%.2f - %.2fi\n", c.real, -c.imaginary);
    } 
    else 
    {
        printf("%.2f + %.2fi\n", c.real, c.imaginary);
    }
}

/* STREAMING_CHUNK: Main function... */
int main() {
Complex num1, num2, result;

// Prompt user for the first complex number
printf("--- Enter the First Complex Number ---\n");
printf("Real part: ");
scanf("%f", &num1.real);
printf("Imaginary part: ");
scanf("%f", &num1.imaginary);

// Prompt user for the second complex number
printf("\n--- Enter the Second Complex Number ---\n");
printf("Real part: ");
scanf("%f", &num2.real);
printf("Imaginary part: ");
scanf("%f", &num2.imaginary);

// Call the function to compute the sum
result = addComplex(num1, num2);

// Display the inputs and the final result
printf("\n--- Results ---\n");
printf("First Number  : ");
displayComplex(num1);
printf("Second Number : ");
displayComplex(num2);
printf("Sum           : ");
displayComplex(result);

return 0;


}