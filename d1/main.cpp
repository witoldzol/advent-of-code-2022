#include <bits/types/FILE.h>
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
  int elf_calories[3000];
  int counter = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (counter == 10){
      break;
    }
    counter++;
    if(!strcmp(line, "\n")) {
      printf("new line !\n");
    } else {
      printf("%s", line);
    }
  }
}
