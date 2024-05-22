#include "tp3.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_INITIAL 100
#define CAPACITY_FACTOR 0.75
#define RESIZE_FACTOR 2

typedef struct Node {
	char* key;
	void* value;
} node_t;

struct dictionary {
  size_t elems;
  size_t arraySize;
  node_t** nodos;
  destroy_f destroy;
};

typedef struct dictionary dictionary_t;
typedef void (*destroy_f) (void *);

size_t hash (const char *key, size_t size);
bool rehash (dictionary_t *dictionary);
void nodos_destroy(node_t** nodos, size_t arraySize, destroy_f destroy);

dictionary_t *dictionary_create (destroy_f destroy) { 
  dictionary_t* dictionary = malloc (sizeof (dictionary_t));
  if (!dictionary)  return NULL;

  dictionary -> elems = 0;
  dictionary -> arraySize = SIZE_INITIAL;
  dictionary -> destroy = destroy;
  dictionary -> nodos = calloc (SIZE_INITIAL , sizeof (node_t*));

  if (!dictionary -> nodos) {
    free (dictionary);
    return NULL;
  }

  return dictionary;
};

bool dictionary_put (dictionary_t *dictionary, const char *key, void *value) {
  if ((float) dictionary -> arraySize * CAPACITY_FACTOR < dictionary -> elems + 1)
    if (!rehash (dictionary))
      return false;

  size_t index = hash (key, dictionary -> arraySize);

  while (dictionary -> nodos[index] && dictionary -> nodos[index] -> key) {
    if (!strcmp (dictionary -> nodos[index] -> key, key)) {
      if (dictionary -> destroy)
        dictionary -> destroy (dictionary -> nodos[index] -> value);
      dictionary -> nodos[index] -> value = value;
      return true;
    }
    index = (index + 1) % dictionary -> arraySize;
  }
  
  if (!dictionary -> nodos[index]){
    node_t* new_node = malloc (sizeof (node_t));
    if (!new_node) return false;
    dictionary -> nodos[index] = new_node;
  }

  char* copy_key = malloc (strlen (key) + 1);
  if (!copy_key) return false;
  strcpy(copy_key, key);

  dictionary -> nodos[index] -> key = copy_key;
  dictionary -> nodos[index] -> value = value;
  dictionary -> elems++;
  
  return true;
};

void *dictionary_get (dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash (key, dictionary -> arraySize);
  while (dictionary -> nodos[index] && dictionary -> nodos[index] -> key) {
    if (!strcmp (dictionary -> nodos[index] -> key, key)) {
      *err = false;
      return dictionary -> nodos[index] -> value;
    }
    index = (index + 1) % dictionary -> arraySize;
  }
  *err = true;
  return NULL;
};

bool dictionary_delete (dictionary_t *dictionary, const char *key) {
  bool err;
  void* value = dictionary_pop (dictionary, key, &err);
  if (!err) {
    if (dictionary -> destroy)
      dictionary -> destroy (value);
    return true;
  }
  return false;
};

void *dictionary_pop (dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash (key, dictionary -> arraySize);

  while (dictionary -> nodos[index] && dictionary -> nodos[index] -> key) {
    if (!strcmp (dictionary -> nodos[index] -> key, key)) {
      void* value = dictionary -> nodos[index] -> value;
      free (dictionary -> nodos[index] -> key);
      dictionary -> nodos[index] -> key = NULL;
      dictionary -> nodos[index] -> value = NULL;
      dictionary -> elems--;
      *err = false;
      return value;
    }
    index = (index + 1) % dictionary -> arraySize;
  }
  *err = true;
  return NULL;
};

bool dictionary_contains (dictionary_t *dictionary, const char *key) {
  size_t index = hash (key, dictionary -> arraySize);
  while (dictionary -> nodos[index] && dictionary -> nodos[index] -> key) {
    if (!strcmp (dictionary -> nodos[index] -> key, key))
      return true;
    index = (index + 1) % dictionary -> arraySize;
  }
  return false;
};

size_t dictionary_size (dictionary_t *dictionary) { 
  return dictionary -> elems; 
  };

// void dictionary_destroy (dictionary_t *dictionary){
//   nodos_destroy(dictionary -> nodos, dictionary -> arraySize, dictionary -> destroy);
//   free (dictionary);
// }

// void nodos_destroy(node_t** nodos, size_t arraySize, destroy_f destroy){
//   bool existe_destroy = destroy;
//   for (size_t i = 0; i < arraySize; i++)
//     if (nodos[i]){
//       if (nodos[i] -> key){
//         if (existe_destroy)
//           destroy(nodos[i] -> value);
//         free(nodos[i] -> key);
//       }
//       free(nodos[i]);
//     }
//   free(nodos);
// };

void dictionary_destroy (dictionary_t *dictionary){
 bool existe_destroy = dictionary -> destroy;
  for (size_t i = 0; i < dictionary -> arraySize; i++)
    if (dictionary -> nodos[i]){
      if (dictionary -> nodos[i] -> key){
        if (existe_destroy)
          dictionary -> destroy(dictionary -> nodos[i] -> value);
        free(dictionary -> nodos[i] -> key);
      }
      free(dictionary -> nodos[i]);
    }
  free(dictionary -> nodos);  
  free (dictionary);
}

size_t hash (const char *key, size_t size) {
  size_t hash = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    hash = (hash * 256 + key[i]) % size;
  }
  return hash;
}

// bool rehash (dictionary_t *dictionary) {
//   size_t oldSize = dictionary -> arraySize;
//   node_t** newNodes = calloc (oldSize * RESIZE_FACTOR, sizeof (node_t*));
//   if (!newNodes) return false;

//   node_t** oldNodes = dictionary -> nodos;
//   dictionary -> nodos = newNodes;
//   dictionary -> arraySize = oldSize * RESIZE_FACTOR;

//   for (size_t i = 0; i < oldSize; i++)
//     if (oldNodes[i] && oldNodes[i] -> key)
//       if (!dictionary_put (dictionary, oldNodes[i] -> key, oldNodes[i] -> value)){
//         nodos_destroy (newNodes, dictionary -> arraySize, dictionary -> destroy);
//         dictionary -> nodos = oldNodes;
//         dictionary -> arraySize = oldSize;
//         return false;
//       }
  
//   nodos_destroy (oldNodes, oldSize, dictionary -> destroy);
//   return true;
// }

bool rehash (dictionary_t *dictionary) {
  size_t oldSize = dictionary -> arraySize;
  node_t** newNodes = calloc (oldSize * RESIZE_FACTOR, sizeof (node_t*));
  if (!newNodes) return false;

  node_t** oldNodes = dictionary -> nodos;
  dictionary -> nodos = newNodes;
  dictionary -> arraySize = oldSize * RESIZE_FACTOR;

  for (size_t i = 0; i < oldSize; i++)
    if (oldNodes[i]){
      if (oldNodes[i] -> key){
        size_t index = hash (oldNodes[i] -> key, dictionary -> arraySize);
        dictionary -> nodos[index] = oldNodes[i];
      }
      free(oldNodes[i]);
    }
  free(oldNodes);
  return true;
}