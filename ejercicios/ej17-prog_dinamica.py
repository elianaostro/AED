#fuerza bruta
w,v=[],[]
def ks(n,c):
    if(n==0 or c==0):
        return 0
    elif(w[n]>c):
        result = ks(n-1,c)
    else:
        temp1 = ks(n-1,c)
        temp2 = ks(n-1,c-w[n]) + v[n]
        result = max(temp1,temp2)
        result = max(temp1,temp2)
        return result

#programacion dinamica
wt,val=[1,2,4,2,5],[5,3,5,3,2]
def ks_dp(n,c):
    k = [[0 for x in range(c)] for x in range(n)]
    for i in range(n):
        for w in range(c):
            if wt[i] <= w:
                k[i][w] = max(val[i] + k[i-1][w-wt[i]], k[i-1][w])
            else:
                k[i][w] = k[i-1][w]
    return k[n-1][c-1]

print(ks_dp(5,5))
