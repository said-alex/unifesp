#### UC Sistemas Operacionais (ADE) - ICT/UNIFESP
___
Prof. Bruno Kimura
bruno.kimura@unifesp.br

###### Objetivo:
Implementar um interpretador de comandos em terminal para Linux.

###### Entregáveis:
• Protótipo em arquivos .c
• Vídeo-apresentação.

###### Observação:
A autenticidade do trabalho será verificada.
Cópias (entre grupos e/ou de fontes da Internet) implicam em anulação.

###### Requisitos do protótipo
O interpretador de comandos deverá:

1. Executar comandos unitários, com múltiplos parâmetros. Exemplo:<br>
`ls -la`

2. Executar comandos encadeados, utilizando o operador pipe “|” para combinar saída e entrada entre os comandos. Exemplo:<br>
`ls -la | grep “teste”`<br>
`cat /proc/cpuinfo | grep "model name" | wc -l`

3. Executar sequências de comandos independentes com o operador “;”. Exemplo:<br>
`echo “SO 2021” ; echo “ADE Viva!”`

4. Executar comandos condicionados com operadores OR (||) e AND (&&). Exemplo:<br>
`cat 12345 || echo "aquivo inexistente"`<br>
`ping -c1 www.unifesp.br.br && echo "SERVIDOR DISPONIVEL" || echo "SERVIDOR INDISPONIVEL"`

5. Executar comandos em background, liberando o shell para receber novos comandos do usuário. Exemplo:<br>
`ping -c5 www.unifesp.br &`

###### Video-apresentação.
O vídeo deverá:

1. Apresentar explicação do trabalho desenvolvido: o que, como e porque foi feito da forma como foi. Atentem-se: <br>
(a) TODOS os integrantes do grupo devem apresentar;
<br>
(b) o tempo de exposição de vídeo é em torno de 20min e deve ser dividido de forma igualitária, por exemplo, em um grupo de 3 alunos, cada teria entre 6min e 7min de fala.

2. Descrever de forma objetiva as contribuições de cada integrante do grupo no trabalho.

3. Apresentar uma auto-avaliação do grupo sobre o trabalho realizado.
