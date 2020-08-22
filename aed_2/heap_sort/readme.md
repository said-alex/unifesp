# Problema 4 - Heapsort
Tempo limite: 0.5s (C)

Implemente o algoritmo de ordenação HeapSort, conforme
especificado nos slides e video-aula (de acordo com o livro T. Cormen).
Escreva um procedimento separado para as seguintes operações:

a) maxheapfy(…)
b) build-max-heap(…)
c) heap-extract-max(…)
d) heapSort(…)

# Entrada

A entrada consiste de duas linhas, sendo a primeira contendo um número
inteiro N (1 ≤ N ≤ 10.000) que especifica a quantidade de valores do arranjo original a
serem ordenados.
A segunda linha contém uma sequência de números inteiros separados por
espaços, onde cada número inteiro Ai pode estar na faixa: 0 ≤ Ai ≤ 10.000,
correspondendo ao arranjo original a ser ordenado.

# Saída

A saída consiste de duas linhas, sendo a primeira o vetor rearranjado após a
chamada a rotina build-max-heap(…). A segunda linha corresponde ao vetor final
devidamente ordenado.
___
Exemplo de Entrada 1

4
8 5 6 7

Exemplo de Saída 1

8 7 6 5
5 6 7 8
___
Exemplo de Entrada 2

10
10 2 4 5 8 5 6 7 11 20

Exemplo de Saída 2

20 11 6 10 8 5 4 7 5 2
2 4 5 5 6 7 8 10 11 20
