#include <stdio.h>
#include <stdbool.h>

int main() {
    int x = 10;
    int* px = &x;

    printf("%d \n", px); //puntero de x
    printf("%d \n", (*px)); //10

    (*px)++;

    printf("%d \n", px);  //puntero de x + 1
    printf("%d \n", (*px)); //11

    return 0;
}

