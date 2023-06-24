#include <stdio.h>

int main() {
  FILE *fp = fopen("sample_input", "r");
  size_t buffer_size = 255;
  char buffer[buffer_size];
  while (fgets(buffer, buffer_size, fp)) {
    printf("%s", buffer);
  }
}
