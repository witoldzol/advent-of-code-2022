#include <cmath>
#include <math.h>
#include <stdio.h>
#include <string.h>

void decimal_to_snafu_map(int n, char *output);
int get_lower_bound(int max_power, long input);

int log_a_to_base_b(int a, int b) { return log2(a) / log2(b); };

int snafu_to_decimal_map(char n) {
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

long snafu_to_int(char *s) {
  int size = strlen(s) - 1; // fget stores newline in a string, which strlen
                            // counts, so we remove it from calc
  long double result = 0;
  double snafu_at_position_i;
  // traverse from right to left, calculate power position based on y index
  for (int i = size, y = 0; i > 0; i--, y++) {
    double base_value = pow(5, y);
    char snafu_char = s[i - 1];
    int snafu_int = snafu_to_decimal_map(snafu_char);
    snafu_at_position_i = base_value * snafu_int;
    result += snafu_at_position_i;
  }
  printf("\n");
  printf("string is : %s\n", s);
  printf("snafu value is : %Lf\n", result);
  printf("=====================\n");
  return result;
}

int get_lower_bound(int max_power, long input) {
  int total = 0;
  if (max_power > 0) {
    for (int i = 0; i < max_power; i++) {
      total += 2 * pow(5, i);
    }
    if (total >= input) {
      printf("INFO - We can fit into the lower bound, returning max -1");
      return --max_power;
    }
  }
  return max_power;
}

void decimal_to_snafu_map(int n, char *output) {
  printf("decimal n is %d\n", n);
  switch (n) {
  case 0:
    strcpy(output, "0");
    break;
  case 1:
    strcpy(output, "1");
    break;
  case 2:
    strcpy(output, "2");
    break;
  case 3:
    strcpy(output, "1=");
    break;
  case 4:
    strcpy(output, "1-");
    break;
  case 5:
    strcpy(output, "10");
    break;
  case 6:
    strcpy(output, "11");
    break;
  case 7:
    strcpy(output, "12");
    break;
  case 8:
    strcpy(output, "2=");
    break;
  case 9:
    strcpy(output, "2-");
    break;
  default:
    strcpy(output, "error");
  }
}

void decimal_to_snafu(long input, char *output) {
  /*
  example : 61
  max pow(5,0)? 2 fits  61 ? no
  max pow(5,1) * 2 + pow(5,0) * 2 fits 61 ? no
  max pow(5,2) 2 + pow(5,1) * 2 + pow(5,0) * 2 fits 61 ? yes
  */

  char temp[sizeof(output)];
  decimal_to_snafu_map(input, temp);
  if (strcmp(temp, "error")) { // strcmp returns 0 if equal, which is false in
                               // if statement
    printf("temp is :%s\n", temp);
    strcpy(output, temp);
    return;
  }

  // log base 5 of input, get ceiling of that number,
  // and thats the max power of 5 that can fit this input
  int max_power = ceil(log_a_to_base_b(input, 5));
  // test lower bound
  max_power = get_lower_bound(max_power, input);
}
