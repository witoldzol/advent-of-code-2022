#include <bits/types/FILE.h>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int get_top_three(int arr[]) {
  int max, mid, min = 0;
  for (int i = 0; i < 3000; i++) {
    int old_max = max;
    int old_mid = mid;
    if (arr[i] > max) {
      max = arr[i];
      mid = old_max;
      min = old_mid;
    } else if (arr[i] > mid) {
      mid = arr[i];
      min = old_mid;
    } else if (arr[i] > min) {
      min = arr[i];
    }
  }
  return max + mid + min;
}

int main() {
  char *line;
  size_t len = 0;
  ssize_t read;
  FILE *fp = fopen("input", "r");
  if (fp == NULL) {
    exit(1);
  }
  int elf_calories_arr[3000] = {0};
  int calorie_counter = 0;
  int arr_pointer = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (!strcmp(line, "\n")) {
      elf_calories_arr[arr_pointer] = calorie_counter;
      arr_pointer++;
      calorie_counter = 0;
    } else {
      int n = atoi(line);
      calorie_counter += n;
    }
  }
  int top_three = get_top_three(elf_calories_arr);
  printf("%d\n", top_three);
}
