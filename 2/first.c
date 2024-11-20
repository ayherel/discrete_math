#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Node {
    int value; 
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

// func dlya sozdaniya novogo uzla
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// initial stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// proverka stack
int stackempty(Stack* stack) {
    return stack->top == NULL;
}

// dobavlenie elementa v stack
void push(Stack* stack, int value) {
    Node* newNode = createNode(value);
    newNode->next = stack->top;
    stack->top = newNode;
}

// udalenie elementa iz stack
int pop(Stack* stack) {
    if (stackempty(stack)) {
        printf("stack is empty\n");
        exit(1);
    }
    Node* temp = stack->top;
    int value = temp->value;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

// get verh stack
int peek(Stack* stack) {
    if (stackempty(stack)) {
        printf("stack is empty\n");
        exit(1);
    }
    return stack->top->value;
}

// opredelenie prioritet operatorov
int prioritet(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// reverst str
void reverse(char* stroka) {
    int n = strlen(stroka);
    for (int i = 0; i < n / 2; i++) {
        char temp = stroka[i];
        stroka[i] = stroka[n - i - 1];
        stroka[n - i - 1] = temp;
    }
}

// proverka simvola
int proverkasimvola(char ch) {
    return (ch >= '0' && ch <= '9');
}

// preobrazovanie infiksnogo v prefixnoe
void infixToPrefix(char* infix, char* prefix) {
    Stack* stack = createStack();
    reverse(infix);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (proverkasimvola(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            push(stack, infix[i]);
        } else if (infix[i] == '(') {
            while (!stackempty(stack) && peek(stack) != ')') {
                prefix[j++] = pop(stack);
            }
            pop(stack); // udalyaem ')'
        } else {
            while (!stackempty(stack) && prioritet(peek(stack)) >= prioritet(infix[i])) {
                prefix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }

    while (!stackempty(stack)) {
        prefix[j++] = pop(stack);
    }
    prefix[j] = '\0';
    reverse(prefix);
}

// vichislenie prefixnoi formy
int evaluatePrefix(char* prefix) {
    Stack* stack = createStack();
    int i = 0;

    while (prefix[i] != '\0') i++;

    for (i--; i >= 0; i--) {
        if (proverkasimvola(prefix[i])) {
            push(stack, prefix[i] - '0'); // simvol v chislo
        } else {
            int operand1 = pop(stack);
            int operand2 = pop(stack);
            switch (prefix[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char infix[100];
    char prefix[100];

    printf("vvedite infiksnoe virajenie: ");
    fgets(infix, sizeof(infix), stdin);
    
    // udalenie simvola novoi stroki
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    infixToPrefix(infix, prefix);
    printf("prefiksnoe virajenie: %s\n", prefix);

    int result = evaluatePrefix(prefix);
    printf("rezultat: %d\n", result);
    getch();
    return 0;
}
