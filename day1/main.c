#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * fp;
  int bufferLength = 255;
  char buffer[bufferLength];
  fp = fopen("input", "r");
  while(fgets(buffer, bufferLength, fp)){
    printf("%s",buffer);
  }
  fclose(fp);
}
