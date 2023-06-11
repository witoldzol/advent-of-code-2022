#include <bits/types/FILE.h>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main() {
  char *line;
  size_t len = 0;
  ssize_t read;
  FILE *fp = fopen("input", "r");
  if (fp == NULL) {
    exit(1);
  }
  long long elf_calories_arr[3000] = {0};
  long long calorie_counter = 0;
  long long arr_pointer = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (!strcmp(line, "\n")) {
      elf_calories_arr[arr_pointer] = calorie_counter;
      arr_pointer++;
      calorie_counter = 0;
    } else {
      long long n = atoi(line);
      calorie_counter += n;
    }
  }
  long long max;
  long long elf;
  for (int i = 0; i < 3000; i++) {
    if (elf_calories_arr[i] > max) {
      max = elf_calories_arr[i];
      elf = i + 1;
    }
  }
  printf("Max calories is %lld, elf %lld\n", max, elf);
}
