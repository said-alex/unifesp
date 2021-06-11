#include <iostream>

using namespace std;

void merge_sort(int[], int, int, int[]);
void merge(int[], int, int, int, int[]);
void print_ary(int[], int);

int N;
int K;
int k;

int main() {
  cin >> N;
  cin >> K;
  int ary[N];
  int ary2[N];

  for (int i = 0; i < N; i++) cin >> ary[i];

  merge_sort(ary, 0, 4, ary2);

  cout << K << endl;

  return 0;
}

void print_ary(int ary[], int len) {
  for (int i = 0; i < len; i++)
    cout << ary[i] << " ";

  cout << endl;
}

void merge_sort(int vetor[], int inicio, int fim, int vetorAux[]) {
  if ((inicio < fim) and (vetor[inicio] > (K * vetor[fim]))) k++;
  if ((fim - inicio) < 2) return;


  int meio = ((inicio + fim)/2);

  merge_sort(vetor, inicio, meio, vetorAux);
  merge_sort(vetor, meio, fim, vetorAux);
  merge(vetor, inicio, meio, fim, vetorAux);
}

void merge(int vetor[], int ini, int meio, int fim, int vetAux[]) {
  int esq = ini;
  int dir = meio;

  for (int i = ini; i < fim; ++i) {
    if ((esq < meio) and ((dir >= fim) or (vetor[esq] < vetor[dir]))) {
        vetAux[i] = vetor[esq];
        ++esq;
    }
    else {
        vetAux[i] = vetor[dir];
        ++dir;
    }
  }

  for (int i = ini; i < fim; ++i) {
    vetor[i] = vetAux[i];
  }
}
