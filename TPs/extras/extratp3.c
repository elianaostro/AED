#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100
#define NUM_HASH 5

struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
    unsigned char *bits;
    unsigned int size_filtro;
    unsigned int hash_count;
    size_t size_elem;
};

unsigned int custom_hash(const unsigned char *data, size_t length, unsigned int n) {
    unsigned int hash = 5381 + n;
    for (size_t i = 0; i < length; ++i) {
        hash = ((hash << 5) + hash) + data[i]; 
    }
    return hash;
}

bool compare_example(void* a, void* b) {
    return a == b;
}

list_t* list_new(){
    list_t* list = malloc(sizeof(list_t));
    if (!list)  return NULL;
    
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;

    list -> bits = malloc(SIZE * sizeof(unsigned char));
    if (!list -> bits) {
        free(list);
        return NULL;
    }
    list -> size_filtro = SIZE;
    list -> hash_count = NUM_HASH;
    list -> size_elem = sizeof(int);

    return list;
}

node_t* node_new(void *value, node_t* prev, node_t* next){
    node_t *nodo = malloc (sizeof(node_t));
    if (!nodo) return NULL;

    nodo -> value = value;
    nodo -> prev = prev;
    nodo -> next = next;
    return nodo;
}

size_t list_length(const list_t *list){
    return list -> size;
}

bool list_is_empty(const list_t *list){
    return list_length(list) == 0;
}

bool list_contains(const list_t *list, void *data){
    for (unsigned int i = 0; i < list -> hash_count; i++) {
        unsigned int h = custom_hash(data, list -> size_elem, i) % list -> size_filtro;
        if (!list -> bits[h]) 
            return false;
    }
    node_t *current = list -> head;
    while (current != NULL) {
        if (compare_example(current -> value, data))
            return true;
        current = current -> next;
    }
    return false;
}

void list_add(list_t *list, void *data){
    for (unsigned int i = 0; i < list -> hash_count; i++) {
        unsigned int h = custom_hash(data, list -> size_elem, i) % list -> size_filtro;
        list -> bits[h]++;
    }
}

void list_remove(list_t *list, void *data){
    if (!list_contains(list, data)) return;
    for (unsigned int i = 0; i < list -> hash_count; i++) {
        unsigned int h = custom_hash(data, list -> size_elem, i) % list -> size_filtro;
        list -> bits[h]--;
    }
}

bool list_insert_head(list_t *list, void *value){
    if (!value) return false;
    if (list_contains(list, value)) return false;

    node_t *nodo = node_new(value, NULL, list -> head);
    if (!nodo) return false;


    if (list_is_empty(list)) list -> tail = nodo;
    else list -> head -> prev = nodo;

    list -> head = nodo;
    list -> size ++;
    list_add(list, value);
    return true;
}

bool list_insert_tail(list_t *list, void *value){
    if (!value) return false;
    if (list_contains(list, value)) return false;

    node_t *nodo = node_new(value, list -> tail, NULL);
    if (!nodo) return false;

    if (list_is_empty(list)) list -> head = nodo;
    else list -> tail -> next = nodo;
    
    list -> tail = nodo;
    list -> size ++;
    list_add(list, value);
    return true;
}

void* list_peek_head(const list_t *list){
    if (list_is_empty(list)) return NULL;
    return list -> head -> value;
}

void* list_peek_tail(const list_t *list){
    if (list_is_empty(list)) return NULL;
    return list -> tail -> value;
}

void* list_pop_head(list_t* list){
    if (list_is_empty(list)) return NULL;

    node_t* new_head = list -> head -> next;
    void* head_value = list_peek_head(list);
    
    if (new_head) new_head -> prev = NULL; 
    else list -> tail = NULL;

    free(list -> head); 
    list -> head = new_head;
    list -> size --;
    list_remove(list, head_value);
    return head_value;
}

void* list_pop_tail(list_t* list){
    if (list_is_empty(list)) return NULL;

    node_t* new_tail = list -> tail -> prev;
    void* tail_value = list_peek_tail(list);
    
    if (new_tail) new_tail -> next = NULL; 
    else list -> head = NULL;

    free(list -> tail); 
    list -> tail = new_tail;
    list -> size --;
    list_remove(list, tail_value);
    return tail_value;
}

void list_destroy(list_t *list, void destroy_value(void *)){
    while(!list_is_empty(list)){
        void* valor = list_pop_head(list);
        if (destroy_value)  destroy_value(valor);
    }
    free(list -> bits);
    free(list);
}
