#include <stdio.h>
#include <stdbool.h>

int CantdePalabras(char *s){
    int i = 0, cant = 0;
    bool sameword = false
    while(s[i] != '\0'){ 
        if (!sameword){
            if (! s[i] == " "){
                sameword = true;
                cant++;
            }
        } else {

        }
    }
    return cant;
}

void realizarPrueba(char *s, int esperado) {
    int resultado = CantdePalabras(s);
    
    printf("Prueba para la frase %s: ", s);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    realizarPrueba("Prueba para la frase", 4); 
    realizarPrueba("hola", 1);  
    realizarPrueba("", 0);  
    realizarPrueba("a a a a a a ", 6); 

    return 0;
}