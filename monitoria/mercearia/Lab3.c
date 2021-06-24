/* Programa: Lab3
   Autor: Guilherme Ribeiro
   Versao: 1.0 - 09/06/2021
*/

#include<stdio.h>
#include<stdlib.h>

 // Arquivo ListaDinEncad.h
struct produto{
    int id;
    int quantidade;
    float lucro;
    float lucrototal;
};

Lista* cria_lista();

 // Arquivo ListaDinEncad.c
struct elemento{
    struct produto dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
typedef struct elemento* Lista;

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = Null;
    return li;
}

void inicializarLista(livro*listaAux){
    listaAux -> tamanhoLista = 0;
    for(i=0; i<100; i++)
        listaAux -> id[i] = 0;
        listaAux -> quantidade[i] = 0;
        listaAux -> lucro[i] = 0;
    listaAux -> ultimo = 0;
}

void inserirProduto(int variavel2, livro*listaAux){

    int auxId, auxQuant;
    float auxlucro;

    scanf("%d %d %.2f", &auxId, &auxQuant, &auxlucro);

    listaAux -> tamanhoLista++;

    livro[variavel2][listaAux->tamanhoLista-1] = usuario.id;
    listaAux -> ultimo = listaAux -> tamanhoLista - 1;
}

void alterarProduto(int variavel2){

}

void removerProduto(int variavel2){

}

void contabilizar(int variavel2){

}

void imprimir(){
    printf("Instrucao de saida\n");
    printf("%d %f\n", id, lucrototal);
}

produto.teste;

int main (){

    int L, variavel, variavel1, variavel2, lucro = 0;

    Lista *li; //ponteiro para ponteiro

    li = cria_lista();

    inicializarLista();

    printf("Informe a quantidade de movimentacao!\n");
    scanf("%d",&L);

    if(L > 0 && L <= 100){
        for(int i = 0; i < L; i++){
            printf("Digite 0, 1, 2, 3, 4 para acessar os comandos abaixo:\n1 - Inserir \n2 - Alterar \n3 - Remover\n4 - Contabilizar\n0 - Sair\n\n");
            scanf("%d",&variavel);

            switch(variavel){
                case 0:
                    break;
                case 1:
                    inserirproduto();
                    break;
                case 2:
                    alterarProduto();
                    break;
                case 3:
                    removerProduto();
                    break;
                case 4:
                    contabilizar();
                    break;
            }
        }
    }

    imprimir();

    system("pause");
    return 0;
}