#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to check if a string consists only of digits
int isInteger(const char *str) {
    // Iterate through each character in the string
    while (*str) {
        // If any character is not a digit, return 0
        if (!isdigit(*str))
            return 0;
        str++;
    }
    // If all characters are digits, return 1
    return 1;
}

int main() {
    FILE *file;
    double x, y;
    double sum_xy = 0, sum_x = 0, sum_y = 0, sum_x_squared = 0;
    int n = 0;
    char filename[20]; // Declare filename variable

    // Loop through the datasets
    int i;
    for (i = 1; i <= 4; i++) {
        sprintf(filename, "datasetLR%d.txt", i); // Construct filename
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            return 1;
        }

        // Read values from the file and calculate sums
        while (fscanf(file, "%lf,%lf", &x, &y) == 2) {
            sum_xy += x * y;
            sum_x += x;
            sum_y += y;
            sum_x_squared += x * x;
            n++;
        }

        // Close the file
        fclose(file);
    }

    // Check if there is at least one data point
    if (n > 0) {
        // Calculate the coefficients A and B for the linear regression equation
        double A = (sum_y * sum_x_squared - sum_x * sum_xy) / (n * sum_x_squared - sum_x * sum_x);
        double B = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);

        // Print the results
        printf("A: %lf\n", A);
        printf("B: %lf\n", B);
        printf("Equation of the regression line: y = %.2lfx + %.2lf\n", B, A);
       
        char input[100];
        printf("Enter a value of x to calculate y: ");
        
        // Read user input as a string
        if (scanf("%s", input) != 1 || !isInteger(input)) {
            // Display error message if input is not an integer
            printf("Error: Please enter an integer value.\n");
            return 1;
        }
       
        int inputX = atoi(input); // Convert string to integer
        double resultY = B * inputX + A;
       
        // Display calculated values
        printf("X: %d\n", inputX);
        printf("For x = %d, y = %.2lf\n", inputX, resultY);
       
    } else {
        printf("No data points found in the file.\n");
    }

    return 0;
}

