#include <assert.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
// bacad
//[0,0,0,0]
/*
 * start_ptr = 0;
 * unique_count = 0;
   a -> put in array, at index int(a) => mark 1, uc = 1
   b => arr[int(b)] = 1, uc = 2
   c => int(c) = 1 ,uc = 3
   if(arr[int(a)] != 0){
   uc = 3 (no change)
   move start ptr past the detected duplicate
   start = index_of_first detected duplicate + 1
   so we want  to have a nested arr like this:
   [[detected, index],[detected, index],[detected, index], [detected, index]]
   }
   after we detect duplicate we will have to clear all unique chars up to first
 detected duplicate zero out pre duplicate && decrement unizeu_char counter

   b uc = 1, arr [[1,0]]
   a uc = 2 arr[1,0],[1,1]
   --> c uc = 3 [1,0],[1,1],[1,2]
   a uc = get idx of duplicate -> 1
   iterate over all elements that have index <= 1
   zero them out, every time you do that, decrement uc
   [1,0] => [0,0], uc-1 => 2
   [1,1] => [0,0] uc-1 => 1



 */
void zero_out_values(int arr[25][2], int index) {
  printf("[INFO] Zeroing values up to index [ %d ]\n", index);
  for (int i = 0; i < 25; i++) {
    if (arr[i][1] <= index) {
      arr[i][0] = 0;
      arr[i][1] = 0;
    }
  }
}

int find_marker(char const *file_name) {
  FILE *fh = fopen(file_name, "r");
  int buffer_size = 10240;
  char buffer[buffer_size];
  fgets(buffer, buffer_size, fh);
  int unique_count = 0;
  // there are 25 lowercase chars possible
  // first ele is flag ifDetected, second is the index where it was detected
  int unique_chars[25][2] = {0};
  for (int i = 0; i < strlen(buffer); i++) {
    int char_idx = (int)buffer[i] - 97;
    if (unique_chars[char_idx][0] == 0) {
      unique_count++;
    } else {
      zero_out_values(unique_chars, unique_chars[char_idx][1]);
      unique_count--;
    }
    if (unique_count == 4) {
      printf("[INFO] Marker after char at index = %d\n", i);
      return i;
    }
    unique_chars[char_idx][0] = 1;
    unique_chars[char_idx][1] = i;
  }
  return 0;
}

int main() { 
  assert(find_marker("sample_input") == 7);
  assert(find_marker("sample_input_2") == 5);
}
