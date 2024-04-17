

def mergeArrays1(arrays):
    mergedArray = []
    currentMin = 0
    i=0
    while not arrays.isEmpty():
        for array in arrays:
            if array[i]< arrays[currentMin][i]:
                currentMin = array
        mergedArray.push(currentMin.pop())
        if(currentMin.isEmpty()):
            arrays.remove(array)
        i+=1


# [3]
# [3,4]
# [3,4,5]
# [7,8,9]
# [2000]

def mergeArrays2(arrays):
    mergedArray = []
    while(arrays.isNotEmpty):
        currentMinArray = arrays[0]
        currentMin = arrays[0][0]
        for array in arrays: 
            if(array[0]< currentMin):
                currentMin = array[0]
                currentMinArray = array
        mergedArray.push(currentMinArray.pop())
        if(currentMinArray.isEmpty()): 
            arrays.remove(array)


def removeRepeatedElements1(lista):
    auxLista = ListaSimple()
    nodo = lista.getHead()
    while nodo:
        if auxLista.getTail() != nodo:
            auxLista.insetLast(nodo)
        nodo = nodo.getNext()

def removeRepeatedElements2(lista):
    nodo = lista.getHead()
    while nodo.getNext():
        sig = nodo.getNext()
        if nodo == sig:
            nodo.changeNext(sig.getNext())
            sig.delete()
        else:
            nodo = sig

# (1,2,2,3,4,4,4,5) debería quedar (1,2,3,4,5). 

def removeRepeatedElements3(lista):
    auxList = ListaSimplementeEnlazada()
    nodo = lista.getHead()
    while nodo:
        if(auxList.getTail() != nodo):
            auxList.insertLast(nodo)
        nodo = nodo.getNext()

