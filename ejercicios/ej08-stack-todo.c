#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack;

// Inicializar la pila
void initStack(Stack *stack) {
    stack ->top = NULL;
    stack ->size = 0; 
}

// Verificar si la pila está vacía
int isEmpty(Stack *stack) {
    return stack->size == 0;
}

// Obtener el tamaño de la pila
int len(Stack *stack) {
    return stack->size;
}

// Obtener el elemento en la cima de la pila
int top(Stack *stack) {
    if(isEmpty(stack)) {
        fprintf(stderr, "Error: La pila está vacía.\n");
        exit(EXIT_FAILURE);
    }
    return (stack->top) -> data;
}

// Empujar un elemento a la pila
void push(Stack *stack, int value) {
   Node* new_nodo = malloc(sizeof(Node));
   if(!new_nodo) return;
   new_nodo -> data = value;

   if(!isEmpty(stack)) {
        Node* previous = stack->top;
        new_nodo -> next = previous;
   }

   stack->top = new_nodo;
   stack->size +=1;
}

// Sacar un elemento de la pila
int pop(Stack *stack) {

    int data = top(stack);

    Node* next = (stack->top)->next;
    free(stack->top);
    stack->top = next;

    stack->size -= 1;
    return data;   
}

// Liberar la memoria de la pila
void freeStack(Stack *stack) {
    while (stack->top != NULL) {
        Node *temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    stack->size = 0;
}

int main() {
    Stack myStack;
    initStack(&myStack);

    printf("La pila está vacía? %s\n", isEmpty(&myStack) ? "Sí" : "No");
    printf("Tamaño de la pila: %d\n", len(&myStack));

    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);

    printf("La pila está vacía? %s\n", isEmpty(&myStack) ? "Sí" : "No");
    printf("Tamaño de la pila: %d\n", len(&myStack));
    printf("Elemento en la cima de la pila: %d\n", top(&myStack));

    printf("Elemento desapilado: %d\n", pop(&myStack));

    freeStack(&myStack);

    return 0;
}
