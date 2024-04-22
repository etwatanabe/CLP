#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
/* Declara��es globais */
int charClass;
char lexeme[MAX_WORD_LENGTH];
char nextChar;
int lexLen;
int nextToken;
char word[MAX_WORD_LENGTH];
int c = 0;
FILE *in_fp, *fopen();

/* Fun��es de Declara��es */
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

/* C�digos de tokens */
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

/* Fun��o principal */
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
            printf("Expressao: %s", word);

            getChar();
            do {
                lex();
                expr();
            } while (nextToken != EOF);
            printf("\n\n");
        }
    }

    fclose(in_fp);
    return 0;
}

void clearWordBuffer() {
    c = 0;
    word[0] = '\0';
}

/* Fun��o para adicionar pr�ximo caractere ao lexema */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Erro - lexema � muito longo \n");
    }
}

/* Fun��o para obter o pr�ximo caractere da entrada e determinar sua classe de caracteres */
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

/* Fun��o para chamar getChar at� que ela retorne um caractere diferente de espa�o em branco */
void getNonBlank() {
    while (isspace(nextChar) && nextChar != '\r' && nextChar != '\n') {
        getChar();
    }
}

/* Analisador l�xico simples para express�es aritm�ticas */
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
    printf("\nProximo token: %d, Proximo lexema: %s", nextToken, lexeme);
    return nextToken;
}

/* Fun��o para processar operadores e par�nteses e retornar o token */
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
    printf("\n<EXPR> -> <TERM> {(+|-) <TERM>}");
    term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
    //printf("Saindo de <expr>\n");
}

/* Analisa sintaticamente cadeias na linguagem gerada pela regra: <term> -> <factor> {(* | /) <factor>} */
void term() {
    // printf("Entrando em <term>\n");
    printf("\n<TERM> -> <FACTOR> {(*|/) <FACTOR>}");
    factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        lex();
        factor();
    }
    // printf("Saindo de <term>\n");
}

/* Analisa sintaticamente cadeias na linguagem gerada pela regra: <factor> -> id | int_constant | (<expr>) */
void factor() {
    // printf("Entrando em <factor>\n");
    printf("\n<FACTOR> -> id | int_constant | (<EXPR>)");
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex();
    } else {
        if (nextToken == LEFT_PAREN) {
            lex();
            expr();
            if (nextToken == RIGHT_PAREN) {
                lex();
            } else {
                printf("\nErro sintatico: esperado ')'");
            }
        } else {
            printf("\nErro sintatico: esperado identificador, constante inteira ou '('");
        }
    }
    // printf("Saindo de <factor>\n");
}