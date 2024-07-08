#include "test_malloc.h"
#include "testing.h"
#include "tp2.h"
#include <stdbool.h>
#include <stdlib.h>

bool test_create_and_destroy_list() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list_destroy(list, NULL);
  return tests_result;
}

bool test_create_with_failed_malloc() {
  bool tests_result = true;
  set_malloc_status(false);
  list_t *list = list_new();
  set_malloc_status(true);
  tests_result &= test_assert("La lista no fue creada", list == NULL);
  return tests_result;
}

bool test_empty_size_and_length() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("La lista está vacia", list_is_empty(list));
  list_destroy(list, NULL);
  return tests_result;
}

bool test_insert_head_successfully() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("La lista está vacia", list_is_empty(list));
  tests_result &= test_assert("Se inserto un elemento en la lista",
                              list_insert_head(list, NULL));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("La lista no está vacia", !list_is_empty(list));
  list_destroy(list, NULL);
  return tests_result;
}

bool test_insert_head_fails() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  set_malloc_status(false);
  tests_result &= test_assert("Falló insertar un elemento en la lista",
                              !list_insert_head(list, NULL));
  set_malloc_status(true);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("Luego de fallar vuelve a funcionar insertar",
                              list_insert_head(list, NULL));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  list_destroy(list, NULL);
  return tests_result;
}

bool test_destroy_value() {
  bool tests_result = true;
  bool insert_status = true;
  list_t *list = list_new();
  for (int i = 0; i < 100; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    insert_status &= list_insert_head(list, aux);
  }
  tests_result &=
      test_assert("Se insertaron 100 elementos en la lista", insert_status);
  list_destroy(list, free);
  test_assert("Se destruyo la lista", true);
  return tests_result;
}

bool test_insert_tail_successfully() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("La lista está vacia", list_is_empty(list));
  tests_result &= test_assert("Se inserto un elemento en la lista",
                              list_insert_tail(list, NULL));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("La lista no está vacia", !list_is_empty(list));
  list_destroy(list, NULL);
  return tests_result;
}

bool test_insert_tail_fails() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  set_malloc_status(false);
  tests_result &= test_assert("Falló insertar un elemento en la lista",
                              !list_insert_tail(list, NULL));
  set_malloc_status(true);
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("Luego de fallar vuelve a funcionar insertar",
                              list_insert_tail(list, NULL));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  list_destroy(list, NULL);
  return tests_result;
}

bool test_peek_head() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &= test_assert("EL valor de head es NULL con la lista vacia",
                              !list_peek_head(list));
  for (int i = 0; i < 10; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    list_insert_head(list, aux);
    tests_result &= test_assert("El valor de head es correcto",
                                *((int *)list_peek_head(list)) == i);
  }
  list_destroy(list, free);
  return tests_result;
}

bool test_peek_tail() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &= test_assert("EL valor de head es NULL con la lista vacia",
                              !list_peek_tail(list));
  for (int i = 0; i < 10; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    list_insert_tail(list, aux);
    tests_result &= test_assert("El valor de head es correcto",
                                *((int *)list_peek_tail(list)) == i);
  }
  list_destroy(list, free);
  return tests_result;
}

bool test_pop_empty_list() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("La salida de pop head es NULL", !list_pop_head(list));
  tests_result &=
      test_assert("La salida de pop tail es NULL", !list_pop_tail(list));
  list_destroy(list, NULL);
  return tests_result;
}

bool test_simple_pop_head() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = malloc(sizeof(int));
  *aux = 42;
  tests_result &=
      test_assert("Se inserto un elemento en el principio de la lista",
                  list_insert_head(list, aux));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("Al eliminar el head el valor es correcto",
                              *((int *)list_pop_head(list)) == 42);
  tests_result &=
      test_assert("No hay más elementos en la lista", !list_pop_head(list));
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("Se inserto un elemento en el final de la lista",
                              list_insert_tail(list, aux));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("Al eliminar el head el valor es correcto",
                              *((int *)list_pop_head(list)) == 42);
  tests_result &=
      test_assert("No hay más elementos en la lista", !list_pop_head(list));
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  free(aux);
  list_destroy(list, NULL);
  return tests_result;
}

