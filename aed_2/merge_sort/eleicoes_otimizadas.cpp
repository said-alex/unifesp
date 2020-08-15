#include <iostream>
#include <cstdlib>

#define NUM_OF_ROUNDS 3

using namespace std;

void print_aray(int[], int);
void merge_sort(int[], int, int);
void merge(int[], int, int, int);
void start_election(int, int);
int  validate_vote(int, int);
int  perform_first_round(int[], int);
int  perform_second_round(int[], int[], int[], int);

int main() {
  int num_of_electors, num_of_candidates;

  cin >> num_of_electors;
  cin >> num_of_candidates;

  start_election(num_of_electors, num_of_candidates);

  return 0;
}

void print_aray(int ary[], int size) {
  cout << endl;
  for (int i = 0; i < size; i++)
    cout << ary[i] << " ";
}

void start_election(int num_of_electors, int num_of_candidates) {
  int first_vote, second_vote, third_vote;

  int *first_option_votes = new int[num_of_electors*sizeof(int)];
  int *sec_option_votes   = new int[num_of_electors*sizeof(int)];
  int *third_option_votes = new int[num_of_electors*sizeof(int)];

  for (int i = 0; i < num_of_electors; i++) {
    cin >> first_vote;
    cin >> second_vote;
    cin >> third_vote;

    first_option_votes[i] = validate_vote(first_vote,  num_of_candidates);
    sec_option_votes[i]   = validate_vote(second_vote, num_of_candidates);
    third_option_votes[i] = validate_vote(third_vote,  num_of_candidates);
  }

  merge_sort(first_option_votes, 0, (num_of_electors - 1));
  merge_sort(sec_option_votes,   0, (num_of_electors - 1));
  merge_sort(third_option_votes, 0, (num_of_electors - 1));

  if(!perform_first_round(first_option_votes, num_of_electors))
    perform_second_round(
      first_option_votes,
      sec_option_votes,
      third_option_votes,
      num_of_electors
    );
}

int validate_vote(int vote, int num_of_candidates) {
  vote > 0 && vote <= num_of_candidates ? vote : 0;
}

int perform_first_round(int f_option_votes[], int num_of_electors) {
  int most_voted_candidate, total_votes = 0;
  int tmp_most_voted_candidate = f_option_votes[0];

  for (int i, tmp_total_votes = 1; i < num_of_electors; i++) {
    if (f_option_votes[i] == tmp_most_voted_candidate) {
      tmp_total_votes++;
      continue;
    }
    else if (tmp_total_votes > total_votes) {
      most_voted_candidate = tmp_most_voted_candidate;
      total_votes = tmp_total_votes;
    }

    tmp_most_voted_candidate = f_option_votes[i];
    tmp_total_votes = 1;
  }

  float percent_of_votes = 100*(total_votes / (float)num_of_electors);

  if (most_voted_candidate == 0) {
    cout << most_voted_candidate;
    exit(0);
  }

  cout << fixed;
  cout.precision(2);
  cout << most_voted_candidate << " " << percent_of_votes;

  return percent_of_votes >= 50.0 ? true : false;
}

int perform_second_round(int f_opt_votes[], int s_opt_votes[], int t_opt_votes[], int num_of_candidates) {
  /* PROGRAMAR EM C É TOTALMENTE IMPRODUTIVO ATUALMENTE */
}

void merge_sort(int ary[], int l_index, int r_index) {
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
