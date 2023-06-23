#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

#define INPUT_LINES 300
// divide in half
// find common char (only one?)
// map common char to int
// sum

char get_common_char(char *str) {
  int len = strlen(str); // strlen() doesn't count \n or \0
  if (len == 0) {
    return '\0';
  }
  int middle = len / 2; // middle points at the first char of second half
  printf("[INFO] Middle point is == [ %d ] for string of length == [ %d ]\n",
         middle, len);
  for (int i = 0; i < middle; i++) {
    char char_i = str[i];
    for (int j = middle; j < len; j++) {
      char char_j = str[j];
      if (char_i == char_j) {
        return char_i;
      }
    }
  }
  printf("[ERROR] Did not find common char, exiting\n");
  exit(1);
}

int map_char_to_priority(char c) {
  // a == 97, we map it to 1, so we substract 96 to get 1
  // A == 65, we map it to 27, so we substract 38 to get 27
  if (c == '\0') {
    return 0;
  }
  if (c >= 'a' && c <= 'z') {
    return ((int)c) - 96;
  } else if (c >= 'A' && c <= 'Z') {
    return ((int)c) - 38;
  }
  printf("[ERROR] Invalid input, char == [ %c ] found, exiting\n", c);
  exit(1);
}
int calculate_sum_of_priorities(char *file_name){
  FILE *fh = fopen(file_name, "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  char common_chars[INPUT_LINES] = {0};
  int i = 0;
  while (fgets(buffer, buffer_size, fh)) {
    char cc = get_common_char(buffer);
    common_chars[i] = cc;
    i++;
  }
  size_t sum = 0;
  for (int i = 0; i < INPUT_LINES; i++) {
    sum += map_char_to_priority(common_chars[i]);
  }
  return sum;
}

int main() {
  assert(calculate_sum_of_priorities("sample_input") == 157);
  assert(calculate_sum_of_priorities("input") == 7997);
}
