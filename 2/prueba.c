#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_REPORTS 1000
#define MAX_LEVELS 100
#define MAX_LINE_LENGTH 256

// Function to check if a report is safe
bool is_safe(int levels[], int n) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 0; i < n - 1; i++) {
        if (levels[i] < levels[i + 1]) {
            decreasing = false;
        } else if (levels[i] > levels[i + 1]) {
            increasing = false;
        }
        if (abs(levels[i] - levels[i + 1]) < 1 || abs(levels[i] - levels[i + 1]) > 3) {
            return false;
        }
    }

    return increasing || decreasing;
}

// Function to check if removing one level can make the report safe
bool can_be_safe_by_removing_one(int levels[], int n) {
    for (int i = 0; i < n; i++) {
        int modified_report[MAX_LEVELS];
        int modified_size = 0;

        // Create a modified report by skipping the i-th level
        for (int j = 0; j < n; j++) {
            if (j != i) {
                modified_report[modified_size++] = levels[j];
            }
        }

        if (is_safe(modified_report, modified_size)) {
            return true;
        }
    }
    return false;
}

// Main function to count safe reports
int count_safe_reports(FILE *file) {
    int safe_count = 0;
    char line[MAX_LINE_LENGTH];
	int	line_count;

	line_count = 1;
    while (fgets(line, sizeof(line), file)) {
        int levels[MAX_LEVELS];
        int n = 0;

        // Parse the report into levels
        char *token = strtok(line, " \n");
        while (token != NULL) {
            levels[n++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        // Check if the report is safe or can be made safe
        if (is_safe(levels, n) || can_be_safe_by_removing_one(levels, n)) {
            safe_count++;
			printf("%d ", line_count);
        }
		line_count++;
    }

    return safe_count;
}

int main() {
    FILE *file = fopen("list.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Count safe reports
    int safe_reports_count = count_safe_reports(file);
    printf("%d\n", safe_reports_count); // Output the count of safe reports

    fclose(file);
    return 0;
}