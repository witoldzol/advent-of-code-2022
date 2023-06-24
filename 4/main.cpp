#include <assert.h>
#include <cstdlib>
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
    char *left_side = strtok(buffer, ",");
    char *right_side = strtok(NULL, ",");
    printf("==== LEFT SIDE ==== [ %s ]\n", left_side);
    int left = atoi(strtok(left_side, "-"));
    printf(" left  = [ %d ]\n", left);
    int right = atoi(strtok(NULL, "-"));
    printf(" right  = [ %d ]\n", right);
    printf("\n");
    printf("==== RIGHT SIDE ==== [ %s ]", right_side); //fix => it has a trailing newline
    int other_left = atoi(strtok(right_side, "-"));
    printf(" other left = [ %d ]\n", other_left);
    int other_right = atoi(strtok(NULL, "-"));
    printf(" other right = [ %d ]\n", other_right);
    sum += is_overlapping(left, right, other_left, other_right);
  }
  return sum;
}

int main() {
  assert(get_overlaps("sample_input") == 2);
  assert(get_overlaps("small_input") == 0);
  assert(get_overlaps("input") == 471);

}
