/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_CHAR 1000
#define N_ARY 5

// Estrutura para representar a pilha
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Variaveis globais
Stack st, productions;
int nTree[MAX_SIZE], binTree[MAX_SIZE];

/* FUNCOES PARA MANIPULAR PILHA */
// Funcao para inicializar stack
void initStack(int value, Stack* stack) {
    stack->top = 0;
    stack->items[stack->top] = value;
}

// Funcao para resetar stack
void resetStack(Stack* stack) {
    stack->items[0] = '\0';
    stack->top = -1;
}

void printStack(Stack* stack) {
    printf("Stack: ");
    for(int i = stack->top; i >= 0; i--) {
        printf("%d /", stack->items[i]);
    }
    printf("\n");
}

// Push
void push(int value, Stack* stack) {
    if (stack->top < MAX_SIZE - 1) {
        stack->items[++stack->top] = value;
    }
    else {
        printf("Stack Overflow\n");
    }
}

// Pop
int pop(Stack* stack) {
    if (stack->top >= 0) {
        int value = stack->items[stack->top];
        stack->items[stack->top--] = '\0';
        return value;
    }
    else {
        printf("Stack Underflow\n");
        return -1;
    }
}

// Funcao para produzir uma arvore a partir de uma lista de producoes
void nAryTree() {
    int n;
    for(int i = 0; i <= productions.top; i++) {
        switch(productions.items[i]) {
            case 0:
                nTree[0] = 'E';
                initStack(0, &st);
                break;
            case 1:
                n = pop(&st);
                nTree[N_ARY*n+1] = '(';
                nTree[N_ARY*n+2] = 'E';
                nTree[N_ARY*n+3] = 'X';
                nTree[N_ARY*n+4] = 'E';
                nTree[N_ARY*n+5] = ')';
                push(N_ARY*n+4, &st);
                push(N_ARY*n+3, &st);
                push(N_ARY*n+2, &st);
                break;
            case 2:
                n = pop(&st);
                nTree[N_ARY*n+1] = '0';
                break;
            case 3:
                n = pop(&st);
                nTree[N_ARY*n+1] = '1';
                break;
            case 4:
                n = pop(&st);
                nTree[N_ARY*n+1] = 'a';
                break;
            case 5:
                n = pop(&st);
                nTree[N_ARY*n+1] = 'b';
                break;
            case 6:
                n = pop(&st);
                nTree[N_ARY*n+1] = 'c';
                break;
            case 7:
                n = pop(&st);
                nTree[N_ARY*n+1] = '+';
                break;
            case 8:
                n = pop(&st);
                nTree[N_ARY*n+1] = '-';
                break;
            case 9:
                n = pop(&st);
                nTree[N_ARY*n+1] = '*';
                break;
            case 10:
                n = pop(&st);
                nTree[N_ARY*n+1] = '/';
                break;
        }
    }
}

void printTree(int* tree) {
    for(int i = 0; i < MAX_SIZE; i++) {
        if(tree[i] != 0) {
            printf("|%3d", i);
        }
    }
    printf("|\n");
    for(int i = 0; i < MAX_SIZE; i++) {
        if(tree[i] != 0) {
            printf("| %c ", tree[i]);
        }
    }
    printf("|\n");
}

void nToBin() {
    // Reestruturando arvore
    for(int i = 0; i < MAX_SIZE; i++) {
        if(nTree[i] == '(' || nTree[i] == ')') {
            nTree[i] = 0;
        }
        else if(nTree[i] == '0' || nTree[i] == '1' || nTree[i] == 'a' || nTree[i] == 'b' || nTree[i] == 'c') {
            int father = (i - 1)/5;
            nTree[father] = nTree[i];
            nTree[i] = 0;
        }
        else if(nTree[i] == '+' || nTree[i] == '-' || nTree[i] == '*' || nTree[i] == '/') {
            int father = (i-1)/N_ARY;
            int grandfather = (father-3)/N_ARY;
            nTree[grandfather] = nTree[i];
            nTree[father] = 0;
            nTree[i] = 0;
        }
    }
}

int parser(FILE *fp) {
    int index = 0;
    char word[MAX_CHAR];
    fgets(word, MAX_CHAR, fp);
    
    initStack('E', &st);
    initStack(0, &productions);
    
    while (word[index] != '\r' && word[index] != '\n' && word[index] != '\0') {
        // Producoes
        if      (word[index]=='(' && st.items[st.top]=='E') { pop(&st); push(')', &st); push('E', &st); push('X', &st); push('E', &st); push('(', &st); push(1, &productions); }
        else if (word[index]=='0' && st.items[st.top]=='E') { pop(&st); push('0', &st); push(2, &productions); }
        else if (word[index]=='1' && st.items[st.top]=='E') { pop(&st); push('1', &st); push(3, &productions); }
        else if (word[index]=='a' && st.items[st.top]=='E') { pop(&st); push('a', &st); push(4, &productions); }
        else if (word[index]=='b' && st.items[st.top]=='E') { pop(&st); push('b', &st); push(5, &productions); }
        else if (word[index]=='c' && st.items[st.top]=='E') { pop(&st); push('c', &st); push(6, &productions); }
        else if (word[index]=='+' && st.items[st.top]=='X') { pop(&st); push('+', &st); push(7, &productions); }
        else if (word[index]=='-' && st.items[st.top]=='X') { pop(&st); push('-', &st); push(8, &productions); }
        else if (word[index]=='*' && st.items[st.top]=='X') { pop(&st); push('*', &st); push(9, &productions); }
        else if (word[index]=='/' && st.items[st.top]=='X') { pop(&st); push('/', &st); push(10, &productions); }
        // Leituras
        else if (word[index]=='a' && st.items[st.top]=='a') { pop(&st); index++; }
        else if (word[index]=='b' && st.items[st.top]=='b') { pop(&st); index++; }
        else if (word[index]=='c' && st.items[st.top]=='c') { pop(&st); index++; }
        else if (word[index]=='0' && st.items[st.top]=='0') { pop(&st); index++; }
        else if (word[index]=='1' && st.items[st.top]=='1') { pop(&st); index++; }
        else if (word[index]=='(' && st.items[st.top]=='(') { pop(&st); index++; }
        else if (word[index]==')' && st.items[st.top]==')') { pop(&st); index++; }
        else if (word[index]=='+' && st.items[st.top]=='+') { pop(&st); index++; }
        else if (word[index]=='-' && st.items[st.top]=='-') { pop(&st); index++; }
        else if (word[index]=='*' && st.items[st.top]=='*') { pop(&st); index++; }
        else if (word[index]=='/' && st.items[st.top]=='/') { pop(&st); index++; }
        // Excecao
        else    { printf("Caracter invalido. ASCII CODE: %d\n", word[index]); return 0; }
    }

    if (st.top != -1) {
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
        printf(parser(fp) ? "Palavra reconhecida.\n\n" : "Palavra NAO reconhecida.\n\n");
        nAryTree();
        printTree(nTree);
        nToBin();
        printTree(nTree);
    }



    fclose(fp);
    return 0;
}