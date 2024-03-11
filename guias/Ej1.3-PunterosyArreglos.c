#include <stdio.h>
#include <stdbool.h>

void myFunc(int* a, int b){
    (*a)++;
    b++;
}

int main(){
    int a = 10;
    int b = 10;
    myFunc(&a, b);
    printf("%d %d\n", a, b); //a = 11, b = 10
    return 0;
}