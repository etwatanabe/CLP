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

    while (!feof(fp)) {
        // Leitura da linha do arquivo
        char str[MAX_STR] = {};
        fscanf(fp, "%[^\n]%*c", str);

        // Analise lexica
        for(int i = 0; str[i] != '\0'; i++) {
            if(str[i] != '0' && str[i] != '1') {
                printf("REJEITADA: %s\n", str); 
                break;
            }
            else if(str[i + 1] == '\0')
                printf("RECONHECIDA: %s\n", str);
        }
    }

    fclose(fp);
    return 0;
}