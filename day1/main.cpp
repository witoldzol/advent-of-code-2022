#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_string_size(char *s, int max_size);
double snafu_to_int(char *s, int size);
int snafu_map(char n);

int main() {
  FILE *fp;
  int bufferLength = 50;
  char buffer[bufferLength];
  int result = 0;

  fp = fopen("input", "r");
  while (fgets(buffer, bufferLength, fp)) {
    // int str_size = get_string_size(buffer, bufferLength);
    // char s[] = "2=0=";
    int str_size = strlen(buffer)-1;
    // printf("str len is : %i\n", str_size);
    // printf("char at 17 is %i\n", buffer[16]);
    result += snafu_to_int(buffer, str_size);
  }
  fclose(fp);
  printf("result is %i", result);
}

double snafu_to_int(char *s, int size) {
  double result=0;
  double snafu_at_position_i;
  for (int i = size, y = 0; i > 0; i--, y++) {
    double base_value = pow(5, y);
    char snafu_char = s[i-1];
    int snafu_int = snafu_map(snafu_char);
    snafu_at_position_i =  base_value * snafu_int;
    result += snafu_at_position_i;
  }
  printf("\n");
  printf("string is : %s\n", s);
  printf("snafu value is : %f\n", result);
  printf("=====================\n");
  return result;
}

int snafu_map(char n) {
  switch (n) {
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

int get_string_size(char *s, int max_size) {
  int index = 0;
  for (int i = 0; i < max_size; i++, index++) {
    if (s[i] == '\n') {
      return index;
    }
  }
  return 0;
}
