#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int values[MAX_SIZE];
    int top;
} Stack;

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

void generate_pcode(int expression[]) {
    Stack operators, values;
    int x, y, op;
    for(int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '+' || expression[i] == '-') {
            push(expression[i], &operators);

        } else if(expression[i] == '*' || expression[i] == '/') {
            if(expression[i+1] == '(') {
                push(expression[i], &operators);
            } else {
                push(expression[i+1], &values);
                y = pop(&values);
                x = pop(&values);
                if(expression[i] == '*') {
                    printf("OPR 0 4\n");
                    push(x*y, &values);
                } else {
                    printf("OPR 0 5\n");
                    push(x/y, &values);
                }
            }
        } else if(expression[i] == ')') {
            while(operators[operators.top] == '*' || operators[operators.top] == '/') {
                op = pop(&operators);
                y = pop(&values);
                x = pop(&values);
                if(op == '*') {
                    printf("OPR 0 4\n");
                    push(x+y, &values);
                } else4 {
                    printf("OPR 0 5\n");
                    push(x/y, &values);

            }
                
        
        } else if(expression[i] != '('){
            printf("LIT 0 %d", expression[i]);
            push(expression[i], &values);
        }
    }
}



int main() {
    

    
    
}
