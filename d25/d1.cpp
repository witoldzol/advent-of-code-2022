#include "d1.h"
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool is_low_power_enough(int max_power, long input);
void fill_reminder_of_array_with_zeros(char *arr, int start, int end);
void get_snafu_char(char *snafu_temp, float times, int i);

void fill_reminder_of_array_with_zeros(char *arr, int start, int end) {
  int j = start + 1;
  for (; j <= end; j++) {
    arr[j] = '0';
  }
  arr[j] = '\0';
}

int round_to_closest_int(float n) {
  // handle over 2's usecase, where 2-2.99 rounds down ( up for negative )
  if (abs(n) > 2) {
    if (n > 0) {
      return floor(n);
    }
    return ceil(n);
  }
  return round(n);
}

float log_a_to_base_b(long long a, int b) { return log2(a) / log2(b); };

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
  printf("[ERROR] Invalid input to snafu map == %d\n", n);
  exit(1);
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
  return result;
}

bool is_low_power_enough(int max_power, long input) {
  printf("[INFO] Calculating if lower bound is possible, max power = %d, input "
         "= %ld\n",
         max_power, input);
  long long total = 0;
  if (max_power > 0) {
    for (int i = 0; i < max_power; i++) {
      total += pow(5, i) * 2; // 2 is max digit in snafu range
    }
    printf("[INFO] Max total = %lld, input = %ld, abs() input = %ld\n", total,
           input, abs(input));
    if (total >= abs(input)) {
      return true;
    }
  }
  return false;
}

char decimal_to_snafu_map(int n) {
  printf("[INFO] decimal passed to snafu map == %d\n", n);
  switch (n) {
  case -1:
    return '-';
    break;
  case -2:
    return '=';
    break;
  case 0:
    return '0';
    break;
  case 1:
    return '1';
    break;
  case 2:
    return '2';
    break;
  default:
    printf("[ERROR] Invalid input to snafu map == %d\n", n);
    return 'e';
  }
}

int max_power(long long input) {
  // log base 5 of input, get ceiling of that number,
  // and thats the max power of 5 that can fit this input
  // example: input = 120, answer : power 3
  // p=3 p=2 p=1 p=0
  // 125 25  5   1
  return ceil(log_a_to_base_b(input, 5));
}

void get_snafu_char(char *snafu_temp, float times, int i) {
  char temp = decimal_to_snafu_map(times);
  if (temp == 'e') {
    printf("[ERROR] Invalid number passed to snafu map, %f\n", times);
    exit(1);
  }
  snafu_temp[i] = temp;
  snafu_temp[i + 1] = '\0';
  printf("[INFO] After pushing new number, temporary snafu is == `%s`\n",
         snafu_temp);
}

void exit_if_over_two(float times) {
  if (times > 2) {
    printf("[ERROR] Exiting because we got 'times' == %d value higher than "
           "2, which is "
           "illegal in snafu system",
           (int)times);
    exit(1);
  }
}

void get_snafu_number(long long input, int power, char *output) {
  long long reminder = input;
  char snafu_temp[100];
  for (int i = 0; i <= power; i++) {
    printf("================ Iteration start : i >> %d ================\n", i);
    long long max = pow(5, power - i);
    printf("[INFO] Max is %lld\n", max);
    float times = reminder / (float)max;
    printf("[INFO] Reminder is  %lld, times after calc is = %f\n", reminder,
           times);
    times = round_to_closest_int(times);
    printf("[INFO] Times after rounding= %.1f, index = %d\n", times, i);
    exit_if_over_two(times);
    if (times == 0) {
      times =
          (i == 0) ? 1 : 0; // I have no idea why this works, or is the case!
    }
    get_snafu_char(snafu_temp, times, i);
    reminder = reminder - (times * pow(5, power - i));
    printf("[INFO] Reminder is %lld\n", reminder);
    if (reminder) {
      continue;
    } else {
      fill_reminder_of_array_with_zeros(snafu_temp, i, power);
      break;
    }
  }
  printf("[INFO] End of iteration, snafu number is => %s for input %lld\n",
         snafu_temp, input);
  strcpy(output, snafu_temp);
}

void decimal_to_snafu(long long input, char *output) {
  printf("*****************************************************\n");
  printf("START NEW RUN \n");
  printf("Input : %lld\n", input);
  printf("*****************************************************\n");
  // strcmp returns 0 if equal, which is false in if statement
  // quick check if we can map input, if we get error, continue with more
  // complex cal
  char temp = decimal_to_snafu_map(input);
  if (temp != 'e') {
    printf("Input mapped to snafu, snafu result is : '%c'\n", temp);
    strcpy(output, &temp);
    output[1] = '\0'; // end string
    return;
  }
  int power = max_power(input);
  // test if we can fit input into power - 1 bracket
  if (is_low_power_enough(power, input)) {
    power--;
    printf(
        "[INFO] We can fit input [ %lld ], into expression with ( power - 1 )"
        "one. Power after lowering by 1 = %d \n",
        input, power);
    get_snafu_number(input, power, output);
  } else {
    printf("[INFO] Lower power would NOT fit input, using power = %d\n", power);
    get_snafu_number(input, power, output);
  }
}
