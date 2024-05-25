#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declara��o da fun��o gera_pcode, que gera c�digo p-code a partir de c�digo intermedi�rio
void gera_pcode(const char* codigo_intermediario);

int main() {
    // Matriz de strings contendo express�es em c�digo intermedi�rio
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

    // Calcula o n�mero de express�es
    size_t num_expressoes = sizeof(expressoes) / sizeof(expressoes[0]);

    // Loop para processar cada express�o
    for (size_t i = 0; i < num_expressoes; i++) {
        printf("Express�o %zu:\n", i + 1);
        size_t j = 0;
        // Loop para processar cada instru��o na express�o
        while (expressoes[i][j] != NULL) {
            // Chama a fun��o gera_pcode para cada instru��o
            gera_pcode(expressoes[i][j]);
            j++;
        }
        printf("\n");
    }

    return 0;
}

// Fun��o que gera c�digo p-code a partir de c�digo intermedi�rio
void gera_pcode(const char* codigo_intermediario) {
    // Verifica se a instru��o � um PUSH com um valor literal
    if (strncmp(codigo_intermediario, "PUSH(", 5) == 0) {
        int valor;
        sscanf(codigo_intermediario, "PUSH(%d)", &valor);
        printf("LIT 0 %d\n", valor); // Gera a instru��o LIT do p-code
    }
    // Verifica se a instru��o � uma adi��o
    else if (strstr(codigo_intermediario, "PUSH(x ADD y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 2\n"); // Realiza a opera��o de adi��o
    }
    // Verifica se a instru��o � uma subtra��o
    else if (strstr(codigo_intermediario, "PUSH(x SUB y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 3\n"); // Realiza a opera��o de subtra��o
    }
    // Verifica se a instru��o � uma multiplica��o
    else if (strstr(codigo_intermediario, "PUSH(x MUL y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 4\n"); // Realiza a opera��o de multiplica��o
    }
    // Verifica se a instru��o � uma divis�o
    else if (strstr(codigo_intermediario, "PUSH(x DIV y)") != NULL) {
        printf("LOD 0 2\n"); // Carrega o valor de x
        printf("LOD 0 3\n"); // Carrega o valor de y
        printf("OPR 0 5\n"); // Realiza a opera��o de divis�o
    }
    // Se a instru��o n�o for reconhecida, exibe um erro e termina o programa
    else {
        fprintf(stderr, "Opera��o desconhecida: %s\n", codigo_intermediario);
        exit(1);
    }
}
