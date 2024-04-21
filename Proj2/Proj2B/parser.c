/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_CHAR 100

// Estrutura para representar a pilha
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;
Stack stack = {"", -1};

// Tipos de funcoes P
typedef enum {
    P1, P2, NONE
} fct;

// Funcao para resetar stack
void resetStack() {
    while(stack.top >= 0) {
        stack.items[stack.top--] = ' ';
    }
}

// Funcao para inicializar stack
void initStack() {
    stack.items[++stack.top] = 'S';
}

// Push
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

// Pop
void pop() {
    if (stack.top >= 0) {
         stack.items[stack.top--] = ' ';
    }
    else {
        printf("Stack Underflow\n");
    }
}

// Funcao para imprimir tabela de analise
void printStack(int i, int q, int d, fct p, char* word, int dot) {
    printf("%2d  %2d  %2d", i, q, d);

    if      (p == P1) { printf("  P1  "); } 
    else if (p == P2) { printf("  P2  "); } 
    else              { printf("  -   "); }

    for(int i = 0; word[i] != '\r' && word[i] != '\n' && word[i] != '\0'; i++) {
        if (i == dot) {
            printf(".");
        }
        printf("%c", word[i]);
    }

    printf("\t\t");
    
    for (int j = stack.top; j >= 0; j--) {
        printf("%c", stack.items[j]);
    }
    printf("\n");
}

// Funcao para simular o automato de pilha
int parser(FILE *fp) {
    int i = 0, q = 0, dot = 0, token = 0;
    char word[MAX_CHAR];
    fgets(word, MAX_CHAR, fp);

    resetStack();
    printStack(i++, q++, 0, NONE, word, dot);
    initStack();
    
    while (word[token] != '\r' && word[token] != '\n' && word[token] != '\0') {
        if      (word[token]=='a' && stack.items[stack.top]=='S') { printStack(i++, q, 1, P1, word, dot); pop(); push("aSb"); }
        else if (word[token]=='b' && stack.items[stack.top]=='S') { printStack(i++, q, 1, P1, word, dot); pop(); push("aSb");  }
        else if (word[token]=='c' && stack.items[stack.top]=='S') { printStack(i++, q, 2, P2, word, dot); pop(); push("c"); }
        else if (word[token]=='a' && stack.items[stack.top]=='a') { printStack(i++, q, 3, NONE, word, dot++); pop(); token++; }
        else if (word[token]=='b' && stack.items[stack.top]=='b') { printStack(i++, q, 4, NONE, word, dot++); pop(); token++; }
        else if (word[token]=='c' && stack.items[stack.top]=='c') { printStack(i++, q, 5, NONE, word, dot++); pop(); token++; }
        else                                                      { printStack(i, q, -1, NONE, word, dot); printf("Caracter nao reconhecido. ASCII CODE: %d\n", word[token]); return 0; }
    }
    printStack(i, q, -1, NONE, word, dot);
    if (stack.top != -1) {
        return 0;
    }
    return 1;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    while(!feof(fp)) {
        printf(" i   q   d   p           w                   Stack\n"
               "=== === === === ===================   ===================\n");

        if (parser(fp)) { printf("Palavra reconhecida.\n\n"); }
        else            { printf("Palavra NAO reconhecida.\n\n"); }
    }

    fclose(fp);
    return 0;
}