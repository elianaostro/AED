void removeRepeatedElements(ListaSimplementeEnlazada lista) {
    ListaSimplementeEnlazada aux = crearListaSimplementeEnlazada();
    if(!aux) return;
    Nodo_t = lista->head;
    insertar(aux, nodo);

    while(nodo)
        if(aux->tail.value != nodo.value){ 
            insertTail(nodo.value)
        }
        nodo = nodo->next:
}

void* getMedio(void* head){
    void* medio = head;
    while (head -> next){
        head = head -> next -> next;
        medio = medio -> next;
    }
    return medio;
}


struct BackupQueue {
    ListaDobleMenteEnlazada queue;
    ListaDobleMenteEnlazada backup;
    int amountOfTransactionsDoneAfterLastBackup;
    int maxOfTransactionsBeforeBackup; // m
}

struct nodo {
    node_t next;
    node_t prev;
    int value;
};


struct PilaEspecial {
    node_t head;
    int min;
    int size;
};
