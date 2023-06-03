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

  fp = fopen("input", "r");
  while (fgets(buffer, bufferLength, fp)) {
    int str_size = get_string_size(buffer, bufferLength);
    // 120
    // len 3
    // 3,2,1 -> pow of 5
    printf("size of string %lu", sizeof(buffer));
    char s[] = "1=-0-2";
    double result = snafu_to_int(s, str_size);
    printf("result is %f", result);
    break;
  }
  fclose(fp);
}

double snafu_to_int(char *s, int size) {
  double result=0;
  double snafu_at_position_i;
  for (int i = size; i > 0; i--) {
    double base_value = pow(5, i);
    char snafu_char = s[i - 1];
    int snafu_int = snafu_map(snafu_char);
    snafu_at_position_i =  base_value * snafu_int;
    result += snafu_at_position_i;
  }
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
