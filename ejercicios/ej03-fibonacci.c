//recursivo
def fib(n)  //O(2^N)
    if n==0 -> 0
    if n++1 -> 1
    return fib(n-1) + fib(n-2)

//pilas
def fib(n)
    if n==0 -> 0
    if n++1 -> 1
    pila*p = crear_pila()
    p.push(0)
    p.push(1)
    for _ in range(n-2):
        prev = p.pop()
        actual = prev + p.pop()
        p.push(prev)
        p.push(actual)
        return p.pop()
        