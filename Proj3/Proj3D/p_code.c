#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EXPRESSIONS 10
#define MAX_INSTRUCTIONS 15

// Função que gera código p-code a partir de código intermediário
void gera_pcode(char* code) {
    if (strncmp(code, "PUSH(", 5) == 0) {
        char variavel;
        sscanf(code, "PUSH(%c)", &variavel);
        printf("LOD 0 %c\n", variavel - 46); // 'a'=3, 'b'=4, 'c'=5, 'd'=6, 'e'=7

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
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x SUB y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(a)", "PUSH(b)", "y=POP(); x=POP(); PUSH(x ADD y)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(a)", "PUSH(b)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(c)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x DIV y)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(d)", "y=POP(); x=POP(); PUSH(x SUB y)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x ADD y)", "y=POP(); x=POP(); PUSH(x SUB y)"},
        {"PUSH(a)", "PUSH(b)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(c)", "PUSH(d)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(a)", "PUSH(b)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x MUL y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x SUB y)", "y=POP(); x=POP(); PUSH(x ADD y)"},
        {"PUSH(a)", "PUSH(b)", "y=POP(); x=POP(); PUSH(x ADD y)", "PUSH(c)", "y=POP(); x=POP(); PUSH(x DIV y)", "PUSH(d)", "PUSH(e)", "y=POP(); x=POP(); PUSH(x MUL y)", "y=POP(); x=POP(); PUSH(x ADD y)"}
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