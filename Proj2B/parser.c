#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

void initStack(void);
void push(char*);
void pop();
int parser(FILE*);
void printStack(void);

// Estrutura para representar a pilha
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;
Stack stack = {"", -1};

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

void printStack() {
    for (int i = 0; i <= stack.top; i++) {
        printf(" %c ", stack.items[i]);
    }
    printf("\n");
}

// Função para simular o autômato de pilha
int parser(FILE *fp) {
    char token = fgetc(fp);
    while (token != EOF) {
        printStack();
        if      (token=='a' && stack.items[stack.top]=='S') { pop(); push("aSb"); }
        else if (token=='b' && stack.items[stack.top]=='S') { pop(); push("aSb"); }
        else if (token=='c' && stack.items[stack.top]=='S') { pop(); push("c"); }
        else if (token=='a' && stack.items[stack.top]=='a') { pop(); token = fgetc(fp); }
        else if (token=='b' && stack.items[stack.top]=='b') { pop(); token = fgetc(fp); }
        else if (token=='c' && stack.items[stack.top]=='c') { pop(); token = fgetc(fp); }
        else    { return 1; }
    }
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

    initStack();

    printf("STACK\n00 01 02 03 04 05 06 07 08 09 10 11 12 13\n============================================\n");

    if (!parser(fp)) {
        printf("Palavra reconhecida pelo automato.");
    }
    else
        printf("Palavra nao reconhecida.");

    return 0;
}