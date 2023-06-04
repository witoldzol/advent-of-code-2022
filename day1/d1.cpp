#include <math.h>
#include <stdio.h>
#include <string.h>

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

long snafu_to_int(char *s) {
  int size = strlen(s) - 1; // strlen counts \n, so we remove it from calc
  long double result = 0;
  double snafu_at_position_i;
  for (int i = size, y = 0; i > 0; i--, y++) {
    double base_value = pow(5, y);
    char snafu_char = s[i - 1];
    int snafu_int = snafu_map(snafu_char);
    snafu_at_position_i = base_value * snafu_int;
    result += snafu_at_position_i;
  }
  printf("\n");
  printf("string is : %s\n", s);
  printf("snafu value is : %Lf\n", result);
  printf("=====================\n");
  return result;
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
  11  dec
  mod 10
  1
  10(modded 1)
  21 snafu
  */
  int zero_count = 0;
  while(input > 9){
    input = input % 10;
    if(input == 0){
      input = 2;
    }
    zero_count++;
  }
  decimal_to_snafu_map(input, output);
  while(zero_count>0){
    strcat(output, "0");
    zero_count--;
  }
}
