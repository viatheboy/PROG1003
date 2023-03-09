import math

antÅr = 6
rente = 0.03
beløp = 0

def seksÅr(beløp):
    sum = 0
    i = 0
    while (i < antÅr):
        i += 1
        sum += beløp
        sum *= 1.03
        #print("Skjer det noe her?")
    return sum


for i in range(0, 20000):
    sum2 = 0
    beløp += 1
    sum2 = seksÅr(beløp)
    if (sum2 >= 100000):
        print(beløp)
        print("100 000 =", sum2)
        break




