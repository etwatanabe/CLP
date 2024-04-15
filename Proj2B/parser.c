#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_OUTPUT_SIZE 10

// Estrutura para representar a pilha
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;
Stack stack = {"", -1};

typedef enum {
    P1, P2, NONE
} fct;
fct output[MAX_OUTPUT_SIZE];

// Funções para manipular a pilha
void initStack() {
    stack.items[++stack.top] = 'S';
}

void push(char* value) {
    int i = 0;
    while(value[i] != '\0') i++;
    for (i = i - 1; i >= 0; i--) {
        if (stack.top < MAX_STACK_SIZE - 1) {
            stack.items[++stack.top] = value[i];
        }
        else {
            printf("Stack Overflow\n");
        }
    }
}

void pop() {
    if (stack.top >= 0) {
         stack.items[stack.top--] = ' ';
    }
    else {
        printf("Stack Underflow\n");
    }
}

void printStack(int i, int d, fct p) {
    printf("%2d  %2d ", i, d);

    if (p == P1) {
        printf("  P1    ");
    } else if (p == P2) {
        printf("  P2    ");
    } else {
        printf("  -     ");
    };

    for (int j = stack.top; j >= 0; j--) {
        printf("%c", stack.items[j]);
    }
    printf("\n");
}

// Função para simular o autômato de pilha
int parser(FILE *fp) {
    int i = 0;

    printStack(i++, 0, NONE);
    initStack();

    char token = fgetc(fp);
    while (token != EOF) {
        if      (token=='a' && stack.items[stack.top]=='S') { printStack(i++, 1, P1); pop(); push("aSb"); }
        else if (token=='b' && stack.items[stack.top]=='S') { printStack(i++, 1, P1); pop(); push("aSb");  }
        else if (token=='c' && stack.items[stack.top]=='S') { printStack(i++, 2, P2); pop(); push("c"); }
        else if (token=='a' && stack.items[stack.top]=='a') { printStack(i++, 3, NONE); pop(); token = fgetc(fp); }
        else if (token=='b' && stack.items[stack.top]=='b') { printStack(i++, 4, NONE); pop(); token = fgetc(fp); }
        else if (token=='c' && stack.items[stack.top]=='c') { printStack(i++, 5, NONE); pop(); token = fgetc(fp); }
        else    { return 1; }
    }
    printStack(i, -1, NONE);
    if (stack.top != -1)
        return 1;
    return 0;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    printf(" i   d   p         Stack\n"
           "=== === ===    =============\n");

    if (!parser(fp)) {
        printf("Palavra reconhecida pelo automato.");
    }
    else
        printf("Palavra nao reconhecida.");

    return 0;
}