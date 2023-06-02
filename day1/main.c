#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int get_string_size(char* s, int max_size);

int main() {
  FILE * fp;
  int bufferLength = 50;
  char buffer[bufferLength];

  fp = fopen("input", "r");
  while(fgets(buffer, bufferLength, fp)){
    int str_size = get_string_size(buffer, bufferLength);
    printf("size of this line is %i\n", str_size);
    printf("last char is %c\n", buffer[str_size-1]);
    buffer[str_size] = '\0';
    printf("entire string is %s", buffer);
    break;
  }
  fclose(fp);
}

int snafu_map(char n){
  switch(n){
    case '2':
      return 2;
    case '1':
      return 1;
    case '0':
      return 0;
    case '-':
      return -1;
    case '=':
      return -2;
  }
  return -9; // error
}

int get_string_size(char* s, int max_size){
  int index = 0;
  for(int i=0; i< max_size; i++, index++){
    if(s[i] == '\n'){
      return index;
    }
  }
  return 0;
}
