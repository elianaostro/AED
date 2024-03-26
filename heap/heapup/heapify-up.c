#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(int arr[], int index) {
    while (arr[index]>arr[(index-1)/2]){
        swap(&arr[index],&arr[(index-1)/2]);
        index = (index-1)/2;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
   int n = 7;
    int* heap = calloc(n, sizeof(int));
    heap[0] = 30;
    heap[1] = 25;
    heap[2] = 20;
    heap[3] = 15;
    heap[4] = 10;
    heap[5] = 5;

    int new_element = 21;
    heap[6] = new_element;

    heapify_up(heap, n - 1);

    printf("Heap después de insertar %d:\n", new_element);
    printArray(heap, n);
    
    free(heap);

    return 0;
}
