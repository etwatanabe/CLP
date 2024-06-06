/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_SIZE 100
#define MAX_TREE 1000
#define N_ARY 3

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

/* Declaracoes globais */
int charClass;
char lexeme[MAX_SIZE][MAX_WORD_LENGTH];
char nextChar;
int lexLen;
int lexCount = -1;
int nextToken;
char word[MAX_WORD_LENGTH];
int c = 0;
int valid = 1;
int cont = 0;


Stack productions = {{}, -1};
FILE *in_fp;

/* Classes de caracteres */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Codigos de tokens */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* Declaracao das funcoes */
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char);
void expr();
void term();
void factor();
void printProductions();
void initStack(Stack*);
void push(int, Stack*);
int pop(Stack*);
void nAryTree();
void printTree(int*);

/* Funcao para adicionar proximo caractere ao lexema */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexCount][lexLen++] = nextChar;
        lexeme[lexCount][lexLen] = 0;
    } else {
        printf("Erro - lexema muito longo \n");
    }
}

/* Funcao para obter o proximo caractere da entrada e determinar sua classe de caracteres */
void getChar() {
    nextChar = word[c++];
    if (nextChar != '\0') {
        // printf("\nCHAR: %d, %c", nextChar, nextChar);
        if (isalpha(nextChar)) {
            charClass = LETTER;
        } else if (isdigit(nextChar)) {
            charClass = DIGIT;
        } else
            charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/* Funcao para chamar getChar ate que ela retorne um caractere diferente de espaco em branco */
void getNonBlank() {
    while (isspace(nextChar)) {
        getChar();
    }
}

/* Analisador lexico simples para expressoes aritmeticas */
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            lexCount++;
            nextToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            lexCount++;
            nextToken = INT_LIT;
            break;
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        case EOF:
            nextToken = EOF;
            lexeme[lexCount][0] = 'E';
            lexeme[lexCount][1] = 'O';
            lexeme[lexCount][2] = 'F';
            lexeme[lexCount][3] = 0;
            break;
    }
    // printf("\nProximo token: %d, Proximo lexema: %s", nextToken, lexeme[lexCount]);
    return nextToken;
}

/* Funcao para processar operadores e parenteses e retornar o token */
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/* Analisa sintaticamente cadeias na linguagem gerada pela regra: <expr> -> <term> {(+ | -) <term>} */
void expr() {
    // printf("Entrando em <expr>\n");
    productions.items[++productions.top] = 1;
    int temp = productions.top;
    term();
    if (nextToken == ADD_OP) {
        productions.items[temp] = 2;
    } else if (nextToken == SUB_OP) {
        productions.items[temp] = 3;
    }
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
    //printf("Saindo de <expr>\n");
}

/* Analisa sintaticamente cadeias na linguagem gerada pela regra: <term> -> <factor> {(* | /) <factor>} */
void term() {
    // printf("Entrando em <term>\n");
    productions.items[++productions.top] = 4;
    int temp = productions.top;
    factor();
    if (nextToken == MULT_OP) {
        productions.items[temp] = 5;
    } else if (nextToken == DIV_OP) {
        productions.items[temp] = 6;
    }
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        lex();
        factor();
    }
    // printf("Saindo de <term>\n");
}

/* Analisa sintaticamente cadeias na linguagem gerada pela regra: <factor> -> id | int_constant | (<expr>) */
void factor() {
    // printf("Entrando em <factor>\n");
    if (nextToken == IDENT || nextToken == INT_LIT) {
        productions.items[++productions.top] = (nextToken == IDENT ? 7 : 8);
        lex();
    } else {
        if (nextToken == LEFT_PAREN) {
            productions.items[++productions.top] = 9;
            lex();
            expr();
            if (nextToken == RIGHT_PAREN) {
                lex();
            } else {
                printf("Erro sintatico: esperado ')'\n");
                valid = 0;
            }
        } else {
            printf("Erro sintatico: esperado identificador, constante inteira ou '('\n");
            valid = 0;
        }
    }
    // printf("Saindo de <factor>\n");
}

