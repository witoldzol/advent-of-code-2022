#include <stdio.h>

int main(){
  FILE *fh = fopen("input", "r");

  size_t buffer_size = 255;
  char buffer[buffer_size];
  while(fgets(buffer, buffer_size, fh)){
    printf("%s", buffer);
  }
}
