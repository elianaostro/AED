def validar_resultado(resultado, expected):
    if(resultado == expected): 
        return "Passed"
    return "Failed"

def validar_parentesis(secuencia):
    lista = []
    for char in secuencia:
        if char == "(":
            lista.append(1)
        elif char == ")":
            if lista.__len__()==0:
                return False
            lista.pop(-1)
    return True

# Ejemplos
print(validar_resultado(validar_parentesis("()"),True))       # True
print(validar_resultado(validar_parentesis("(()())"), True))   # True
print(validar_resultado(validar_parentesis(")(())"), False))     # False
print(validar_resultado(validar_parentesis("())"), False))