#include "tp3.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_INITIAL 128
#define CAPACITY_FACTOR 0.7
#define RESIZE_FACTOR 2

typedef void (*destroy_f) (void *);
typedef struct Node {
	char* key;
	void* value;
} node_t;

typedef struct dictionary {
  size_t size;
  size_t capacity;
  node_t** nodos;
  destroy_f destroy;
  countfilter_t filtro;
} dictionary_t;

size_t hash (const char *key, size_t size);
bool rehash (dictionary_t *dictionary);

dictionary_t *dictionary_create (destroy_f destroy) { 
  dictionary_t* dictionary = malloc (sizeof (dictionary_t));
  if (!dictionary)  return NULL;

  dictionary -> size = 0;
  dictionary -> capacity = SIZE_INITIAL;
  dictionary -> destroy = destroy;

  dictionary -> nodos = calloc (SIZE_INITIAL , sizeof (node_t*));
  if (!dictionary -> nodos) {
    free (dictionary);
    return NULL;
  }

  return dictionary;
};

bool dictionary_put (dictionary_t *dictionary, const char *key, void *value) {
  if (((float) dictionary->size)/ ((float) dictionary->capacity) > CAPACITY_FACTOR)
    if (!rehash (dictionary))
      return false;

  size_t index = hash (key, dictionary -> capacity);

  while (dictionary -> nodos[index] && dictionary -> nodos[index] -> key) {
    if (strcmp (dictionary -> nodos[index] -> key, key) == 0) {
      if (dictionary -> destroy && dictionary->nodos[index]->value)
        dictionary -> destroy (dictionary -> nodos[index] -> value);
      dictionary -> nodos[index] -> value = value;
      return true;
    }
    index = (index + 1) % dictionary -> capacity;
    if (index == hash (key, dictionary -> capacity))
      return false;
  }
  
  if (!dictionary -> nodos[index]){
    node_t* new_node = malloc (sizeof (node_t));
    if (!new_node) return false;
    dictionary -> nodos[index] = new_node;
  }

  char* copy_key = malloc ((strlen (key) + 1) * sizeof (char));
  if (!copy_key) return false;
  strcpy(copy_key, key);

  dictionary -> nodos[index] -> key = copy_key;
  dictionary -> nodos[index] -> value = value;
  dictionary -> size++;
  
  return true;
};

void *dictionary_get (dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash (key, dictionary -> capacity);
  while (dictionary -> nodos[index]) {
    if (dictionary -> nodos[index] -> key && !strcmp (dictionary -> nodos[index] -> key, key)) {
      *err = false;
      return dictionary -> nodos[index] -> value;
    }
    index = (index + 1) % dictionary -> capacity;
  }
  *err = true;
  return NULL;
};

bool dictionary_delete (dictionary_t *dictionary, const char *key) {
  bool err;
  void* value = dictionary_pop (dictionary, key, &err);
  if (err) return false;
  if (dictionary -> destroy && value) dictionary -> destroy(value);
  return true;
};

void *dictionary_pop (dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash (key, dictionary -> capacity);

  while (dictionary -> nodos[index]) {
    if (dictionary -> nodos[index] -> key && !strcmp(dictionary -> nodos[index] -> key, key)) {
      void* value = dictionary -> nodos[index] -> value;
      free (dictionary -> nodos[index] -> key);
      dictionary -> nodos[index] -> key = NULL;
      dictionary -> nodos[index] -> value = NULL;
      dictionary -> size--;
      *err = false;
      return value;
    }
    index = (index + 1) % dictionary -> capacity;
    if (index == hash (key, dictionary -> capacity)){
      *err = true;
      return NULL;
    }
  }
  *err = true;
  return NULL;
};

bool dictionary_contains (dictionary_t *dictionary, const char *key) {
  size_t index = hash (key, dictionary -> capacity);
  while (dictionary -> nodos[index]) {
    if (dictionary -> nodos[index] -> key && !strcmp (dictionary -> nodos[index] -> key, key))
      return true;
    index = (index + 1) % dictionary -> capacity;
  }
  return false;
};

size_t dictionary_size (dictionary_t *dictionary) { 
  return dictionary -> size; 
};

void dictionary_destroy (dictionary_t *dictionary){
 bool existe_destroy = dictionary -> destroy;
  for (size_t i = 0; i < dictionary -> capacity; i++)
    if (dictionary -> nodos[i]){
      if (dictionary -> nodos[i] -> key){
        if (existe_destroy && dictionary->nodos[i]->value)
          dictionary -> destroy(dictionary -> nodos[i] -> value);
        free(dictionary -> nodos[i] -> key);
      }
      free(dictionary -> nodos[i]);
    }
  free(dictionary -> nodos);  
  free (dictionary);
}

size_t hash (const char *key, size_t size) {
  size_t hash = 2166136261u;
    for (int i = 0; key[i] != '\0'; i++) {
        hash ^= key[i];
        hash *= 16777619;
    }
    return hash % size;
}

bool rehash (dictionary_t *dictionary) {
  size_t oldSize = dictionary -> capacity;
  node_t** newNodes = calloc (oldSize * RESIZE_FACTOR, sizeof (node_t*));
  if (!newNodes) return false;

  node_t** oldNodes = dictionary -> nodos;
  dictionary -> nodos = newNodes;
  dictionary -> capacity = oldSize * RESIZE_FACTOR;

  for (size_t i = 0; i < oldSize; i++)
    if (oldNodes[i]){
      if (oldNodes[i] -> key){
        size_t index = hash (oldNodes[i] -> key, dictionary -> capacity);
        while (dictionary->nodos[index])
          index = (index + 1) % dictionary -> capacity;
        dictionary -> nodos[index] = oldNodes[i];
      } else {
        free(oldNodes[i]);
      }
    }
  free(oldNodes);
  return true;
}