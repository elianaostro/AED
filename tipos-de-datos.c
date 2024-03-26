#include <stdio.h>
#include <stdbool.h>

//gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror stack.c -o stack

void TiposDeDatos(){
    void    vacio;
    char    caracter =  'a';
    int     numero =    7;
    long    Ngrande =   234567;
    float   flotante =  4,6;
    double  Fgrande =   3,14290;
    bool    booleano =  true;
}

void OperadoresAritmeticos(int a, int b){
    int suma =          a + b;
    int resta =         a - b;
    int producto =      a * b;
    int dividendo =     a / b;
    int resto =         a % b;
    a++; //incrementa un numero
    b++; //decrementa un numero
}

int Casteo(long a){
    return (int) a;
}

void OperadoresRelacionales(int a,int b){
    bool igualdad =     a==b ;
    bool desigualdad =  a!=b ;
    bool mayor =        a>b ;
    bool menor =        a<b ;
    bool mayor =        a>=b ;
    bool menor =        a<=b ;
}

void OperadoresLogicos(bool a, bool b){
    bool and =  a&&b ;
    bool or =   a||b ;
    bool not =  !a ;
}

void excepciones(int a){
    if (a<5) {
        //codigo
    } else {
        //codigo
    }

    if (a==5) //codigo
}

void bucle(int a){

    while (a<10){
        a++;
    }

    while (a>3) a--;

    for (/*inicializacion*/ int i=1; /*test*/ i<a; /*actualizacion*/ i++) {
        //codigo
    }
}

struct lista_simplemente_enlazada{
    metadatos(lista){
        nodo* head
        size_t cant
        nodo* tail
        
        nodo{
            nodo* sig
            void* valor
        }
    }

    primitivas{
        lista* crear();                         //O(1)
        void destruir(lista* l);                //O(n)
        bool intert_first(void* val, lista* l); //O(1)
        bool intsert_last(void* val, lista* l); //O(1) (con tail)
        void* pop_first(lista* l);              //O(1)
        void* pop_last(lista* l);               //O(n) (con/sin tail)
        size_t cant(lista* l);                  //O(1) 
    }

    //crear funcion que elimine los duplicados

    class iteradores{
        nodo* actual
        lista* l

        iter* create_at_first(lista* l) //O(1)
        bool avanzar(iter)              //O(1)
        void* obtener(iter)             //O(1)
        bool al_final(iter)             //O(1)
        bool insert_front(iter,val)     


        iter* iter = create_first(lista)
        while(!al_final(iter)){
            print( obtener(iter) )
            avanzar(iter)
        }
        print(obtener(iter))  
    }
};

typedef struct nodo{
    nodo* sig
    nodo* ant
    void* valor
}

typedef struct lista_doblemente_enlazada{
    //metadatos
    nodo* head
    size_t cant
    nodo* tail
}

//primitivas
lista* crear();                         //O(1)
void destruir(lista* l);                //O(n)
bool intert_first(void* val, lista* l); //O(1)
bool intsert_last(void* val, lista* l); //O(1) (con tail)
void* pop_first(lista* l);              //O(1)
void* pop_last(lista* l);               //O(1)
size_t cant(lista* l);                  //O(1) 


typedef struct iteradores{
    nodo* actual
    lista* l
};

//primitivas
iter* create_at_first(lista* l) //O(1)
iter* create_at_last(lista* l)  //O(1)
bool avanzar(iter)              //O(1)
bool retroceder(iter)           //O(1)
void* obtener(iter)             //O(1)
bool al_final(iter)             //O(1)
bool al_principio(iter)         //O(1)
bool insert_front(iter,val)     //O(n)
bool insert_back(iter,val)      //O(n)
void* remover(iter)




typedef struct nodo{
            nodo* sig
            void* valor
        } Nodo;

typedef struct listas_circulares{
    // es una lista simplemente enlazada y un iterador
    /*j1 -> j2
    j2 -> j3
    j3 -> j1*/
    nodo* actual
    size_t cant        
}

//primitivas{
lCircular* crear();             //O(1)
void destruir(l);               //O(n)
void* actual(l);                //O(1)
void avanzar(l);                //O(1)
bool insert_after(l, dato);     //O(1)
bool insert_before(l, dato);    //O(1)
void* remover(l);               //O(1)
size_t largo(l);                //O(1)
bool vacia(l);                  //O(1)




typedef struct Nodo{  
    nodo* sig;
    nodo* ant;
    void* valor;
} Node;

typedef struct listas circulares_Doblemente_Enlazadas{
    //metadatos
    nodo* actual
    size_t cant
};

//primitivas
lCircular* crear();             //O(1)
void destruir(l);               //O(n)
void* actual(l);                //O(1)
void avanzar(l);                //O(1)
void retroceder(l);             //O(1)
bool insert_after(l, dato);     //O(1)
bool insert_before(l, dato);    //O(1)
void* remover(l);               //O(1)
size_t largo(l);                //O(1)
bool vacia(l);                  //O(1)




//primitivas pila
pila* crear():                      //O(1)
void destruir(pila* p);             //O(1) o O(n) si borro los datos
bool push(pila* p, void* dato):     //O(1)
void* top(pila* p);                 //O(1)
void* pop(pila* p);                 //O(1)
size_t cantidad();                  //O(1)
bool is_empty()                     //O(1)


typedef struct pila(stack){
    //LIFO(Last in First out)
    //metadatos(VD):  #vector dinamico
    void** datos
    size_t cant
};

//primitivas
pila* crear(){    //O(1)
    void** datos= malloc(sizeof(void*)*2)
    pila* p=malloc(sizeof(pila))
    p -> cant = 0
    p -> datos = datos
    return p;
}
void destruir(pila* p){   //O(1) o O(n) si borro los datos
    free(p -> datos)
    free(p)
}
bool push(pila* p, void* dato){   //O(1)
    p ->dato [p -> cant] = datos
    p -> cant ++
}


typedef struct pila2(stack){
    //metadatos(listas):  #vector dinamico
    lista* l
}

//primitivas{
pila* crear(){
    p = malloc(sizeof(pila))
    p -> l = lista-crear()
}
bool push(p, dato){
    return lista-insert_first(p -> l, dato)
}
void* pop(p){
    return lista-pop_first(p -> l)
}




typedef struct Cola(queue){
    //FIFO first in first out
    //metadatos op1
    lista* l;

    //metadatos  op2
    pila* p1;
    pila* p2;
};

//primitivas
cola* crear();          //O(1)
void destruir();        //O(n)
bool encolar(c, dato);  //O(1)
void* desencolar(c);    //O(1)


typedef struct nodo{
    void* dato;
    struct nodo* sig;
} nodo_t;

typedef struct heap{
    // una estrutura que te devuelve el max o min en O(1)
    
};
