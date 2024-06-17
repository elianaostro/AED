#include "tp3.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_INITIAL 128
#define CAPACITY_FACTOR_DIC 0.7
#define CAPACITY_FACTOR_NODO 0.1
#define RESIZE_FACTOR 2

typedef struct entry {
    char* key;
    void* value;
    node_t* next;
} entry_t;

typedef struct node {
    entry_t* head;
    size_t size;
}node_t;

typedef struct dictionary {
  size_t size;
  size_t capacity;
  node_t* nodos;
  destroy_f destroy;
} dictionary_t;

size_t hash(const char *key, size_t size) {
  size_t hash = 2166136261u;
    for (int i = 0; key[i] != '\0'; i++) {
        hash ^= key[i];
        hash *= 16777619;
    }
    return hash % size;
}

dictionary_t *dictionary_create(destroy_f destroy) { 
  dictionary_t* dictionary = malloc(sizeof(dictionary_t));
  if (!dictionary)  return NULL;

  dictionary -> size = 0;
  dictionary -> capacity = SIZE_INITIAL;
  dictionary -> destroy = destroy;
  dictionary -> nodos = calloc(SIZE_INITIAL, sizeof(node_t));

  if (!dictionary -> nodos) {
    free(dictionary);
    return NULL;
  }

  return dictionary;
};

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  if (((float) dictionary->size)/ ((float) dictionary->capacity) > CAPACITY_FACTOR_DIC)
    if (!rehash(dictionary))
      return false;

  size_t index = hash(key, dictionary -> capacity);
  entry_t entry = dictionary -> nodos[index] -> head;
  
  while (entry) {
    if (strcmp(entry -> key, key) == 0) {
      if (dictionary -> destroy && entry -> value)
        dictionary -> destroy(entry -> value);
      entry -> value = value;
      return true;
    }
    entry = entry -> next;
  }

  entry_t* new_entry = malloc(sizeof(entry_t));
  if (!new_entry) return false;

  char* new_key = malloc(strlen(key) + 1);
  if (!new_key) return false;
  strcpy(copy_key, key);

  new_entry -> key = new_key;
  new_entry -> value = value;
  new_entry -> next = dictionary -> nodos[index] -> head;

  dictionary -> nodos[index] -> head = new_entry;
  dictionary -> nodos[index] -> size++;
  dictionary -> size++;
  
  return true;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash(key, dictionary -> capacity);
  entry_t entry = dictionary -> nodos[index] -> head;
  while (entry) {
    if (entry -> key && !strcmp(entry -> key, key)) {
      *err = false;
      return entry -> value;
    }
    entry = entry -> next;
  }
  *err = true;
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  bool err;
  void* value = dictionary_pop(dictionary, key, &err);
  if (err) return false;
  if (dictionary -> destroy && value) dictionary -> destroy(value);
  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash(key, dictionary -> capacity);
  entry_t* entry = dictionary -> nodos[index] -> head;
  entry_t* prev = NULL;
  while (entry) {
    if (entry -> key && !strcmp(entry -> key, key)) {
      void* value = entry -> value;
      if (prev) prev -> next = entry -> next;
      else dictionary -> nodos[index] -> head = entry -> next;
      free(entry -> key);
      free(entry);
      dictionary -> size--;
      dictionary -> nodos[index] -> size--;
      *err = false;
      return value;
    }
    prev = entry;
    entry = entry -> next;
  }
  *err = true;
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  size_t index = hash(key, dictionary -> capacity);
  
};

size_t dictionary_size(dictionary_t *dictionary) { return 0; };

void dictionary_destroy(dictionary_t *dictionary){};