bool test_simple_pop_tail() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = malloc(sizeof(int));
  *aux = 42;
  tests_result &=
      test_assert("Se inserto un elemento en el principio de la lista",
                  list_insert_tail(list, aux));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("Al eliminar el tail el valor es correcto",
                              *((int *)list_pop_tail(list)) == 42);
  tests_result &=
      test_assert("No hay más elementos en la lista", !list_pop_tail(list));
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  tests_result &= test_assert("Se inserto un elemento en el final de la lista",
                              list_insert_head(list, aux));
  tests_result &=
      test_assert("El largo de la lista es 1", list_length(list) == 1);
  tests_result &= test_assert("Al eliminar el tail el valor es correcto",
                              *((int *)list_pop_tail(list)) == 42);
  tests_result &=
      test_assert("No hay más elementos en la lista", !list_pop_tail(list));
  tests_result &=
      test_assert("El largo de la lista es 0", list_length(list) == 0);
  free(aux);
  list_destroy(list, NULL);
  return tests_result;
}

bool test_multiple_peek() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 10; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    if (i % 2 == 0) {
      tests_result &= test_assert("Se inserto un número al principio",
                                  list_insert_head(list, aux));
      tests_result &= test_assert("El valor de head es el insertado",
                                  *((int *)list_peek_head(list)) == i);
      if (list_length(list) > 1) {
        tests_result &= test_assert("El valor de tail es correcto",
                                    *((int *)list_peek_tail(list)) == (i - 1));
      } else {
        tests_result &= test_assert("El valor de tail es correcto",
                                    *((int *)list_peek_tail(list)) == i);
      }
    } else {
      tests_result &= test_assert("Se inserto un número al final",
                                  list_insert_tail(list, aux));
      tests_result &= test_assert("El valor de head es correcto",
                                  *((int *)list_peek_head(list)) == (i - 1));
      tests_result &= test_assert("El valor de tail es el insertado",
                                  *((int *)list_peek_tail(list)) == i);
    }
  }
  list_destroy(list, free);
  return tests_result;
}

bool test_multiple_pop() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 100; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    list_insert_head(list, aux);
    list_insert_tail(list, aux);
  }

  tests_result &=
      test_assert("El largo de la lista es 200", list_length(list) == 200);

  for (int i = 99; i >= 0; i--) {
    int *aux = list_pop_head(list);
    tests_result &=
        test_assert("Eliminar el primer elemento funciona correctamente",
                    *((int *)aux) == i);
    tests_result &=
        test_assert("Eliminar el último elemento funciona correctamente",
                    (int *)list_pop_tail(list) == aux);
    free(aux);
  }

  tests_result &= test_assert("La lista está vacia", list_is_empty(list));

  list_destroy(list, NULL);
  return tests_result;
}

bool test_multiple_pop_random_patterns() {
  bool tests_result = true;
  list_t *list = list_new();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 100; i++) {
    int *aux = malloc(sizeof(int));
    *aux = i;
    list_insert_head(list, aux);
    list_insert_tail(list, aux);
    switch (rand() % 4) {
    case 0:
      list_insert_head(list, aux);
      list_insert_tail(list, aux);
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      *((int *)list_pop_head(list)) == i);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      *((int *)list_pop_tail(list)) == i);
      break;

    case 1:
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      *((int *)list_pop_head(list)) == i);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      *((int *)list_pop_tail(list)) == i);
      list_insert_head(list, aux);
      list_insert_tail(list, aux);
      break;

    case 2:
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      *((int *)list_pop_tail(list)) == i);
      list_insert_head(list, aux);
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      *((int *)list_pop_head(list)) == i);
      list_insert_tail(list, aux);
      break;

    case 3:
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      *((int *)list_pop_head(list)) == i);
      list_insert_head(list, aux);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      *((int *)list_pop_tail(list)) == i);
      list_insert_tail(list, aux);
      break;
    }
  }

  tests_result &=
      test_assert("El largo de la lista es 200", list_length(list) == 200);

  for (int i = 99; i >= 0; i--) {
    int *aux = list_pop_head(list);
    tests_result &=
        test_assert("Eliminar el primer elemento funciona correctamente",
                    *((int *)aux) == i);
    tests_result &=
        test_assert("Eliminar el último elemento funciona correctamente",
                    (int *)list_pop_tail(list) == aux);
    free(aux);
  }

  tests_result &= test_assert("La lista está vacia", list_is_empty(list));

  list_destroy(list, NULL);
  return tests_result;
}

