#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* item;
  int lenght;
} Array;

void build_max_heap(Array*);
int  heap_extract_max(Array*);
void heap_sort(Array*);
void max_heapfy(Array*, int);
void print_ary(Array*);
void swap(Array*, int, int);

int main() {
  Array ary;

  scanf("%d", &ary.lenght);

  ary.item = malloc(ary.lenght * sizeof(int));

  int i;
  for (i = 0; i < ary.lenght; i++)
    scanf("%d", &ary.item[i]);

  heap_sort(&ary);
  free(ary.item);

  return 0;
}

void heap_sort(Array* ary) {
  Array aux_ary;
  aux_ary.lenght = ary->lenght;
  aux_ary.item = ary->item;
  ary->item = malloc(ary->lenght * sizeof(int));

  build_max_heap(&aux_ary);
  print_ary(&aux_ary);

  int i;
  for (i = (ary->lenght - 1); i > -1; i--)
    ary->item[i] = heap_extract_max(&aux_ary);

  print_ary(ary);
  free(aux_ary.item);
}

void build_max_heap(Array* ary) {
  int i;
  for (i = ((ary->lenght / 2) - 1); i >= 0; i--)
    max_heapfy(ary, i);
}

int heap_extract_max(Array* ary) {
  if (ary->lenght < 0)
    exit(1);

  int max = ary->item[0];
  int last = ary->lenght - 1;

  ary->item[0] = ary->item[last];
  ary->lenght--;

  max_heapfy(ary, 0);

  return max;
}

void max_heapfy(Array* ary, int i) {
  int left = (2 * i) + 1;
  int right = (2 * i) + 2;
  int max = i;

  if ((left < ary->lenght) && (ary->item[left] > ary->item[i]))
    max = left;

  if ((right < ary->lenght) && (ary->item[right] > ary->item[max]))
    max = right;

  if (max != i) {
    swap(ary, i, max);
    max_heapfy(ary, max);
  }
}

void swap(Array* ary, int i1, int i2) {
  int temp = ary->item[i1];
  ary->item[i1] = ary->item[i2];
  ary->item[i2] = temp;
}

void print_ary(Array* ary) {
  int i;
  for (i = 0; i < ary->lenght; i++)
    printf("%d ", ary->item[i]);

  puts("");
}
