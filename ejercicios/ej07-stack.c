#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack; 

bool isEmpty(Stack *stack){
    return stack->size == 0
}

int top(Stack *stack){
    if(isEmpty(stack)) return NULL;
    return (stack ->top) -> data
}

void push(Stack *stack, int value){
    Node* new_nodo = mallok(sizeof(Node));
    if(!new_nodo) return;
    new_nodo -> value = value;

    if(!isEmpty(stack)){
        Node* previous = stack->top;
        new_nodo -> next = previous;
    }

    stack->top = new_nodo;
    stack->size += 1;
}

int pop(Stack *stack){
    int data = top(stack);
    if(!data) return null;

    nodo* next = (stack->top)->next;
    free(stack->top);
    stack->top = next;
    stack->size -=1;
    return data;
}