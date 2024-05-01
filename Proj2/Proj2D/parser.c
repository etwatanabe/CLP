/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 200
#define MAX_CHAR 200

// Estrutura para representar a pilha
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;
Stack stack = {{}, -1}, productions = {{}, -1};

// Estrutura para representar a arvore
typedef struct {
    int address[MAX_SIZE];
    char symbol[MAX_SIZE];
    int top;
} Tree;
Tree tree;

/* FUNCOES PARA MANUSEAR A PILHA */
// Funcao para resetar stack
void resetStack() {
    while(stack.top >= 0) {
        stack.items[stack.top--] = '\0';
    }
}

// Funcao para inicializar stack
void initStack() {
    stack.items[++stack.top] = 'E';
}

// Funcao para imprimir as informacoes da pilha
void printStack(int i, int q, int d, int prod, char* word, int dot) {
    printf("%2d  %2d  %2d", i, q, d);

    if (prod > 0) { printf("  P%d    ", prod); }
    else          { printf("  --    "); }

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

// Push
void push(char* value) {
    int i = 0;
    while(value[i] != '\0') i++;
    for (i = i - 1; i >= 0; i--) {
        if (stack.top < MAX_SIZE - 1) {
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
         stack.items[stack.top--] = '\0';
    }
    else {
        printf("Stack Underflow\n");
    }
}

/* FUNCOES PARA MANUSEAR AS PRODUCOES */
// Funcao para resetar as producoes
void resetProductions() {
    while(productions.top >= 0) {
        productions.items[productions.top--] = -1;
    }
}

void printProductions() {
    printf("Productions: ");
    for(int i = 0; i <= productions.top; i++) {
        printf("%d ", productions.items[i]);
    }
    printf("\n");
}
void resetTree() {
    while(tree.top >= 0) {
        tree.address[tree.top] = -1;
        tree.symbol[tree.top--] = '\0';
    }
}

void printTree() {
    printf("Addr: ");
    for(int i = 0; i <= tree.top; i++) {
        printf("| %3d ", tree.address[i]);
    }
    printf("|\n");
    printf("Symb: ");
    for(int i = 0; i <= tree.top; i++) {
        printf("| %3c ", tree.symbol[i]);
    }
    printf("|\n\n");
}

void productionsToTree() {
    tree.address[++tree.top] = 0; tree.symbol[tree.top] = 'E';
    for(int i = 0; i <= productions.top; i++) {
        switch(productions.items[i]) {
            case 1:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '(';
                tree.address[++tree.top] = 5*i+2; tree.symbol[tree.top] = 'E';
                tree.address[++tree.top] = 5*i+3; tree.symbol[tree.top] = 'X';
                tree.address[++tree.top] = 5*i+4; tree.symbol[tree.top] = 'E';
                tree.address[++tree.top] = 5*i+5; tree.symbol[tree.top] = ')';
                break;
            case 2:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '0'; break;
            case 3:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '1'; break;
            case 4:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = 'a'; break;
            case 5:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = 'b'; break;
            case 6:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = 'c'; break;
            case 7:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '+'; break;
            case 8:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '-'; break;
            case 9:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '*'; break;
            case 10:
                tree.address[++tree.top] = 5*i+1; tree.symbol[tree.top] = '/'; break;
        }
    }
    printf("\n");
}

// Funcao para simular o automato de pilha
int parser(FILE *fp) {
    int i = 0, dot = 0, index = 0;
    char word[MAX_CHAR];
    fgets(word, MAX_CHAR, fp);
    
    printf(" i   q   d   p           w                   Stack\n"
            "=== === === ===   ===================   ===================\n");

    printStack(i++, 0, 0, 0, word, dot);
    initStack();
    
    while (word[index] != '\r' && word[index] != '\n' && word[index] != '\0') {
        // Producoes
        if      (word[index]=='(' && stack.items[stack.top]=='E') { printStack(i++, 1,  1,  1, word, dot); pop(); push("(EXE)"); productions.items[++productions.top] = 1; }
        else if (word[index]=='0' && stack.items[stack.top]=='E') { printStack(i++, 1,  2,  2, word, dot); pop(); push("0"); productions.items[++productions.top] = 2; }
        else if (word[index]=='1' && stack.items[stack.top]=='E') { printStack(i++, 1,  3,  3, word, dot); pop(); push("1"); productions.items[++productions.top] = 3; }
        else if (word[index]=='a' && stack.items[stack.top]=='E') { printStack(i++, 1,  4,  4, word, dot); pop(); push("a"); productions.items[++productions.top] = 4; }
        else if (word[index]=='b' && stack.items[stack.top]=='E') { printStack(i++, 1,  5,  5, word, dot); pop(); push("b"); productions.items[++productions.top] = 5; }
        else if (word[index]=='c' && stack.items[stack.top]=='E') { printStack(i++, 1,  6,  6, word, dot); pop(); push("c"); productions.items[++productions.top] = 6; }
        else if (word[index]=='+' && stack.items[stack.top]=='X') { printStack(i++, 1,  7,  7, word, dot); pop(); push("+"); productions.items[++productions.top] = 7; }
        else if (word[index]=='-' && stack.items[stack.top]=='X') { printStack(i++, 1,  8,  8, word, dot); pop(); push("-"); productions.items[++productions.top] = 8; }
        else if (word[index]=='*' && stack.items[stack.top]=='X') { printStack(i++, 1,  9,  9, word, dot); pop(); push("*"); productions.items[++productions.top] = 9; }
        else if (word[index]=='/' && stack.items[stack.top]=='X') { printStack(i++, 1, 10, 10, word, dot); pop(); push("/"); productions.items[++productions.top] = 10; }
        // Leituras++
        else if (word[index]=='a' && stack.items[stack.top]=='a') { printStack(i++, 1, 11, 0, word, dot++); pop(); index++; }
        else if (word[index]=='b' && stack.items[stack.top]=='b') { printStack(i++, 1, 12, 0, word, dot++); pop(); index++; }
        else if (word[index]=='c' && stack.items[stack.top]=='c') { printStack(i++, 1, 13, 0, word, dot++); pop(); index++; }
        else if (word[index]=='0' && stack.items[stack.top]=='0') { printStack(i++, 1, 14, 0, word, dot++); pop(); index++; }
        else if (word[index]=='1' && stack.items[stack.top]=='1') { printStack(i++, 1, 15, 0, word, dot++); pop(); index++; }
        else if (word[index]=='(' && stack.items[stack.top]=='(') { printStack(i++, 1, 16, 0, word, dot++); pop(); index++; }
        else if (word[index]==')' && stack.items[stack.top]==')') { printStack(i++, 1, 17, 0, word, dot++); pop(); index++; }
        else if (word[index]=='+' && stack.items[stack.top]=='+') { printStack(i++, 1, 18, 0, word, dot++); pop(); index++; }
        else if (word[index]=='-' && stack.items[stack.top]=='-') { printStack(i++, 1, 19, 0, word, dot++); pop(); index++; }
        else if (word[index]=='*' && stack.items[stack.top]=='*') { printStack(i++, 1, 20, 0, word, dot++); pop(); index++; }
        else if (word[index]=='/' && stack.items[stack.top]=='/') { printStack(i++, 1, 21, 0, word, dot++); pop(); index++; }
        // Excecao
        else    { printStack(i, 0, -1, 0, word, dot); printf("Caracter invalido. ASCII CODE: %d\n", word[index]); return 0; }
    }
    printStack(i, 0, -1, 0, word, dot);
    if (stack.top != -1) {
        return 0;
    }
    return 1;
}

void reset() {
    resetStack();
    resetProductions();
    resetTree();
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    while(!feof(fp)) {
        reset();

        printf(parser(fp) ? "Palavra reconhecida.\n\n" : "Palavra NAO reconhecida.\n\n");

        printProductions();
        productionsToTree();
        printTree();
    }

    fclose(fp);
    return 0;
}