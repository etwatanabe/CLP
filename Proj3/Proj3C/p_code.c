#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EXPRESSIONS 10
#define MAX_INSTRUCTIONS 15

// Função que gera código p-code a partir de código intermediário
void gera_pcode(char* code) {
    if (strncmp(code, "PUSH(", 5) == 0) {
        int valor;
        sscanf(code, "PUSH(%d)", &valor);
        printf("LIT 0 %d\n", valor);
    } else if (strstr(code, "PUSH(x ADD y)")) {
        printf("OPR 0 2\n");
    } else if (strstr(code, "PUSH(x SUB y)")) {
        printf("OPR 0 3\n");
    } else if (strstr(code, "PUSH(x MUL y)")) {
        printf("OPR 0 4\n");
    } else if (strstr(code, "PUSH(x DIV y)")) {
        printf("OPR 0 5\n");
    } else {
        fprintf(stderr, "Operação desconhecida: %s\n", code);
        exit(1);
    }
}

int main() {
    char* expressions[NUM_EXPRESSIONS][MAX_INSTRUCTIONS] = {
        {"PUSH(3)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(5)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(4)", "PUSH(6)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(7)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(8)", "PUSH(7)", "PUSH(1)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(5)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(2)", "PUSH(9)", "PUSH(5)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(3)", "PUSH(4)", "y=POP(); x=POP(); PUSH(x ADD y)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(6)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(1)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(3)", "PUSH(4)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(5)", "PUSH(3)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(8)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(8)", "PUSH(4)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(7)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(3)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)",},
        {"PUSH(6)", "PUSH(3)", "PUSH(2)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(5)", "y=POP(); x=POP(); PUSH(x ADD y)",},
        {"PUSH(9)", "PUSH(1)", "y=POP(); x=POP(); PUSH(x ADD y)", "PUSH(5)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(6)", "PUSH(2)", "PUSH(3)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)",}
    };

    for (int i = 0; i < NUM_EXPRESSIONS; i++) {
        printf("Expressao %d:\n", i + 1);
        int j = 0;
        while (expressions[i][j] != NULL) {
            gera_pcode(expressions[i][j]);
            j++;
        }
        printf("\n");
    }

    return 0;
}