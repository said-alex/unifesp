#include <iostream>

using namespace std;

void merge_sort(int[], int, int);
void merge(int[], int, int, int);

int main() {
  int ary[] = {9,5,4,2,8,7,3,6,1};

  merge_sort(ary, 0, 8);

  for (int i = 0; i < 9; i++)
    cout << ary[i] << " ";

  return 0;
}

void merge_sort(int ary[], int l_index, int r_index)
{
  if (l_index >= r_index) return;

  int m_index = (l_index + r_index) / 2;

  merge_sort(ary, l_index, m_index);
  merge_sort(ary, (m_index + 1), r_index);
  merge(ary, l_index, m_index, r_index);
}

void merge(int ary[], int l_index, int m_index, int r_index) {
  int first_half_size = m_index - l_index + 1;
  int sec_half_size = r_index - m_index;

  int *l_ary = new int[first_half_size*sizeof(int)];
  int *r_ary = new int[sec_half_size*sizeof(int)];

  for (int i = 0; i < first_half_size; i++) l_ary[i] = ary[l_index + i];
  for (int j = 0; j < sec_half_size; j++) r_ary[j] = ary[m_index + 1 + j];

  int i, j = 0, k = l_index;

  while (i < first_half_size && j < sec_half_size) {
    if (l_ary[i] <= r_ary[j]) {
      ary[k] = l_ary[i];
      i++;
    }
    else {
      ary[k] = r_ary[j];
      j++;
    }

    k++;
  }

  while (i < first_half_size) {
    ary[k] = l_ary[i];
    i++;
    k++;
  }

  while (j < sec_half_size) {
    ary[k] = r_ary[j];
    j++;
    k++;
  }

  delete l_ary;
  delete r_ary;
}
