#include <stdio.h>
#include <stdbool.h>

void crearArreglo(int v){
    int arreglo[8]={v,v,v,v,v,v,v,v};
    for (int i = 0; i < 8; i++){
        printf("%d \n", arreglo[i]);
    }
}

int* crearArregloDin(int n, int v){
    int arreglo[n];
    for (int i = 0; i < n; i++){
        arreglo[i] = v;
    }
    return &arreglo;
}

int main(){
    crearArreglo(5);
    int* arreglo = crearArregloDin(3, 5);
    for (int i = 0; i < 3; i++){
        printf("%d \n", arreglo[i]);
    }
    
    return 0;
}