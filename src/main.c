#include <stdlib.h>
#include <stdio.h>
#include "reader.h"



int main(void) {

    // File pointer check
    FILE *file = fopen("data/credit_card_statement.csv", "r");
    if (file == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return -1;
    }

    // Buffer creation
    char line[1024];
    const char separator = ',';

    // Read the first line of the categories
    fgets(line, 1024, file);
    int separator_counting = count_separators(line, "Valor", separator); // 4

    double sum = 0;
    const char *file_readed = fgets(line, 1024, file);
    while (file_readed) {
        // Define the position of the start of number substring
        const int position = locate_number_substring(line, separator, separator_counting); // Location of number substring

        // Get the number string
        char *number_str = number_sub_string(line, separator, position);

        if (number_str != NULL) {
            // Convert the number string to a double
            double result = read_float_by_str(number_str, separator);
            sum += result;

            // Free the allocated memory for number_str and nullify
            free(number_str);
            number_str = NULL;
        }

        file_readed = fgets(line, 1024, file);
    }

    char ch;
    printf("Run: ");
    scanf("%c", &ch);

    // Print the result
    printf("Sum: R$ %.2lf\n", sum);

    // Handle final control operations
    fclose(file);
    return 0;
}


