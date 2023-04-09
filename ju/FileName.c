#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int top;
    int data[MAX_STACK_SIZE];
} Stack;

void initialize(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        printf("Error: stack full\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    if (s->top < 0) {
        printf("Error: stack empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int peek(Stack* s) {
    if (s->top < 0) {
        return -1;
    }
    return s->data[s->top];
}

int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void infix_to_postfix(char* infix, char* postfix) {
    Stack s;
    int i, j;
    char token, op;

    initialize(&s);
    j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];

        if (isdigit(token)) {
            postfix[j++] = token;
        }
        else if (token == '(') {
            push(&s, '(');
        }
        else if (token == ')') {
            while (peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);
        }
        else {
            while (precedence(token) <= precedence(peek(&s))) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    while (peek(&s) != -1) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int evaluate_postfix(char* postfix) {
    Stack s;
    int i, operand1, operand2, result;
    char token;

    initialize(&s);

    for (i = 0; postfix[i] != '\0'; i++) {
        token = postfix[i];

        if (isdigit(token)) {
            push(&s, token - '0');
        }
        else {
            operand2 = pop(&s);
            operand1 = pop(&s);

            switch (token) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                printf("Error: invalid operator\n");
                exit(EXIT_FAILURE);
            }

            push(&s, result);
        }
    }

    return pop(&s);
}


int main() {
    char infix[100], postfix[100];
    int result;

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
