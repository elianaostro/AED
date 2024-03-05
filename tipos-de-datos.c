#include <stdio.h>
#include <stdbool.h>

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
    a++ //incrementa un numero
    b++ //decrementa un numero
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

class lista_simplemente_enlazada{
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

        iter* iter = create_first(lista)
        while(!al_final(iter)){
            print( obtener(iter) )
            avanzar(iter)
        }
        print(obtener(iter))  
    }
}

class lista_doblemente_enlazada{
    metadatos(lista){
        nodo* head
        size_t cant
        nodo* tail
        
        nodo{
            nodo* sig
            nodo* ant
            void* valor
        }
    }

    primitivas{
        lista* crear();                         //O(1)
        void destruir(lista* l);                //O(n)
        bool intert_first(void* val, lista* l); //O(1)
        bool intsert_last(void* val, lista* l); //O(1) (con tail)
        void* pop_first(lista* l);              //O(1)
        void* pop_last(lista* l);               //O(1)
        size_t cant(lista* l);                  //O(1) 
    }

    class iteradores{
        nodo* actual
        lista* l

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
    }
}

class listas circulares{
    // es una lista simplemente enlazada y un iterador
    /*j1 -> j2
    j2 -> j3
    j3 -> j1*/

    metadatos(lista){
        nodo* actual
        size_t cant
        
        nodo{
            nodo* sig
            void* valor
        }
    }

    primitivas{
        lCircular* crear();             //O(1)
        void destruir(l);               //O(n)
        void* actual(l);                //O(1)
        void avanzar(l);                //O(1)
        bool insert_after(l, dato);     //O(1)
        bool insert_before(l, dato);    //O(1)
        void* remover(l);               //O(1)
        size_t largo(l);                //O(1)
        bool vacia(l);                  //O(1)
        }
}


class listas circulares_Doblemente_Enlazadas{
    metadatos(lista){
        nodo* actual
        size_t cant
        
        nodo{
            nodo* sig
            nodo* ant
            void* valor
        }
    }

    primitivas{
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
        }
}