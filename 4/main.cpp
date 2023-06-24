#include <assert.h>
#include <cstring>
#include <stdio.h>

int is_overlapping(int a, int b, int c, int d) {
  // check if two ranges, a-b && c-d contain each other
  // eg. 3-3, 2-4 => 2-4 contains range 3-3, return true
  // eg2. 1-3, 2,4 => 2,4 contains only part of 1-3, so return false

  // check if left side contains right side
  if (a <= c && b >= d) {
    return true;
    // check if right side contains right side
  } else if (c <= a && d >= b) {
    return 1;
  }
  return 0;
}

int get_overlaps(char *file_name) {
  FILE *fp = fopen(file_name, "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  int sum = 0;
  while (fgets(buffer, buffer_size, fp)) {
    char *token = strtok(buffer, ",");
    int left = token[0];
    int right = token[2];
    printf("[INFO] token = [ %s ]\n", token);
    printf("[INFO] left = %c, right = %c\n", left, right);
    token = strtok(NULL, ",");
    int other_left = token[0];
    int other_right = token[2];
    int len = strlen(token);
    token[len - 1] = '\0'; // remove trailing newline
    printf("[INFO] token = [ %s ]\n", token);
    printf("[INFO] other left = %c, other right = %c\n", other_left,
           other_right);
    sum += is_overlapping(left, right, other_left, other_right);
  }
  return sum;
}

int main() { 
  assert(get_overlaps("sample_input") == 2); 
  printf("sum = %d ", get_overlaps("input") == 2);
}
