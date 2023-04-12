#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define MAX_ANSWERS 5

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    char question[MAX_LINE_LENGTH];
    char answers[MAX_ANSWERS][MAX_LINE_LENGTH];
    int points[MAX_ANSWERS];
    int answer_count = 0;

    // Open input file for reading
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Could not open input file\n");
        exit(1);
    }

    // Open output file for writing
    output_file = fopen("output.csv", "w");
    if (output_file == NULL) {
        printf("Could not create output file\n");
        exit(1);
    }

    // Write headers to output file
    fprintf(output_file, "question,answer,points,answer,points,answer,points,answer,points,answer,points\n");

    // Read input file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_file)) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // If line starts with a number followed by a period, it's a new question
        if (isdigit(line[0]) && line[1] == '.') {
            // Write previous question's data to output file
            if (answer_count > 0) {
                fprintf(output_file, "%s,", question);
                for (int i = 0; i < answer_count; i++) {
                    strcpy(answers[i], (answers)[i]+3);
                    fprintf(output_file, "%s,%d", answers[i], points[i]);
                    if (i < answer_count - 1) {
                        fprintf(output_file, ",");
                    }
                }
                fprintf(output_file, "\n");
                answer_count = 0;
            }

            // Store new question
            strcpy(question, line);
        } else {
            // Parse answer and points from line
            char *answer = strtok(line, " ");
            int points_value = atoi(strtok(NULL, " "));

            // Add answer and points to arrays
            if (answer_count < MAX_ANSWERS) {
                strcpy(answers[answer_count], answer);
                points[answer_count] = points_value;
                answer_count++;
            }
        }
    }

    // Write data for last question to output file
    if (answer_count > 0) {
        fprintf(output_file, "%s,", question);
        for (int i = 0; i < answer_count; i++) {
            strcpy(answers[i], (answers)[i]+3);
            fprintf(output_file, "%s,%d", answers[i], points[i]);
            if (i < answer_count - 1) {
                fprintf(output_file, ",");
            }
        }
        fprintf(output_file, "\n");
    }

    // Close input and output files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
