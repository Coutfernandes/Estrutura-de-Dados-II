#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

int is_operator(char* token) {
    if (token == NULL || strlen(token) != 1) {
        return 0;
    }
    char op = token[0];
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para a pilha.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o no.\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(Stack* stack) {
    if (stack == NULL || stack->top == NULL) {
        fprintf(stderr, "Erro: Expressao malformada (operandos insuficientes para um operador).\n");
        exit(EXIT_FAILURE); 
    }
    
    Node* temp = stack->top;
    double poppedValue = temp->value;
    stack->top = temp->next;
    free(temp);
    
    return poppedValue;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void freeStack(Stack* stack) {
    Node* current = stack->top;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

double evaluateRPN(char* expression) {
    Stack* stack = createStack();
    char* token;
    
    char* expr_copy = strdup(expression);
    if (expr_copy == NULL) {
        fprintf(stderr, "Erro ao duplicar a string de expressao.\n");
        freeStack(stack);
        exit(EXIT_FAILURE);
    }

    token = strtok(expr_copy, " ");
    
    while (token != NULL) {
        
        if (is_operator(token)) {
            
            double val2 = pop(stack); 
            double val1 = pop(stack);
            double result;
            
            char op = token[0];

            switch (op) {
                case '+':
                    result = val1 + val2;
                    break;
                case '-':
                    result = val1 - val2;
                    break;
                case '*':
                    result = val1 * val2;
                    break;
                case '/':
                    if (val2 == 0.0) {
                        fprintf(stderr, "Erro: Tentativa de divisao por zero.\n");
                        free(expr_copy);
                        freeStack(stack);
                        exit(EXIT_FAILURE);
                    }
                    result = val1 / val2;
                    break;
            }
            
            push(stack, result);
            
        } else {
            push(stack, atof(token));
        }
        
        token = strtok(NULL, " ");
    }

    if (isEmpty(stack)) {
        fprintf(stderr, "Erro: Expressao malformada (pilha vazia no final).\n");
        free(expr_copy);
        freeStack(stack);
        exit(EXIT_FAILURE);
    }

    double final_result = pop(stack);
    
    if (!isEmpty(stack)) {
        fprintf(stderr, "Erro: Expressao malformada (operandos demais).\n");
        free(expr_copy);
        freeStack(stack);
        exit(EXIT_FAILURE);
    }
    
    free(expr_copy);
    freeStack(stack);

    return final_result;
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Uso: %s \"expressao_rpn\"\n", argv[0]);
        printf("Exemplo: %s \"10 5 + 2 *\"\n", argv[0]);
        return 1;
    }

    char* expression = argv[1];
    
    double resultado = evaluateRPN(expression);
    
    printf("Resultado: %.2f\n", resultado);
    
    return 0;
}
