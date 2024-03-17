#include <stdio.h>
#include <stdbool.h>

bool esPar(int numero){
    return (numero%2 ==0);
}

void realizarPrueba(int numero, bool esperado) {
    int resultado = esPar(numero);
    
    printf("Prueba para el numero %d: ", numero);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    realizarPrueba(2, true); 
    realizarPrueba(3, false);  
    realizarPrueba(6, true);  
    realizarPrueba(9, false); 
    realizarPrueba(12, true); 

    return 0;
}