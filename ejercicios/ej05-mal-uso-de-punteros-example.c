#include <stdio.h>


/* 
// * EJEMPLO 1
// * Intentar acceder al valor apuntado por un puntero no inicializado
// */
int main() {
    int *ptr;
    ptr = (int*)10;
    printf("%p", ptr);
    return 0;
}


/* 
* EJEMPLO 2
* Desreferenciar un puntero no inicializado
*/

// int main() {
//     int *ptr;
//     printf("%d\n", *ptr);
//     return 0;
// }



/* 
* EJEMPLO 3
* Intentar desreferenciar el puntero después de liberar la memoria
*/
// int main() {
//     int *ptr = (int *)malloc(sizeof(int));
//     *ptr = 10;
//     printf("%d", *ptr);
//     free(ptr);
//     printf("%d\n", *ptr);
//     return 0;
// }



/* 
* EJEMPLO 4
* Intentar desreferenciar el puntero después de que su ámbito ha terminado
*/
// int *getPointer() {
//     int x = 10;
//     return &x;
// }

// int main() {
//     int *ptr = getPointer();
//     printf("%d\n", *ptr);
//     return 0;
// }