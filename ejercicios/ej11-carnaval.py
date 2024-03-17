class Queue:
    def __init__(self):
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        if self.is_empty():
            return None
        return self.items.pop(0)

    def size(self):
        return len(self.items)
    
    def enqueuetodo(self, queue):
        while not queue.is_empty():
            item = queue.dequeue()
            self.enqueue(item)
    


def OrdenarCarnaval(llegada,salida):
    calle = Queue()
    esperado = 1
    while not llegado.is_empty() or not calle.is_empty():
        calleFirst = calle.first()
        if :
        
        else:
            colaFirst = llegada.dequeue()
            if colaFirst == esperado:
                salida.enqueue()
                esperado+=1
            else:
                if colaFirst > calle.first():
                    return -1
                calle.push(colaFirst)
    return 0




