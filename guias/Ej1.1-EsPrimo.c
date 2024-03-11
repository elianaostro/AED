#include <stdio.h>
#include <stdbool.h>

bool esPrimo(int n){
    bool esPrimo = true;
    for (int i = 2; i < n; i++){
        if (n % i == 0){
            esPrimo = false;
            break;
        } else {
            esPrimo = true;
        }
    }
    return esPrimo;
}

void realizarPrueba(int numero, bool esperado) {
    bool resultado = esPrimo(numero);
    
    printf("Prueba para el numero %d: ", numero);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    realizarPrueba(2, true); 
    realizarPrueba(3, true);  
    realizarPrueba(4, false);  
    realizarPrueba(12, false); 
    realizarPrueba(13, true); 

    return 0;
}