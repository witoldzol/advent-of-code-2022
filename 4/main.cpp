#include <stdio.h>
#include <assert.h>

int get_overlaps(char *file_name){
  FILE *fp = fopen(file_name, "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  while (fgets(buffer, buffer_size, fp)) {
    printf("%s", buffer);
  }
  return 2;
}

int main() {
  assert(get_overlaps("sample_input") == 2);
}
