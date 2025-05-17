//
// Created by zegui on 19/01/2025.
//
#include <stdlib.h>
#include <stdio.h>

char *read_csv_to_array(FILE *file) { // Salva o arquivo .csv em um array
    if (file == NULL) {
        return NULL;
    }

    int tamanho = 4096;
    char *array = (char *)malloc(sizeof(char) * tamanho);
    if (array == NULL) {
        return NULL;
    }

    int i = 0;
    int ch = fgetc(file);
    while (ch != EOF) {
        array[i] = (char) ch;
        i++;
        ch = fgetc(file);
    }

    return array;
}

char *ler_entre_aspas(char *text) { // Lê um texto que está entre aspas
    if (text == NULL) {
        return NULL;
    }
    int i = 0;
    while (text[i] != '"') {
        i++;
    }

    int contador = 0;
    while (text[i + 1 + contador] != '"' && text[i + 1 + contador] != '\n' && text[i + 1 + contador] != '\0') {
        contador++;
    }

    char *str = (char *)malloc(sizeof(char) * (contador + 1));
    if (str == NULL) {
        return NULL;
    }

    for (int j = 0; j < contador; j++) {
        str[j] = text[i + 1 + j];
    }
    str[contador] = '\0';
    return str;
}

char *ler_numero_texto(char *text) { // Lê um número texto das aspas do valor no csv
    if (text == NULL) {
        return NULL;
    }

    char *em_aspas = ler_entre_aspas(text);
    if (em_aspas == NULL) {
        return NULL;
    }

    int contador = 0;
    while (em_aspas[contador] != '\0') {
        contador++;
    }
    contador++;

    char *texto_numero = (char *)malloc(sizeof(char) * (contador - 3));
    if (texto_numero == NULL) {
        return NULL;
    }

    for (int i = 0; i < contador - 3; i++) {
        texto_numero[i] = em_aspas[i + 3];
    }

    free(em_aspas);
    return texto_numero;
}

float numero_csv(char *text) {
    if (text == NULL) {
        return 0.0001f;
    }

    char *texto_numero = ler_numero_texto(text);
    if (texto_numero == NULL) {
        return 0.0001f;
    }
    const char sep = ',';
    float valor = read_float_by_str(texto_numero, sep);

    free(texto_numero);

    return valor;
}

float soma_total_da_fatura(char *csv, int l) {
    if (csv == NULL) {
        return -1;
    }
    // Salvar o csv em um array
    // Procura "valor" e salva quantas vírgulas são até ele
    // Pula esse tanto de vírgulas e salva o endereço do primeiro caractere do valor
    // Acessa esse endereço, ler todo o valor e transforma ele para inteiro
    // Coloca esse valor float em um array
    // Soma os valores do array e soma

    const char sep = ',';
    int categoria = count_separators(csv, "valor", sep);
    int p = 0;
    while (csv[p] != '\n') {
        p++;
    }
    p++;

    int virgulas = 0;
    int linhas = l;
    float valores[l];
    float valor;
    for (int linha = 0; linha < linhas; linha++) {
        while (csv[p] != '\n') {
            if (csv[p] == ',') {
                virgulas++;
            }
            if (virgulas >= categoria) {
                valor = numero_csv(&csv[p]);
                valores[linha] = valor;
            }
            p++;
        }
    }
    float soma = 0;
    for (int i = 0; i < l; i++) {
        soma += valores[i];
    }
    free(csv);

    return soma;
}
