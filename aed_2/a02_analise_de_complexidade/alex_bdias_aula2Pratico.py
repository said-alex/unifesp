P = 0
M = 1
F = 2
Q = 3
B = 4

def foo(livros, tam, conjunto_de_somas = [], col1 = 0, col2 = 1):
  print(col1, col2)
  if (col1 + 1) == tam and col2 == tam:
    return conjunto_de_somas

  soma = valor_do_conjunto_de_livros([livros[P][col1], livros[M][col1], livros[F][col1], livros[Q][col1], livros[B][col1]])

  if soma not in conjunto_de_somas:
    conjunto_de_somas = inserir_em_ordem_decrescente(soma, conjunto_de_somas)

  soma = valor_do_conjunto_de_livros([livros[P][col2], livros[M][col2], livros[F][col2], livros[Q][col2], livros[B][col2]])

  if soma not in conjunto_de_somas:
    conjunto_de_somas = inserir_em_ordem_decrescente(soma, conjunto_de_somas)

  conjunto_de_somas = somas_dos_conjuntos_mais_caros_tomados_2_a_2(
    [livros[P][col1], livros[M][col1], livros[F][col1], livros[Q][col1], livros[B][col1]],
    [livros[P][col2], livros[M][col2], livros[F][col2], livros[Q][col2], livros[B][col2]],
    conjunto_de_somas,
  )

  if (col2 + 1) == tam:
    col1 += 1
    return foo(livros, tam, conjunto_de_somas, col1, col1 + 1)
  else:
    return foo(livros, tam, conjunto_de_somas, col1, col2 + 1)

########################

def somas_dos_conjuntos_mais_caros_tomados_2_a_2(livros1, livros2, conjunto_de_somas = [], i = 0): # O(10)
  if i == len(livros1) or i == len(livros2): return conjunto_de_somas

  if livros1[i] > livros2[i]:
    livros1_cpy = livros1.copy()
    livros1_cpy[i] = livros2[i]
    soma = valor_do_conjunto_de_livros(livros1_cpy) # O(5)

    if soma not in conjunto_de_somas:
      conjunto_de_somas = inserir_em_ordem_decrescente(soma, conjunto_de_somas) # O(s)

  return somas_dos_conjuntos_mais_caros_tomados_2_a_2(livros1, livros2, conjunto_de_somas, i + 1)

#########################

def valor_do_conjunto_de_livros(livros): # O(5)
  valor_do_conjunto = 0

  for valor_do_livro in livros:
    valor_do_conjunto += valor_do_livro

  return valor_do_conjunto

#########################

def inserir_em_ordem_decrescente(soma, conjunto_de_somas): # O(len(somas))
  conjunto_aux = []

  for s in conjunto_de_somas:
    if soma > s:
      conjunto_aux.append(soma)
      aux = s
      s = soma
      soma = aux
    else: conjunto_aux.append(s)

  conjunto_aux.append(soma)

  return conjunto_aux

########################

livros = [
  [8, 6, 5, 3, 2],
  [9, 6, 5, 3, 1],
  [8, 6, 5, 4, 2],
  [9, 5, 4, 3, 2],
  [8, 7, 5, 4, 1],
]

tam = len(livros[P])

# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:1] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:2] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:3] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:4] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:5] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:6] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:7] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:8] ))
# print(valor_do_conjunto_de_livros( foo(livros, tam)[0:9] ))
print(valor_do_conjunto_de_livros( foo(livros, tam)[0:10] ))
