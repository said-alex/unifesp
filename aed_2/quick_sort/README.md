# Problema 3 - AED2 - 2020/09 - Quicksort é estável?
(Tempo Limite de execução do programa: 20,0s na linguagem C)

O Quicksort é um algoritmo considerado muito rápido para a maioria das
situações. Considere o algoritmo abaixo do Quicksort, em que o pivô
escolhido como uma mediana de 3 valores, onde esse três valores devem
ser definidos como:

a) primeiro elemento do intervalo considerado do vetor
b) o elemento na posição do meio
c) o último elemento, de acordo com o pseudo-código a seguir:
___
 //Escolha do Pivo por mediana de 3<br>
 meio = (p+r)/2;<br>
 a = A[p];<br>
 b = A[meio];<br>
 c = A[r];<br>
 medianaIndice = 0; //índice da mediana (zero para inicio)<br>
 //A sequência de if...else a seguir verifica qual é a mediana<br>
 if (a < b)<br>
  if (b < c) //a < b && b < c<br>
    medianaIndice = meio;<br>
  else<br>
    if (a < c) //a < c && c <= b<br>
      medianaIndice = r;<br>
    else //c <= a && a < b<br>
      medianaIndice = p;<br>
 else<br>
  if (c < b) //c < b && b <= a<br>
    medianaIndice = meio;<br>
  else<br>
    if (c < a) //b <= c && c < a<br>
      medianaIndice = r;<br>
    else //b <= a && a <= c<br>
      medianaIndice = p;<br>
 //coloca o elemento da mediana no fim para poder usar o<br>
 //Quicksort do Cormen<br>
 trocar(A, medianaIndice, r)<br>
 //Restante do código do algoritmo de particao (Cormen)<br>
 ...<br>
 ___
Você deve implementar um programa que leia da entrada um conjunto de
informações sobre N pessoas contendo o nome de cada pessoa com até 15
caracteres e a sua idade. O seu programa deverá utilizar o algoritmo do
Quicksort com escolha do pivo por mediana de 3, conforme indicado acima,
e que ordene-os de forma crescente por idade. Posteriormente deve-se
verificar se o resultado da ordenação é estável, ou seja, se pessoas com a
mesma idade foram mantidas na mesma ordem relativa da entrada. Após a
ordenação, você deve imprimir uma região indicada da lista ordenada.

# Entrada
A primeira linha da entrada contém o número N (2 ≤ N ≤ 105.000) de pessoas a serem
ordenadas. Nas próximas N linhas são apresentados, em cada linha, um nome de até 15
caracteres e um inteiro representando a idade. A linha seguinte contém dois números P
(1 ≤ P ≤ N) da posição do primeiro nome a ser impresso e o número M (1 ≤ M ≤ N-P+1) de
pessoas a serem impressas partir do P-éssimo nome.

# Saída
Na primeira linha da saída, imprima “yes” se a ordenação for estável, ou “no”, caso
contrário. Nas próximas M linhas, imprima os M nomes e idades presentes a partir da Péssima posição da lista ordenada, uma pessoa a cada linha.
___
Exemplo de Entrada<br>
4<br>
Alex 20<br>
Gabriel 20<br>
Joana 18<br>
Rodrigo 18<br>
1 4<br>

Exemplo de Saída<br>
no<br>
Rodrigo 18<br>
Joana 18<br>
Alex 20<br>
Gabriel 20<br>
___
Exemplo de Entrada<br>
5<br>
Daniel 25<br>
Ana 21<br>
Jose 22<br>
Silvia 25<br>
Joao 23<br>
3 2<br>

Exemplo de Saída<br>
yes<br>
Joao 23<br>
Daniel 25<br>
