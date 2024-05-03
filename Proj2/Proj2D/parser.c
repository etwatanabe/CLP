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
#define A 5
#define B 3
#define C 2

// Estrutura para representar a pilha
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Variaveis globais
Stack st, productions;
int nTree[MAX_SIZE], binTree[MAX_SIZE], binTreeSize = 0, npr[MAX_SIZE], nprSize = 0;

/* FUNCOES PARA MANIPULAR PILHA */
// Funcao para inicializar stack
void initStack(int value, Stack* stack) {
    stack->top = 0;
    stack->items[stack->top] = value;
}

// Funcao para resetar stack
void resetStack(Stack* stack) {
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

void printPostOrder(int* tree, int n, int index) {
    if (index >= n)
        return;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    printPostOrder(tree, n, leftChild);
    printPostOrder(tree, n, rightChild);
    printf("%c ", tree[index]);
    npr[nprSize++] = tree[index];
}

void nToBin() {
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
    for(int i = 0; i < MAX_SIZE; i++) {
        if(nTree[i] != 0) {
            binTree[binTreeSize++] = nTree[i];
        }
    }
}

void pcode() {
    int x, y;
    for(int i = 0; i < nprSize; i++) {
        switch(npr[i]) {
            case '0':
                printf("LIT 0 0\n");
                push(0, &st);
                break;
            case '1':
                printf("LIT 0 1\n");
                push(1, &st);
                break;
            case 'a':
                printf("LOD 0 3\n");
                push(A, &st);
                break;
            case 'b':
                printf("LOD 0 4\n");
                push(B, &st);
                break;
            case 'c':
                printf("LOD 0 5\n");
                push(C, &st);
                break;
            case '+':
                printf("OPR 0 2\n");
                y = pop(&st);
                x = pop(&st);
                push(x+y, &st);
                break;
            case '-':
                printf("OPR 0 3\n");
                y = pop(&st);
                x = pop(&st);
                push(x-y, &st);
                break;
            case '*':
                printf("OPR 0 4\n");
                y = pop(&st);
                x = pop(&st);
                push(x*y, &st);
                break;
            case '/':
                printf("OPR 0 5\n");
                y = pop(&st);
                x = pop(&st);
                push(x+y, &st);
                break;
        }
    }
}

int parser(char* word) {
    for(int i = 0; word[i] != '\0'; i++) {
        if(word[i] == '\r' || word[i] == '\n') {
            word[i] = '\0';
            break;
        }
    }
    int index = 0;
    
    initStack('E', &st);
    initStack(0, &productions);
    
    while (word[index] != '\0') {
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

void reset() {
    for(int i = 0; i < MAX_SIZE; i++) {
        nTree[i] = 0;
        binTree[i] = 0;
        npr[i] = 0;
    }
    binTreeSize = 0;
    nprSize = 0;
    resetStack(&st);
    resetStack(&productions);
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    char word[MAX_CHAR];

    while(!feof(fp)) {
        reset();
        printf("\n==============================================================================================================\n\n");
        fgets(word, MAX_CHAR, fp);
        printf(parser(word) ? "Palavra '%s' reconhecida.\n" : "Palavra '%s' NAO reconhecida.\n", word);

        nAryTree();
        printf("\nArvore n-aria codificada:\n");
        printTree(nTree);

        nToBin();
        printf("\nArvore binaria codificada:\n");
        printTree(binTree);

        printf("\nNPR da arvore binaria:\n");
        printPostOrder(binTree, binTreeSize, 0);

        printf("\n\nNPR para p-code:\n");
        pcode();
    }



    fclose(fp);
    return 0;
}