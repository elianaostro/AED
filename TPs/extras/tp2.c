#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define size 1000
#define num_hash 5

bool compare_strings(const char *a, const char *b) {
    return strcmp(a, b);
}

typedef struct node node_t;
typedef struct {
    unsigned int num_hash;
    unsigned int size;
    unsigned int *counts;
} counting_filter_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
    counting_filter_t filter;
    bool (*compare)(const char *, const char *);
};

struct list_iter {
    list_t* list;
    node_t* curr;
};

unsigned int custom_hash(const unsigned char *data, size_t length, unsigned int n);

void counting_filter_init(counting_filter_t *filter, unsigned int  size, unsigned int num_hash) {
    filter->counts = malloc(size * sizeof(unsigned int));
    if (!filter->counts) return;
    filter->num_hash = num_hash;
    filter->size = size;
}

bool counting_filter_contains(const counting_filter_t *filter, const void *data, size_t len) {
    for (unsigned int i = 0; i < filter->num_hash; i++) {
        unsigned int h = custom_hash(data, len, i) % filter->size;
        if (!filter->counts[h]) 
            return false;
    }
    return true;
}

void counting_filter_add(counting_filter_t *filter, const void *data, size_t len) {
    for (unsigned int i = 0; i < filter->num_hash; i++) {
        unsigned int h = custom_hash(data, len, i) % filter->size;
        filter->counts[h]++;
    }
}

void counting_filter_remove(counting_filter_t *filter, const void *data, size_t len) {
    if (!counting_filter_contains(filter, data, len)) return;
    for (unsigned int i = 0; i < filter->num_hash; i++) {
        unsigned int h = custom_hash(data, len, i) % filter->size;
        filter->counts[h]--;
    }
}

void counting_filter_destroy(counting_filter_t *filter) {
    free(filter->counts);
    free(filter);
}

list_t* list_new() {
    list_t* list = malloc(sizeof(list_t));
    if (!list)  return NULL;
    
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    counting_filter_init(&list->filter, size, num_hash);
    list -> compare = compare_strings;
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

bool list_contains(const list_t *list, void *value){
    if (counting_filter_contains(&list->filter, value, sizeof(value))) {
        node_t *current = list -> head;
        while (current != NULL) {
            if (list -> compare(current -> value, value))
                return true;
            current = current -> next;
        }
    }
    return false;
}

bool list_insert_head(list_t *list, void *value){
    if (list_contains(list, value)) return false;

    node_t *nodo = node_new(value, NULL, list -> head);
    if (!nodo) return false;

    if (list_is_empty(list)) list -> tail = nodo;
    else list -> head -> prev = nodo;

    list -> head = nodo;
    list -> size ++;
    counting_filter_add(&list->filter, value, sizeof(value));
    return true;
}

bool list_insert_tail(list_t *list, void *value){
    if (list_contains(list, value)) return false;

    node_t *nodo = node_new(value, list->tail, NULL);
    if (!nodo) return false;

    if (list_is_empty(list)) list -> head = nodo;
    else list -> tail -> next = nodo;
    
    list -> tail = nodo;
    list -> size ++;
    counting_filter_add(&list->filter, value, sizeof(value));
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
    counting_filter_remove(&list->filter, head_value, sizeof(head_value));
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
    counting_filter_remove(&list->filter, tail_value, sizeof(tail_value));
    return tail_value;
}

void list_destroy(list_t *list, void destroy_value(void *)){
    while(!list_is_empty(list)){
        void* value = list_pop_head(list);
        if (destroy_value) destroy_value(value);
    }
    counting_filter_destroy(&list->filter);
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

bool list_iter_insert_first_elem(list_iter_t *iter, void *value){
    if (!list_insert_head(iter -> list, value)) return false;
    iter -> curr = iter -> list -> head;
    return true;
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
    if (list_is_empty(iter -> list)) return list_iter_insert_first_elem(iter, value);
    if (list_iter_at_last(iter)) return list_insert_tail(iter -> list, value);

    node_t *nodo = node_new(value, iter -> curr, iter -> curr -> next);
    if (!nodo) return false;
    
    iter -> curr -> next -> prev = nodo;
    iter -> curr -> next = nodo;
    iter -> list -> size ++;
    counting_filter_add(&iter->list->filter, value, sizeof(value));
    return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    if (list_is_empty(iter -> list)) return list_iter_insert_first_elem(iter, value);
    if (!list_iter_backward(iter)) return list_insert_head(iter -> list, value);
    bool funciono = list_iter_insert_after(iter, value);
    list_iter_forward(iter);
    if (!funciono) return false;
    list_iter_forward(iter);
    return true;
}

void *list_iter_delete(list_iter_t *iter){
    if (list_is_empty(iter -> list)) return NULL;

    if (list_iter_at_last(iter)) {
        iter -> curr = iter -> curr -> prev;
        return list_pop_tail(iter -> list);
    }
    
    if (list_iter_at_first(iter)) {
        iter -> curr = iter -> curr -> next;
        return list_pop_head(iter -> list);
    }

    node_t* curr = iter -> curr;
    void* value = curr -> value;

    iter -> curr = curr -> next;
    curr -> prev -> next = curr -> next;
    curr -> next -> prev = curr -> prev;

    free(curr);
    iter -> list -> size --;
    counting_filter_remove(&iter->list->filter, value, sizeof(value));
    return value;
}

unsigned int custom_hash(const unsigned char *data, size_t length, unsigned int n) {
    const uint32_t prime1 = 2654435761U;
    const uint32_t prime2 = 2246822519U;
    const uint32_t prime3 = 3266489917U;
    const uint32_t prime4 = 668265263U;
    const uint32_t prime5 = 374761393U;

    uint32_t hash = n + prime5;
    size_t i;

    for (i = 0; i + 4 <= length; i += 4) {
        uint32_t k1 = *(uint32_t*)(data + i);
        k1 *= prime2;
        k1 = (k1 << 13) | (k1 >> 19);
        k1 *= prime1;
        hash ^= k1;
        hash = (hash << 17) | (hash >> 15);
        hash = hash * prime4 + prime3;
    }

    const uint8_t *tail = (const uint8_t*)(data + i);
    uint32_t k2 = 0;

    switch (length & 3) {
        case 3: k2 ^= tail[2] << 16;
        case 2: k2 ^= tail[1] << 8;
        case 1: k2 ^= tail[0];
                k2 *= prime3;
                k2 = (k2 << 17) | (k2 >> 15);
                k2 *= prime4;
                hash ^= k2;
    }

    hash ^= (uint32_t)length;
    hash *= prime1;
    hash ^= (hash >> 15);
    hash *= prime2;
    hash ^= (hash >> 13);
    hash *= prime3;
    hash ^= (hash >> 16);

    return hash;
}
