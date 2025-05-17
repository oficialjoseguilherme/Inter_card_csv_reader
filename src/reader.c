#include <stdlib.h>
#include <stdio.h>

int count_separators(const char *str, const char *category, const char separator) { // Conta a quantidade de vírgulas para a categoria desejada
    if (str == NULL || category == NULL) {
        return -1;
    }

    int contador = 0;
    int naoAchou = 1;
    for (int i = 0; naoAchou && str[i] != EOF && str[i] != '\n'; i++) {
        if (str[i] == separator) {
            contador++;
        }
        if (str[i] == category[0]) {
            int continua = 1;
            naoAchou = 0;
            for (int j = 0; continua && category[j] != '\0' && str[i + j] != EOF && str[i + j] != '\n'; j++) {
                if (category[j] != str[i + j]) {
                    naoAchou = 1;
                    continua = 0;
                }
            }
        }
    }

    return contador;
}

int char_to_int(char c) { // Converte caractere para inteiro
    if (c < '0' || c > '9') {
        return 0;
    }

    return c - '0';
}

double read_float_by_str(const char *str, const char separator) { // Lê valor do número em texto do csv
    if (str == NULL) {
        return 0.0001f;
    }

    double valor = 0;
    for (int i = 0; str[i - 1] != separator && str[i] != '\0'; i++) {
        if (str[i] == separator) {
            double aux = 0;
            for (int j = i - 1; j >= 0; j--) {
                aux = (double) char_to_int(str[j]);
                for (int k = 0; k < (i - 1) - j; k++) {
                    aux *= 10;
                }

                valor += aux;
            }

            for (int j = i + 1; str[j] != '\0'; j++) {
                aux = (double) char_to_int(str[j]);
                for (int k = 0; k < j - i; k++) {
                    aux /= 10;
                }
                valor += aux;
            }
        }
    }

    return valor;
}

int is_character_of_float(const char ch, const char separator) {
    return (ch >= '0' && ch <= '9') || ch == separator;
}

char *number_sub_string(const char *str, const char separator, const int position) {
    if (str == NULL || position < 0) {
        return NULL;
    }

    int length = 0; // Length of number substring
    int start = 0; // Position of the start of number substring
    int done = 0; // Flag to indicate that the loop has completed
    for (int i = position; str[i] != '\0' && str[i] != '\n' && !done; i++) {
        if (is_character_of_float(str[i], separator)) {
            for (int j = i; is_character_of_float(str[j], separator); j++) {
                length++;
            }
            start = i;
            done = 1;
        }
    }

    char *number_str = (char *)malloc(sizeof(char) * (length + 1));
    if (number_str == NULL) {
        return NULL;
    }

    done = 0;
    for (int i = start; str[i] != '\0' && str[i] != '\n' && !done; i++) {
        if (is_character_of_float(str[i], separator)) {
            for (int j = i; is_character_of_float(str[j], separator); j++) {
                number_str[j - i] = str[j];
            }
            number_str[length] = '\0';
            done = 1;
        }
    }

    return number_str;
}

int locate_number_substring(const char *str, const char separator, int category) {
    if (str == NULL) {
        return -1;
    }

    int position = 0;
    int separator_counting = 0;
    for (int i = 0; separator_counting < category; i++) {
        if (str[i] == separator) {
            separator_counting++;
            position = i;
        }
    }

    position++;
    return position;

}
