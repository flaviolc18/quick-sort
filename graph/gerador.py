#!/usr/bin/python3
import numpy as np
import random
import math
import sys

if len(sys.argv) < 3:
    print("usage: python {} [numero_vertices] [numero_instrucoes]".format(sys.argv[0]))
    exit(2)

N = int(sys.argv[1])
I = int(sys.argv[2])

# Temos idades variando de 1 a 100, cada vértice é representado por uma idade e é garantido que não existem vértices com idades repetidas, logo temos no máximo 100 vértices
if(N > 100 or N <= 0):
    print("0 < numero_vertices <= 100")
    exit(2)

# O número mínimo de arestas possíveis ocorre quando o grafo é
# minimamente conectado, e é `N-1`. O número máximo -- lembrando que o
# grafo é um grafo acíclico dirigido (DAG) -- ocorre quando todo vértice
# possui uma aresta a todos os outros vértices à sua frente na ordenação
# topológica, e é `N * (N - 1) / 2`.
M = random.randint(N - 1, N * (N - 1) / 2)

print(N, M, I)

# `random.sample` retorna uma lista de inteiros _únicos_.
idades = random.sample(range(1, 101), N)
print(" ".join(str(x) for x in idades))

# Todas as arestas possiveis do grafo, respeitando uma ordenação
# topológica arbitrária. No caso, a ordenação topológica é crescente,
# i.e., uma aresta de x para y só pode existir se x < y.
possiveis = np.vstack([
    np.array([(i, j) for j in range(i + 1, N)])
    for i in range(N - 1)
])

# Seleciona M arestas aleatórias, sem repetição. Também garante que as
# selecionadas estejam em uma ordem aleatória.
np.random.shuffle(possiveis)
arestas = possiveis[:M]

# Estamos mapeando os valores dos vértices para uma permutação
# aleatória. Isso torna a ordenação topológica que antes era crescente
# numa ordenação aleatória.
mapeamento = np.random.permutation(N)
arestas = list(map(
    lambda x: (mapeamento[x[0]]+1, mapeamento[x[1]]+1),
    arestas
))

for a in arestas:
    print(a[0], a[1])

# Sempre geramos uma única instrução MEETING
n_meeting = 1

# Aqui procuramos distribuir o número de instruções uniformemente entre as 2 restantes, porém, respeitando os limites da quantidade de vértices
# Usamos, para a instrução COMMANDER, o mínimo entre a quantidade de vértices e a metade das instruções restantes
n_commander = math.ceil(min((I-n_meeting)/2, N))

# O restante é usado para a instrução SWAP
n_swap = I - n_meeting - n_commander

# Para o SWAP, pegamos sempre arestas existentes para exercitar a complexidade do algoritmo implementado, pois, caso contrário, a instrução é executada em O(1)
for i in range(n_swap):
    v1, v2 = random.choice(arestas)
    print('S {} {}'.format(v1, v2))

# Escolha de um vértice aleatório para a instrução COMMANDER
for i in range(n_commander):
    v = random.randint(1, N)
    print('C {}'.format(v))

for i in range(n_meeting):
    print('M')
