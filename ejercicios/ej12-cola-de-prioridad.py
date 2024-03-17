'''  arbol binario
de raiz a hojas
altura(h) es la cantidad de niveles(j)
cant max por nivel es 2^(h-j)
arbol completo izq/der
    se completa el nivel y el siguiente se empieza por la izquierda hasta completar cada hoja y se pasa el sig y vuelve a empezar
se puede escribir como lista 
[0, 01, 02, 011, 012, 021, 022, ... ]

padre(i)= (i - 1) / 2
hijo izq (i) = (i * 2) + 1
hijo der (i) = (i * 2) + 2
max nodos altura h: 2^(h+1) -1
min nodos altura h: 2^h
Nodos(n)
2^h <= n <= 2^(h+1) -1
'''

''' Heaps
def: es un arbol binario completo a izq que cumple la propiedad de heap
prop: el padre siempre es mayor a sus hijos
'''


def insert(heap,valor):
    head -> arr[head -> cant] = valor
    heapup (heap -> arr, heap -> cant)
    heap -> cant++
    return

get_max()
def remove_max(heap): #O(log(n))
    swap(heap -> arr, 0, hep -> cant)
    heap -> cant --
heap_down(heap -> arr, 0)

create()
destroy()

build(arr) -> heap

#propio del heap
def heapup(arr, i): #O(log(n)) ~ h+1
    if arr[(i-1)/2]<arr[i]:
        swap(arr,(i-1)/2,i)
        return heapup(arr,(i-1)/2)
    
def heapdown(arr, i): #O(log(n))
    pos_hi=(i*2)+1
    pos_hd=(1*2)+2
    if arr[pos_hi]<arr[poss_hd]:
        swap(arr,i,pos_hi)
        heapdown(arr,pos_hi)
    else:
        ...
    return
