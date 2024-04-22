/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/

#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
/* Declaracoes globais */
int charClass;
char lexeme[MAX_WORD_LENGTH];
char nextChar;
int lexLen;
int nextToken;
char word[MAX_WORD_LENGTH];
int c = 0;
int valid = 1;
int procedure[MAX_WORD_LENGTH];
int procedureCount;
int cont = 0;

FILE *in_fp, *fopen();

/* Funcoes de Declaracoes */
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void term();
void factor();

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

void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
int lookup(char);
void expr(void);
void term(void);
void factor(void);
void printProcedures(void);

/* Funcao principal */
int main() {
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR - cannot open input.txt \n");
    } else {
        while(!feof(in_fp)) {
            c = 0;
            fgets(word, MAX_WORD_LENGTH, in_fp);
            for(int i = 0; word[i] != '\0'; i++) {
                if (word[i] == '\r' || word[i] == '\n') {
                    word[i] = '\0';
                }
            }
            printf("Expressao: %s\n", word);

            getChar();
            do {
                procedureCount = -1;
                lex();
                expr();
                printProcedures();
                if(valid) {
                    printf("Expressao aceita.");
                }
            } while (nextToken != EOF);
            printf("\n\n");
        }
    }

    fclose(in_fp);
    return 0;
}

/* Funcao para adicionar proximo caractere ao lexema */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
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
            nextToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }
    // printf("\nProximo token: %d, Proximo lexema: %s", nextToken, lexeme);
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
    procedure[++procedureCount] = 0;
    int temp = procedureCount;
    term();
    if (nextToken == ADD_OP) {
        procedure[temp] = 1;
    } else if (nextToken == SUB_OP) {
        procedure[temp] = 2;
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
    procedure[++procedureCount] = 3;
    int temp = procedureCount;
    factor();
    if (nextToken == MULT_OP) {
        procedure[temp] = 4;
    } else if (nextToken == DIV_OP) {
        procedure[temp] = 5;
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
        procedure[++procedureCount] = (nextToken == IDENT ? 6 : 7);
        lex();
    } else {
        if (nextToken == LEFT_PAREN) {
            procedure[++procedureCount] = 8;
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

void printProcedures() {
    for(int i = 0; i <= procedureCount; i++) {
        switch(procedure[i]) {
            case 0:
                printf("<EXPR> -> <TERM>\n");
                break;
            case 1:
                printf("<EXPR> -> <TERM> + <TERM>\n");
                break;
            case 2:
                printf("<EXPR> -> <TERM> - <TERM>\n");
                break;
            case 3:
                printf("<TERM> -> <FACTOR>\n");
                break;
            case 4:
                printf("<TERM> -> <FACTOR> * <FACTOR>\n");
                break;
            case 5:
                printf("<TERM> -> <FACTOR> / <FACTOR>\n");
                break;
            case 6:
                printf("<FACTOR> -> id\n");
                break;
            case 7:
                printf("<FACTOR> -> int_constant\n");
                break;
            case 8:
                printf("<FACTOR> -> ( <EXPR> )\n");
                break;
        }
    }
}