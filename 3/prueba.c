#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 10240

int multiply_and_sum(const char *input) {
    int total_sum = 0;
    const char *ptr = input;

    while (*ptr) {
        // Look for 'mul('
        if (strncmp(ptr, "mul(", 4) == 0) {
            ptr += 4; // Move past 'mul('

            // Read the first number
            while (*ptr && !isdigit(*ptr) && *ptr != '-' && *ptr != '+') {
                ptr++;
            }
            char *endptr;
            int x = strtol(ptr, &endptr, 10); // Convert to integer
            ptr = endptr; // Move past the first number

            // Look for the comma
            while (*ptr && *ptr != ',') {
                ptr++;
            }
            if (*ptr == ',') {
                ptr++; // Move past the comma
            }

            // Read the second number
            while (*ptr && !isdigit(*ptr) && *ptr != '-' && *ptr != '+') {
                ptr++;
            }
            int y = strtol(ptr, &endptr, 10); // Convert to integer
            ptr = endptr; // Move past the second number

            // Look for the closing parenthesis
            while (*ptr && *ptr != ')') {
                ptr++;
            }
            if (*ptr == ')') {
                total_sum += x * y; // Add the product to the total sum
            }
        } else {
            ptr++;
        }
    }

    return total_sum;
}

int main() {
    FILE *file = fopen("text.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    int total_sum = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        total_sum += multiply_and_sum(line); // Process the line and add to total
    }

    printf("Total sum of valid multiplications: %d\n", total_sum); // Output the result

    fclose(file);
    return 0;
}