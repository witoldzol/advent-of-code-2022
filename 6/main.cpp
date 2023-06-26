#include <assert.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>

int zero_out_values(int arr[26][2], int index, int unique_count) {
  printf("[INFO] Zeroing values up to index [ %d ]\n", index);
  for (int i = 0; i < 26; i++) {
    // zero out all inserts that came before the duplicate char
    // for each find, decrement unique_count by 1
    // stop before reaching new index, it will be overwritten later on anyway
    if (arr[i][1] < index && arr[i][0] == 1) {
      arr[i][0] = 0;
      arr[i][1] = 0;
      printf("[INFO] decrementing unique_count, current value : [ %d ]\n",
             unique_count);
      unique_count--;
    }
  }
  return unique_count;
}

int find_marker(char const *file_name) {
  FILE *fh = fopen(file_name, "r");
  int buffer_size = 10240;
  char buffer[buffer_size];
  fgets(buffer, buffer_size, fh);
  int unique_count = 0;
  // there are 25 lowercase chars possible
  // first ele is flag ifDetected, second is the index where it was detected
  int unique_chars[26][2] = {0};
  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == '\n') {
      continue;
    }
    printf("[INFO] Iteration [ %d ]\n", i);
    int char_idx = ((int)buffer[i]) - 97;
    printf("[INFO] Char : [ %c ], char_idx : [ %d ]\n", buffer[i], char_idx);
    if (unique_chars[char_idx][0] == 0) {
      unique_count++;
      printf("[INFO] Incrementing unique_count = [ %d ] Char : [ %c ], "
             "char_idx : [ %d ]\n",
             unique_count, buffer[i], char_idx);
    } else {
      printf("first index of char %c at char_idx %d is %d\n", buffer[i],
             char_idx, unique_chars[char_idx][1]);
      unique_count = zero_out_values(unique_chars, unique_chars[char_idx][1],
                                     unique_count);
    }
    if (unique_count == 4) {
      printf("[INFO] Marker after char at index = %d\n", i);
      return i+1;
    }
    unique_chars[char_idx][0] = 1;
    unique_chars[char_idx][1] = i;
  }
  return 0;
}

int main() {
  assert(find_marker("sample_input") == 7);
  assert(find_marker("sample_input_2") == 5);
  assert(find_marker("input") == 1282);
}
