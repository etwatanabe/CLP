/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 100

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    char line[MAX_STR];
    while (fgets(line, MAX_STR, fp) != NULL) {
        int isValid = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if ((line[i] < '0' || line[i] > '9') && (line[i] != '\n')) {
                isValid = 0;
                break;
            }
        }
        if (isValid)
            printf("RECONHECIDA: %s", line);
        else
            printf("REJEITADA: %s", line);
    }

    fclose(fp);
    return 0;
}