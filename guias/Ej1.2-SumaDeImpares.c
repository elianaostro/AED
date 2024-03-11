#include <stdio.h>
#include <stdbool.h>

bool esPar(int numero){
    return (numero%2 ==0);
}

int SumaDeImpares (int n){
    int resultado = 0;
    for (int i = 0; i < n; i++){
        if (!esPar(i)) resultado += i;
    }

    return resultado;
}

void realizarPrueba(int numero, int esperado) {
    int resultado = SumaDeImpares(numero);
    
    printf("Prueba para el numero %d: ", numero);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    realizarPrueba(2, 1); 
    realizarPrueba(3, 1);  
    realizarPrueba(6, 9);  
    realizarPrueba(9, 16); 
    realizarPrueba(12, 36); 

    return 0;
}