void printProductions() {
    for(int i = 0; i <= productions.top; i++) {
        printf("P%d ", productions.items[i]);
    }
    printf("\n");
}

/* Funções para manipulação da pilha */
void initStack(Stack *s) {
    s->top = -1;
}

void push(int value, Stack *s) {
    if (s->top < MAX_SIZE - 1) {
        s->items[++s->top] = value;
    } else {
        printf("Erro - pilha cheia\n");
    }
}

int pop(Stack *s) {
    if (s->top > -1) {
        return s->items[s->top--];
    } else {
        printf("Erro - pilha vazia\n");
        return -1;
    }
}

/* Função para construir a árvore N-ária */
void nAryTree() {
    int n, nTree[MAX_TREE] = {};
    Stack st;
    initStack(&st);
    nTree[0] = 'E';
    push(0, &st);

    for(int i = 0; i <= productions.top; i++) {
        n = pop(&st);
        switch(productions.items[i]) {
            case 1:
                nTree[N_ARY*n+1] = 'T';
                push(N_ARY*n+1, &st);
                break;
            case 2:
                nTree[N_ARY*n+1] = 'T';
                nTree[N_ARY*n+2] = '+';
                nTree[N_ARY*n+3] = 'T';
                push(N_ARY*n+3, &st);
                push(N_ARY*n+1, &st);
                break;
            case 3:
                nTree[N_ARY*n+1] = 'T';
                nTree[N_ARY*n+2] = '-';
                nTree[N_ARY*n+3] = 'T';
                push(N_ARY*n+3, &st);
                push(N_ARY*n+1, &st);
                break;
            case 4:
                nTree[N_ARY*n+1] = 'F';
                push(N_ARY*n+1, &st);
                break;
            case 5:
                nTree[N_ARY*n+1] = 'F';
                nTree[N_ARY*n+2] = '+';
                nTree[N_ARY*n+3] = 'F';
                push(N_ARY*n+3, &st);
                push(N_ARY*n+1, &st);
                break;
            case 6:
                nTree[N_ARY*n+1] = 'F';
                nTree[N_ARY*n+2] = '-';
                nTree[N_ARY*n+3] = 'F';
                push(N_ARY*n+3, &st);
                push(N_ARY*n+1, &st);
                break;
            case 7:
                nTree[N_ARY*n+1] = 'i';
                break;
            case 8:
                nTree[N_ARY*n+1] = 'i';
                break;
            case 9:
                nTree[N_ARY*n+1] = '(';
                nTree[N_ARY*n+2] = 'E';
                nTree[N_ARY*n+3] = ')';
                push(N_ARY*n+2, &st);
                break;
        }
    }
    printTree(nTree);
}

/* Função para imprimir a árvore */
void printTree(int *tree) {
    int count = 0;
    for(int i = 0; i < MAX_TREE; i++) {

        if(tree[i] != 0) {
            printf("|%5d", i);
        }
    }
    printf("|\n");
    for(int i = 0; i < MAX_TREE; i++) {
        if(tree[i] != 0) {
            if(tree[i] == 'i' && count <= lexCount) {
                printf("|%5s", lexeme[count++]);
            } else {
                printf("|%5c", tree[i]);
            }
        }
    }
    printf("|\n");
}

/* Funcao principal */
int main() {
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR - cannot open input.txt \n");
    } else {
        while(!feof(in_fp)) {
            c = 0;
            valid = 1;
            lexCount = 0;
            fgets(word, MAX_WORD_LENGTH, in_fp);
            for(int i = 0; word[i] != '\0'; i++) {
                if (word[i] == '\r' || word[i] == '\n') {
                    word[i] = '\0';
                }
            }
            printf("Expressao: %s\n", word);

            getChar();
            initStack(&productions);
            do {
                productions.top = -1;
                lex();
                expr();
                printProductions();
                if(valid) {
                    printf("Expressao aceita.\n");
                    printf("Arvore n-aria em vetor:\n");
                    nAryTree();
                }
            } while (nextToken != EOF);
            printf("\n\n");
        }
    }

    fclose(in_fp);
    return 0;
}
