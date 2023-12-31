#include <stdio.h>
#include <ctype.h>

char *p;
char stack[50];
char output[50];
int size = 0;
int top = -1;

int priority(char element);
void pop();
void push(char element);
void print();

int main() {
    char infix[50];
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    p = infix;

    push('('); // Step 1

    while (*p != '\0') {
        if (isalnum(*p)) {
            print();
            output[size++] = *p;
        } else if (*p == '(') {
            push(*p);
        } else if (*p == ')') {
            while (stack[top] != '(') {
                pop();
            }
            pop(); // Remove the left parenthesis
        } else if (priority(*p) > priority(stack[top])) {
            push(*p);
        } else {
            while (priority(*p) <= priority(stack[top]) && stack[top] != '(') {
                pop();
            }
            push(*p);
        }

        p++;
    }

    // Pop remaining elements from the stack
    while (top != -1) {
        pop();
    }

    printf("Postfix expression:\n ");
    print();

    return 0;
}

int priority(char element) {
    if (element == '^')
        return 3;
    else if (element == '*' || element == '/')
        return 2;
    else if (element == '+' || element == '-')
        return 1;
    else if (element == '(' || element == ')')
        return 0;
}

void pop() {
    if (stack[top] != '(') {
        output[size++] = stack[top];
    }
    top--;
}

void push(char element) {
    top++;
    stack[top] = element;
}

void print() {
    printf("Current output: ");
    for (int j = 0; j < size; j++) {
        if (output[j] != '(' && output[j] != ')') {
            printf("%c", output[j]);
        }
    }
    printf("\n");
}

