#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

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
};

struct list_iter {
    list_t* list;
    node_t* curr;
};

list_t* list_new(){
    list_t* list = malloc(sizeof(list_t));
    if (!list)  return NULL;
    
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    return list;
}

size_t list_length(const list_t* list){
    return list -> size;
}

bool list_is_empty(const list_t* list){
    return list_length(list) == 0;
}

bool list_insert_head(list_t* list, void* value){
    node_t* nodo = malloc(sizeof(node_t));
    if (!nodo) return false;
    
    nodo->value = value;
    nodo->prev = NULL;
    nodo->next = list -> head;
    
    if (list_is_empty(list)) list -> tail = nodo;  //if list->size == 1, then list -> head = list -> tail
    else list -> head -> prev = nodo;
    
    list -> head = nodo;
    list -> size ++;
    return true;
}

bool list_insert_tail(list_t* list, void* value){
    node_t* nodo = malloc(sizeof(node_t));
    if (!nodo) return false;
    
    nodo->value = value;
    nodo->next = NULL;
    nodo->prev = list -> tail;

    if (list_is_empty(list)) list -> head = nodo;
    else list -> tail -> next = nodo;
    
    list -> tail = nodo;
    list -> size ++;
    return true;
}

void* list_peek_head(const list_t* list){
    if (list_is_empty(list)) return NULL;
    return list -> head -> value;
}

void* list_peek_tail(const list_t* list){
    if (list_is_empty(list)) return NULL;
    return list -> tail -> value;
}

// void* list_pop_head(list_t* list){
//     if (list_is_empty(list)) return NULL;

//     node_t* head = list -> head;
//     void* head_value = list_peek_head(list);
    
//     list -> head = head -> next;
//     if (list_length(list)>1) list -> head -> prev = NULL; 
//     else list -> tail = NULL; 

//     free(head);
//     list -> size --;
//     return head_value;
// }

// void* list_pop_tail(list_t* list){
//     if (list_is_empty(list)) return NULL;

//     node_t* tail = list -> tail;
//     void* tail_value = list_peek_tail(list);
    
//     list -> tail = tail -> prev;
//     if (list_length(list)>1) list -> tail -> next = NULL;
//     else list -> head = NULL;

//     free(tail);
//     list -> size --;
//     return tail_value;
// }

void* list_pop_head(list_t* list){
    if (list_is_empty(list)) return NULL;

    node_t* new_head = list -> head -> next;
    void* head_value = list_peek_head(list);
    
    if (new_head) new_head -> prev = NULL; 
    else list -> tail = NULL;

    free(list -> head); 
    list -> head = new_head;
    list -> size --;
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
    return tail_value;
}



void list_destroy(list_t* list, void destroy_value(void*)){
    while(!list_is_empty(list)){
        void* valor = list_pop_head(list);
        if (destroy_value)  destroy_value(valor);
    }
    free(list);
}

list_iter_t* list_iter_create_head(list_t* list){
    list_iter_t* list_iter = malloc(sizeof(list_iter_t));
    if (!list_iter)  return NULL;
    
    list_iter -> list = list;
    list_iter -> curr = list -> head;
    return list_iter;
}

list_iter_t* list_iter_create_tail(list_t* list){
    list_iter_t* list_iter = malloc(sizeof(list_iter_t));
    if (!list_iter)  return NULL;
    
    list_iter -> list = list;
    list_iter -> curr = list -> tail;
    return list_iter;
}

bool list_iter_forward(list_iter_t* iter){
    if (list_is_empty(iter -> list) || list_iter_at_last(iter)) return false;
    iter -> curr = iter -> curr -> next;
    return true;
}

bool list_iter_backward(list_iter_t* iter){
    if (list_is_empty(iter -> list) || list_iter_at_first(iter)) return false;
    iter -> curr = iter -> curr -> prev;
    return true;
}

void* list_iter_peek_current(const list_iter_t* iter){
    if (list_is_empty(iter -> list)) return NULL;
    return iter -> curr -> value;
}

bool list_iter_at_last(const list_iter_t* iter){    
    return iter -> curr ==  iter -> list -> tail;
}

bool list_iter_at_first(const list_iter_t* iter){
    return iter -> curr ==  iter -> list -> head;
}

void list_iter_destroy(list_iter_t* iter){
    free(iter);
}

bool list_iter_insert_after(list_iter_t* iter, void* value){
    if (list_iter_at_last(iter)) return list_insert_tail(iter -> list, value);
    
    node_t* nodo = malloc (sizeof(node_t));
    if (!nodo) return false;
    
    nodo -> value = value;
    nodo -> prev = iter -> curr;
    nodo -> next = iter -> curr -> next;
    
    iter -> curr -> next -> prev = nodo;
    iter -> curr -> next = nodo;
    iter -> list -> size ++;
    return true;
}

bool list_iter_insert_before(list_iter_t* iter, void* value){
    if (list_iter_at_first(iter)) return list_insert_head(iter -> list, value);

    node_t* nodo = malloc (sizeof(node_t));
    if (!nodo) return false;
    
    nodo -> value = value;
    nodo -> prev = iter -> curr -> prev;
    nodo -> next = iter -> curr;
    
    iter -> curr-> prev -> next = nodo;
    iter -> curr-> prev = nodo;
    iter -> list -> size ++;
    return true;
}

// bool list_iter_insert_after(list_iter_t *iter, void *value){
//     if (list_iter_at_last(iter)) return list_insert_tail(iter->list,value);
//     node_t *nodo = malloc (sizeof(node_t));
//     if (!nodo) return false;
//     nodo->value = value;
//     nodo->prev = iter->curr;
//     nodo->next = iter->curr->next;
//     iter->curr->next->prev = nodo;
//     iter->curr->next = nodo;
//     iter->list->size ++;
//     return true;
// }

// bool list_iter_insert_before(list_iter_t *iter, void *value){
//     if (list_iter_at_first(iter)) return list_insert_head(iter -> list, value);
//     node_t *nodo = malloc (sizeof(node_t));
//     if (!nodo) return false;
//     nodo->value = value;
//     nodo->next = iter->curr;
//     nodo->prev = iter->curr->prev;
//     iter->curr->prev->next = nodo;
//     iter->curr->prev = nodo;
//     iter->list->size++;
//     return true;
// }

void* list_iter_delete(list_iter_t* iter){
    if(list_is_empty(iter -> list)) return NULL;

    if (list_iter_at_last(iter)) {
        iter -> curr = iter -> list -> tail;
        return list_pop_tail(iter -> list);
    }
    
    if (list_iter_at_first(iter)) {
        void* value = list_pop_head(iter -> list);
        iter -> curr = iter -> list -> head;
        return value;
    }
    
    node_t* curr = iter -> curr;
    void* value = curr -> value;
    iter -> curr = curr -> next;
    curr -> prev -> next = curr -> next;
    curr -> next -> prev = curr -> prev;
    free(curr);
    iter -> list -> size --;
    return value;
}