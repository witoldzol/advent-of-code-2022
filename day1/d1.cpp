#include <stdio.h>
#include <string.h>
#include <math.h>

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

void decimal_to_snafu(long input, char *output) {
  // char foo[] = "wow";
  // strcpy(output, foo);
  /*
     0 -> 0
     1 -> 1
     2 -> 2
     3 -> 1=
     4 -> 1-
     5 -> 10
     6 -> 11
     7 -> 12
     8 -> 2=
     9 -> 2-
   */
  /*
     if x followed by 0, divide x by 5, if division higher than 2, move over?
     10 -> 10 /5 -> 20
     11 -> 11 /5 -> 2 + map(1)
     12 -> 22 2 + map(2)
     13 ->  2 + map(3 ?)
     20 -> 20/5 = 4 (less than 10 ? map(4)) + 0 => 40
     30 -> 30/5 = 6 => 110
     100 -> 100/5 = 20 > 9 == true, add 0, divide again 20/5 => 4 < 0 == true,
     map(4) + 0 + 0 > 1-00 (125-25)
   */
  input = 388888;
  char input_as_str[255];
  sprintf(output, "%ld", input);
}

void decimal_to_snafu_map(int n, char *output) {
  switch (n) {
  case '0':
    strcpy(output, "0");
  case '1':
    strcpy(output, "1");
  case '2':
    strcpy(output, "2");
  case '3':
    strcpy(output, "1=");
  case '4':
    strcpy(output, "1-");
  case '5':
    strcpy(output, "10");
  case '6':
    strcpy(output, "11");
  case '7':
    strcpy(output, "12");
  case '8':
    strcpy(output, "2=");
  case '9':
    strcpy(output, "2-");
  }
}
