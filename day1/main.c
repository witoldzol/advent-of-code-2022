#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("input", "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }

  while((read = getline(&line, &len, fp)) != 1){
    // printf("Read line of length %zu\n", read);
    printf("%s", line);
    line++;
  }

  fclose(fp);
  if(line){
    free(line);
  }
  exit(EXIT_SUCCESS);
}
