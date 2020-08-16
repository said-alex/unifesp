#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char name[15];
  int age;
} Person;

typedef struct {
  Person* person;
  int last;
  int lenght;
} PeopleList;

typedef struct {
  PeopleList people;
  PeopleList same_age_people_order_before;
  PeopleList same_age_people_order_after;
  int is_stable;
} QuickSortStability;

void start_quick_sort_stability_analysis(QuickSortStability*);
void set_same_age_people_order(PeopleList*, PeopleList);
void validate_quick_sort_stability(QuickSortStability*);
void init_people_list(PeopleList*, int);
void push(PeopleList*, Person);
void quick_sort(Person*, int, int);
int  partition(Person*, int, int);
void swap(Person*, int, int);
void show_people(Person*, int, int);

/* Função principal */
int main() {
  QuickSortStability quick_sort_stability;
  start_quick_sort_stability_analysis(&quick_sort_stability);

  return 0;
}

/* Inicia a análise de estabilidade do algoritmo Quick Sort */
void start_quick_sort_stability_analysis(QuickSortStability* quick_sort_stability) {
  quick_sort_stability->is_stable = 1;

  int tmp_lenght;
  scanf("%d", &tmp_lenght);

  init_people_list(&quick_sort_stability->people, tmp_lenght);

  init_people_list(
    &quick_sort_stability->same_age_people_order_before,
    tmp_lenght
  );

  init_people_list(
    &quick_sort_stability->same_age_people_order_after,
    tmp_lenght
  );

  int i;
  Person tmp_person;
  tmp_person.id = -1;
  for (i = 0; i < tmp_lenght; i++) {
    scanf("%s %d", tmp_person.name, &tmp_person.age);
    push(&quick_sort_stability->people, tmp_person);
  }

  set_same_age_people_order(
    &quick_sort_stability->same_age_people_order_before,
    quick_sort_stability->people
  );

  quick_sort(
    quick_sort_stability->people.person, 0, (quick_sort_stability->people.last)
  );

  set_same_age_people_order(
    &quick_sort_stability->same_age_people_order_after,
    quick_sort_stability->people
  );

  validate_quick_sort_stability(quick_sort_stability);

  int show_from, steps;
  scanf("%d %d", &show_from, &steps);

  if (quick_sort_stability->is_stable) puts("yes");
  else puts("no");

  show_people(quick_sort_stability->people.person, (show_from - 1), ((show_from - 1) + steps));
}

/* Inicializa a lista de pessoas */
void init_people_list(PeopleList* people, int lenght) {
  people->person = malloc(lenght*sizeof(Person));
  people->lenght = lenght;
  people->last = -1;
}

/* Adiciona um 'Person' ao final da lista determinada */
void push(PeopleList* people, Person person) {
  if (people->last >= (people->lenght - 1)) return;
  people->person[++people->last] = person;
}

/* Preenche a lista de pessoas com mesma idade na ordem em que estão dispostos na lista principal */
void set_same_age_people_order(PeopleList* same_age_people, PeopleList people) {
  PeopleList people_cpy;
  init_people_list(&people_cpy, people.lenght);

  int i;
  for (i = 0; i <= people.last; i++) {
    push(&people_cpy, people.person[i]);
  }

  int j, age_occurrence;
  for (i = 0; i <= people.last; i++) {
    for (j = (i + 1), age_occurrence = 0; j <= people.last; j++) {
      if (people_cpy.person[j].id && (people_cpy.person[i].age == people_cpy.person[j].age)) {
        push(same_age_people, people.person[j]);
        people_cpy.person[j].id = 0;
        age_occurrence++;
        same_age_people->person[same_age_people->last].id = age_occurrence;
      }
    }

    if (age_occurrence) {
      push(same_age_people, people.person[i]);
      same_age_people->person[same_age_people->last].id = age_occurrence + 1;
    }
  }
}

/* Valida a estabilidade da ordenação realizada */
void validate_quick_sort_stability(QuickSortStability* quick_sort_stability) {
  PeopleList same_age_people_order_before = quick_sort_stability->same_age_people_order_before;
  PeopleList same_age_people_order_after = quick_sort_stability->same_age_people_order_after;

  int i, j;
  for (i = 0; i <= same_age_people_order_before.last; i++) {
    for (j = 0; j <= same_age_people_order_after.last; j++) {
      if (!strcmp(same_age_people_order_before.person[i].name, same_age_people_order_after.person[j].name) &&
        same_age_people_order_before.person[i].id != same_age_people_order_after.person[j].id
      ) {
        quick_sort_stability->is_stable = 0;
        return;
      }
    }
  }
}

/* Inicio do algoritmo Quick Sort */
void quick_sort(Person* ary, int l_end_index, int r_end_index) {
  if (l_end_index >= r_end_index) return;

  int pivot_index = partition(ary, l_end_index, r_end_index);
  quick_sort(ary, l_end_index, (pivot_index - 1));
  quick_sort(ary, (pivot_index + 1), r_end_index);
}

/* Algoritmo de partição por mediana de 3 */
int partition(Person* ary, int l_end_index, int r_end_index) {
  int middle_index   = (l_end_index + r_end_index) / 2;
  Person l_end_element  = ary[l_end_index];
  Person middle_element = ary[middle_index];
  Person r_end_element  = ary[r_end_index];
  int median_index   = 0;

  if (l_end_element.age < middle_element.age)
    if (middle_element.age < r_end_element.age)
      median_index = middle_index;
    else if (l_end_element.age < r_end_element.age)
      median_index = r_end_index;
    else
      median_index = l_end_index;
  else if (r_end_element.age < middle_element.age)
    median_index = middle_index;
  else if (r_end_element.age < l_end_element.age)
    median_index = r_end_index;
  else
    median_index = l_end_index;

  swap(ary, median_index, r_end_index);

  Person pivot = ary[r_end_index];
  int pivot_index = l_end_index - 1;
  int i;

  for (i = l_end_index; i < r_end_index; i++)
    if (ary[i].age <= pivot.age) {
      pivot_index = pivot_index + 1;
      swap(ary, pivot_index, i);
    }

  swap(ary, pivot_index + 1, r_end_index);

  return pivot_index + 1;
}

/* Troca de posição dois elementos de um array */
void swap(Person* ary, int pivot, int r_end_index) {
  Person temp = ary[pivot];
  ary[pivot] = ary[r_end_index];
  ary[r_end_index] = temp;
}

/* Imprime no console a lista de pessoas */
void show_people(Person* people_list, int from, int to) {
  int i;
  for (i = from; i < to; i++) {
    printf("%s %d\n", people_list[i].name, people_list[i].age);
  }
}
