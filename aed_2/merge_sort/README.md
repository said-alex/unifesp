# Problema 2 - AED2 - 2020 - Eleições otimizadas
(Tempo Limite de execução do programa: 0,5 s)

Em tempo de crise, tal qual ocorre no momento com o Covid-19, tudo que compõe orçamento de
governos e instituições deve ser repensando para redução de gastos. Eleições em muitos lugares do mundo são
realizadas em 2 turnos, entretanto, pode-se gerar alguma economia de recursos se puderem ser realizadas em
apenas 1 turno. Porém, a não realização de um segundo turno tem o potencial de eleger um candidato que tenha
um alto percentual de rejeição e que possivelmente não ganharia um segundo turno.

Com o objetivo de tornar eleições com 2 turnos mais econômica, uma universidade está propondo um
procedimento inovador para eleição de reitor para ser realizado em um único dia, onde cada eleitor pode votar em
até 3 candidatos, em ordem de sua preferência, ou seja, o primeiro candidato escolhido é o de maior preferência, e
assim sucessivamente. Para contabilização de votos no primeiro turno apenas os votos em primeira opção são
contabilizados. Caso não haja vencedor no primeiro turno com pelo menos 50% dos votos válidos, um segundo
turno virtual é realizado entre os 2 primeiros candidatos mais votados na eleição de primeiro turno sem realizar
outra consulta, onde, a escolha em qualquer das 3 opções feitas pelos eleitores pode ser contabilizada como um
único voto válido para o segundo turno.

Em uma eleição com C candidatos, cada candidato possui um número único entre 1 e C. Qualquer voto
com valor menor do que 1 ou maior do que C é considerado como voto inválido. Para um candidato vencer no
primeiro turno, ele precisa conquistar pelo menos 50% dos votos válidos. Uma eleição sem nenhum voto válido
no primeiro turno não possui um resultado válido. Empates em número de votos são resolvidos de acordo com o
número dos candidatos. Se dois candidatos empatarem em qualquer um dos turnos, a ordem entre esses candidatos
na classificação é definida de acordo com a ordem crescente dos números desses candidatos (considera-se que o
candidato de menor número é o de maior idade e, portanto, de maior prioridade).

Caso nenhum candidato tenha conquistado pelo menos 50% dos votos em primeira opção, então um
segundo turno virtual é realizado. No segundo turno, o voto de cada eleitor pode ser contabilizado no máximo
uma vez. Se o eleitor não votou em nenhum dos 2 candidatos que disputam o segundo turno em nenhuma das 3
opções, então o seu voto não é computado como voto válido no segundo turno. Caso contrário, o voto de sua
maior preferência em algum candidato que concorre no segundo turno é contado como voto válido ao candidato
escolhido. Por exemplo, em um segundo turno disputado entre os candidatos 2 e 3, se um eleitor votou nos
candidatos 1 2 3, então o seu voto vai para o candidato 2 apenas, pois, em caso do candidato 1 não passar do
primeiro turno, considera-se que o eleitor escolheria o candidato 2 em um segundo turno com a participação do
candidato 2 e qualquer outro candidato.

A sua tarefa é escrever um programa que realize a contagem de votos em até 2 turnos conforme as regras
propostas das eleições econômicas.

# Entrada

A primeira linha de um caso de teste contém os inteiros V (1 ≤ V ≤ 10.000), indicando o número de
eleitores votantes, e C, indicando o número de candidatos (1 ≤ C ≤ 100). Nas próximas V linhas, são apresentados
os votos de cada eleitor votante. Em cada uma dessas linhas, são fornecidos 3 inteiros com as escolhas, em ordem
de preferência, de um eleitor.

# Saída

Caso não haja nenhum voto válido em primeira opção, imprima apenas o número 0. Caso contrário, o seu
programa deve imprimir na primeira linha da saída o número do candidato vencedor do primeiro turno e a
porcentagem de votos com 2 dígitos de precisão, separados por um espaço em branco. Caso o vencedor do
primeiro turno tenha vencido com menos de 50% dos votos válidos, você deve imprimir na segunda linha o
número do vencedor do segundo turno e sua porcentagem de votos com 2 dígitos de precisão, separados por um
espaço em branco. Para os cálculos da porcentagens, deve-se considerar apenas os votos válidos.

# Exemplos

Entrada
10 3
1 2 3
1 2 4
2 1 4
2 3 1
3 2 1
3 2 1
1 3 2
4 3 2
2 1 3
1 2 4

Saída
1 44.44
2 60.00

Entrada
7 5
4 2 3
3 5 6
3 2 1
2 3 4
3 2 1
3 2 1
2 3 1

Saída
3 57.14

Entrada
5 3
4 4 4
4 4 4
4 4 4
4 4 1
4 4 4

Saída
0