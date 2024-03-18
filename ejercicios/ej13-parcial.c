// EJ 1
struct list {
    struct node *head;
    struct node *tail;
}

struct node {
    struct node *sig;
    void *value;
}


/* 
borrar primero O(1)
insertar último O(1)
borrar último O(n)
insertar primero O(1)
obtener la cantidad O(n)
sacar un nodo del medio O(n) 
*/

// Ej 2

struct Nodo{
    int Key;
    void *Value;
    struct Nodo *Next;
    struct Nodo *Prev;
}

struct ListaD{
    struct Nodo *Head;
    struct Nodo *Tail;
    int Cantidad;
}

void swap(void *x, void *y) {
    void temp = *x;
    *x = *y;
    *y = temp;
}

void inertir_lista(ListaD*l){
    if (!l.cantidad || l.cantidad == 1) return;
    struct nodo *actual = l -> head;
    while(actual -> next){
        swap(actual->prev, acutal->next)
        actual = actual -> prev;
    }
    swap(l -> head, l -> tail);

}
