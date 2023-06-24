#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define INPUT_LINES 300

int map_char_to_priority(char c) {
  // a == 97, we map it to 1, so we substract 96 to get 1
  // A == 65, we map it to 27, so we substract 38 to get 27
  if (c == '\0' || c == '\n') {
    return 0;
  }
  if (c >= 'a' && c <= 'z') {
    // printf("[INFO] Char = %c => %d\n", c, ((int)c - 96));
    return ((int)c) - 96;
  } else if (c >= 'A' && c <= 'Z') {
    return ((int)c) - 38;
  }
  printf("[ERROR] Invalid input, char == [ %c ] found, exiting\n", c);
  exit(1);
}

/*
 * We are counting every char in string & hence reach limit == 3
 * What we need to do is increment by 1 per STRING, so we need 3 separate passes
 * on the same table
 */
int increment_table(char *str, int *table) {
  int temp[53] = {0};
  int len = strlen(str); // strlen() doesn't count \n or \0
  if (len == 0) {
    return 0;
  }
  int char_to_i = 0;
  for (int i = 0; i < len; i++) {
    char_to_i = map_char_to_priority(str[i]);
    if (char_to_i == 0) {
      continue;
    }
    if (char_to_i > 52) {
      printf("[ERROR] Found char outside of 0 -> 52 bound. Char value == [%d], "
             "exiting\n",
             char_to_i);
      exit(1);
    }
    if (temp[char_to_i] == 0) {
      temp[char_to_i] = 1;
      table[char_to_i] += 1;
    }
    if (table[char_to_i] == 3) {
      printf("[INFO] Found common char = [ %d ] \n", char_to_i);
      return char_to_i;
    }
  }
  for (int y = 0; y <= 53; y++) {
    printf("%d", table[y]);
  }
  printf("\n");
  return 0;
}

int get_common_char(char *str) {
  int len = strlen(str); // strlen() doesn't count \n or \0
  if (len == 0) {
    return '\0';
  }
  int middle = len / 2; // middle points at the first char of second half
  printf("[INFO] Middle point is == [ %d ] for string of length == [ %d ]\n",
         middle, len);
  int first_half[53] = {0}; // 52 is max number of expected chars that we can
                            // find in supplied input
  // iterate over first half & populate fields
  for (int i = 0; i < middle; i++) {
    int char_to_i = map_char_to_priority(str[i]);
    if (char_to_i > 52) {
      printf("[ERROR] Found char outside of 0 -> 52 bound. Char value == [%d], "
             "exiting\n",
             char_to_i);
      exit(1);
    }
    first_half[char_to_i] = 1;
  }
  // find the matching char (corresponding vlaue)
  for (int j = middle; j < len; j++) {
    int char_to_i = map_char_to_priority(str[j]);
    if (first_half[char_to_i] == 1) {
      printf("[INFO] Found a common char, value == [ %d ]\n", char_to_i);
      return char_to_i;
    }
  }
  printf("[ERROR] Did not find common char, exiting\n");
  exit(1);
}

int calculate_security_badge_priorities_sum(char *file_name) {
  FILE *fh = fopen(file_name, "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  int table[53] = {0};
  int i = 0;
  int sum = 0;
  while (fgets(buffer, buffer_size, fh)) {
    sum += increment_table(buffer, table);
    i++;
    if (i % 3 == 0) {
      memset(table, 0, 53 * sizeof(int));
      i = 0;
    }
  }
  return sum;
}

int calculate_sum_of_priorities(char *file_name) {
  FILE *fh = fopen(file_name, "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  char common_chars[INPUT_LINES] = {0};
  int i = 0;
  size_t sum = 0;
  while (fgets(buffer, buffer_size, fh)) {
    sum += get_common_char(buffer);
    i++;
  }
  return sum;
}

int main() {
  assert(calculate_sum_of_priorities("sample_input") == 157);
  assert(calculate_sum_of_priorities("input") == 7997);
  assert(calculate_security_badge_priorities_sum("sample_input") == 70);
  assert(calculate_security_badge_priorities_sum("input") == 2545);
}
