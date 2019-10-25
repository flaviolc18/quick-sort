import numpy as np
import random
import math
import sys

if len(sys.argv) < 2:
    print("usage: python {} [numero_ilhas]".format(sys.argv[0]))
    exit(2)

N = int(sys.argv[1])
M = N*100

possiveis_custos = [i*10 for i in range(1, N+1)]
possiveis_pontuacoes = [i for i in range(1, N+1)]


custos = random.choices(possiveis_custos, k=N)
pontuacoes = random.choices(possiveis_pontuacoes, k=N)

print(M, N)
# for i in range(N):
#     print(custos[i], pontuacoes[i])
