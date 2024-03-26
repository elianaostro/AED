#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify_down(int arr[], int index, int size) {
   while (2**index<(int)(size-1)/2 && (arr[index]<arr[index*2+1] || arr[index]<arr[index*2+2])){ //esta mal la comparacion
        if (arr[index*2+1] < arr[index*2+2]){
            swap(&arr[index],&arr[index*2+2]);
            index = index*2+2;
        }
        swap(&arr[index],&arr[index*2+1]);
        index = index*2+1;
    }
}

int extract_max(int arr[], int *n) {
    if (*n <= 0) return -1; 
    int max = arr[0]; 
    arr[0] = arr[*n - 1]; 
    (*n)--;
    heapify_down(arr, 0, *n); 
    return max;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int heap[] = {30, 25, 20, 15, 10, 5}; 
    int n = sizeof(heap) / sizeof(heap[0]); 

    int extracted_element = extract_max(heap, &n);

    printf("Elemento extraído: %d\n", extracted_element);
    printf("Heap después de extraer el primer elemento:\n");
    printArray(heap, n);

    return 0;
}