bool test_multiple_random_failed_operations() {
  bool tests_result = true;
  list_t *list1 = list_new();
  tests_result &= test_assert("La lista 1 fue creada", list1 != NULL);
  list_t *list2 = list_new();
  tests_result &= test_assert("La lista 2 fue creada", list2 != NULL);
  int *aux = NULL, *aux2 = NULL;
  for (int i = 0; i < 300; i++) {
    switch (rand() % 12) {
    case 0: // insert head exitoso
      aux = malloc(sizeof(int));
      *aux = i;
      list_insert_head(list1, aux);
      list_insert_head(list2, aux);
    case 1: // insert head fallido
      set_malloc_status(false);
      list_insert_head(list1, aux);
      set_malloc_status(true);
    case 2: // insert tail exitoso
      aux = malloc(sizeof(int));
      *aux = i;
      list_insert_tail(list1, aux);
      list_insert_tail(list2, aux);
    case 3: // insert tail fallido
      set_malloc_status(false);
      list_insert_tail(list1, aux);
      set_malloc_status(true);
    case 4: // pop head
      aux = list_pop_head(list1);
      if (aux) {
        free(aux);
      }
      list_pop_head(list2);
    case 5: // pop tail
      aux = list_pop_tail(list1);
      if (aux) {
        free(aux);
      }
      list_pop_tail(list2);
    default:
      aux = malloc(sizeof(int));
      *aux = i;
      list_insert_head(list1, aux);
      list_insert_head(list2, aux);
    }
    tests_result &=
        test_assert("El estado de las listas es correcto",
                    (list_length(list1) == list_length(list2)) &&
                        (list_peek_head(list1) == list_peek_head(list2)) &&
                        (list_peek_tail(list1) == list_peek_tail(list2)));
  }
  for (int i = 0; i < list_length(list1) / 2; i++) {
    switch (rand() % 6) {
    case 0:
      aux = list_pop_head(list1);
      aux2 = list_pop_head(list2);
      tests_result &= test_assert("El valor extraido de las listas es correcto",
                                  aux == aux2);
      free(aux);
    case 1: // insert head fallido
      aux = list_pop_tail(list1);
      aux2 = list_pop_tail(list2);
      tests_result &= test_assert("El valor extraido de las listas es correcto",
                                  aux == aux2);
      free(aux);
    }
  }
  list_destroy(list1, free);
  list_destroy(list2, NULL);
  return tests_result;
}

int main(void) {
  srand(42);
  int return_code = 0;
  return_code += !test_create_and_destroy_list();
  return_code += !test_create_with_failed_malloc();
  return_code += !test_empty_size_and_length();
  return_code += !test_insert_head_successfully();
  return_code += !test_insert_head_fails();
  return_code += !test_destroy_value();
  return_code += !test_insert_tail_successfully();
  return_code += !test_insert_tail_fails();
  return_code += !test_peek_head();
  return_code += !test_peek_tail();
  return_code += !test_pop_empty_list();
  return_code += !test_simple_pop_head();
  return_code += !test_simple_pop_tail();
  return_code += !test_multiple_peek();
  return_code += !test_multiple_pop();
  return_code += !test_multiple_pop_random_patterns();
  return_code += !test_multiple_random_failed_operations();
  if (return_code == 0) {
    printf("Todo ok!\n");
  } else {
    printf("Error code is %d\n", return_code);
  }

  return return_code;
}
