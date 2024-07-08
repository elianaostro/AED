#include <stdbool.h>
#include <stdio.h>

#ifndef TP2_H
#define TP2_H

struct list;
typedef struct list list_t;
struct iterator;
typedef struct list_iter list_iter_t;

/*
 * Crea una nueva lista.
 * Devuelve NULL si falla.
 */
list_t *list_new(void);

/*
 * Devuelve TRUE si la lista está vacia.
 * Pre-condiciones: La lista existe.
 */
bool list_is_empty(const list_t *list);

/*
 * Devuelve el largo de la lista.
 * Pre-condiciones: La lista existe.
 */
size_t list_length(const list_t *list);

/*
 * Inserta un elemento al principio de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve TRUE si funcionó y insertó un elemento.
 */
bool list_insert_head(list_t *list, void *value);

/*
 * Inserta un elemento al final de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve TRUE si funcionó y insertó un elemento.
 */
bool list_insert_tail(list_t *list, void *value);

/*
 * Elimina un elemento del principio de la lista y devuelve el puntero al dato que almacenaba.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el dato y saca un nodo del principio de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void *list_pop_head(list_t *list);

/*
 * Elimina un elemento del final de la lista y devuelve el puntero al dato que almacenaba.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el dato y saca un nodo del final de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void *list_pop_tail(list_t *list);

/*
 * Devuelve el puntero al dato que está en el principio de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el primer valor de la lista, NULL si la lista está vacia.
 */
void *list_peek_head(const list_t *list);

/*
 * Devuelve el puntero al dato que está en el final de la lista.
 * Devuelve NULL si la lista está vacia.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el último valor de la lista, NULL si la lista está vacia.
 */
void *list_peek_tail(const list_t *list);

/*
 * Destruye una lista liberando toda su memoria. Recibe por parametro una función para liberar a sus miembros.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: La memoria de la lista está liberada junto con la de sus elementos.
 * El puntero a lista ya no puede usarse. Si la función es NULL no la utiliza.
 */
void list_destroy(list_t *list, void destroy_value(void *));


#endif