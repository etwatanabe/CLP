#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaração da função gera_pcode, que gera código p-code a partir de código intermediário
void gera_pcode(const char* codigo_intermediario);

int main() {
    // Matriz de strings contendo expressões em código intermediário
    const char* expressoes[][10] = {
        {"PUSH(7)", "PUSH(2)", "PUSH(4)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(8)", "PUSH(5)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(4)", "PUSH(3)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(6)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(9)", "PUSH(3)", "PUSH(1)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(10)", "PUSH(4)", "y=POP(); x=POP(); PUSH(x SUB y)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(3)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(6)", "PUSH(8)", "PUSH(4)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(3)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(4)", "PUSH(1)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(5)", "PUSH(3)", "PUSH(9)", "PUSH(6)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x MUL y)"},
        {"PUSH(7)", "PUSH(2)", "PUSH(5)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(8)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x ADD y)", "PUSH(3)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x MUL y)"}
    };

    // Calcula o número de expressões
    size_t num_expressoes = sizeof(expressoes) / sizeof(expressoes[0]);

    // Loop para processar cada expressão
    for (size_t i = 0; i < num_expressoes; i++) {
        printf("Expressão %zu:\n", i + 1);
        size_t j = 0;
        // Loop para processar cada instrução na expressão
        while (expressoes[i][j] != NULL) {
            // Chama a função gera_pcode para cada instrução
            gera_pcode(expressoes[i][j]);
            j++;
        }
        printf("\n");
    }

    return 0;
}

// Função que gera código p-code a partir de código intermediário
void gera_pcode(const char* codigo_intermediario) {
    // Verifica se a instrução é um PUSH com um valor literal
    if (strncmp(codigo_intermediario, "PUSH(", 5) == 0) {
        int valor;
        sscanf(codigo_intermediario, "PUSH(%d)", &valor);
        printf("LIT 0 %d\n", valor); // Gera a instrução LIT do p-code
    }
    // Verifica se a instrução é uma adição
    else if (strstr(codigo_intermediario, "PUSH(x ADD y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 2\n"); // Realiza a operação de adição
    }
    // Verifica se a instrução é uma subtração
    else if (strstr(codigo_intermediario, "PUSH(x SUB y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 3\n"); // Realiza a operação de subtração
    }
    // Verifica se a instrução é uma multiplicação
    else if (strstr(codigo_intermediario, "PUSH(x MUL y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 4\n"); // Realiza a operação de multiplicação
    }
    // Verifica se a instrução é uma divisão
    else if (strstr(codigo_intermediario, "PUSH(x DIV y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 5\n"); // Realiza a operação de divisão
    }
    // Se a instrução não for reconhecida, exibe um erro e termina o programa
    else {
        fprintf(stderr, "Operação desconhecida: %s\n", codigo_intermediario);
        exit(1);
    }
}
