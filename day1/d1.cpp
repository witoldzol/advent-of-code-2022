#include "d1.h"
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool is_lower_bound_available(int max_power, long input);

float log_a_to_base_b(long long a, int b) {
  float x = log2(a);
  printf("log2 of %lld is %f\n", a, x);
  float y = log2(b);
  printf("log2 of %d is %f\n", b, y);
  printf("x =  %f / y = %f => %f\n", x, y, x / y);
  return x / y;
};

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
  return result;
}

bool is_lower_bound_available(int max_power, long input) {
  printf("[INFO] Calculating if lower bound is possible, max power = %d, input "
         "= %ld\n",
         max_power, input);
  int total = 0;
  if (max_power > 0) {
    for (int i = 0; i < max_power; i++) {
      total += pow(5, i) * 2; // 2 is max digit in snafu range
    }
    printf("[INFO] Max total = %d, input = %ld, abs() input = %ld\n", total,
           input, abs(input));
    if (total >= abs(input)) {
      printf("INFO - We can fit into the lower bound, we can lower max power "
             "by one\n");
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
  return ceil(log_a_to_base_b(input, 5));
}
void run_highbound(long long input, int power, char *output) {
  long long reminder = input;
  // todo - we should check this after each pass
  printf("[INFO] Lower bound NOT available for input %lld. Power == %d\n",
         reminder, power);
  char snafu_temp[100];
  for (int i = 0; i <= power; i++) {
    printf("===================\n");
    // if (is_lower_bound_available(power - i, reminder)) {
    //   printf("[INFO] *** Switching to lower bound from highbound ***\n");
    //   printf("[INFO] input = %lld, power = %d\n", input, power);
    //   run_lowerbound(input, power, output);
    //   return;
    // }
    long long max = pow(5, power - i);
    printf("[INFO] Max is %lld\n", max);
    float max_float = (float)max;
    printf("[INFO] Max float is %f\n", max_float);
    float times = reminder / max_float;
    printf("[INFO] Reminder is  %lld, times after calc is = %f\n", reminder,
           times);
    if (times < 0) {
      printf("[INFO] -2- times is now => %f\n", times);
      if (times < -2.0) {
        times = ceil(times);
        printf("[INFO] -3- times is now => %f\n", times);
      } else {
        times = floor(times);
        printf("[INFO] -4- times is now => %f\n", times);
      }
    }
    if (times > 2 || times < -2) {

      printf("Iteration %d, max power = %d, input = %lld\n.", i, power,
             reminder);
      printf("Exiting because we got 'times' value higher than 2, which is "
             "illegal in snafu system\n");
      exit(1);
    }
    printf("[INFO] times = %f, index = %d\n", times, i);
    // 3125 - 2 * 625 + 125  + 25 - 5 + 2
    //
    // 2022
    // power = 5
    // 1 5 25 125 625 3125
    // i=0, times 2022/3125 < 0 --> take 1
    // reminder 2022 - 3125  = -1103
    // times floor -> - (2 * 125 ) = -250
    // -1103 + 250 =
    //
    // result = 1-1111
    // ???? calc if low bound possible (input = -1103, pow=4)
    // (2 * 625) + (2 * 125) + (2 * 25) + (2 * 5) + (2 * 1)
    // max = 1562, can fit 1103, take lower bound
    // -1103 / 625 -> times -1.9
    //
    //
    if ((times < 3 && times >= 1) || (times > -3 && times < 0)) {
      printf("[INFO] -1- times is now => %f\n", times);
      if (times < 0) {
        printf("[INFO] -2- times is now => %f\n", times);
        if (times < -2.0) {
          times = ceil(times);
          printf("[INFO] -3- times is now => %f\n", times);
        } else {
          times = floor(times);
          printf("[INFO] -4- times is now => %f\n", times);
        }
      }
      times = floor(times);

      char temp = decimal_to_snafu_map(times);
      if (temp == 'e') {
        printf("[ERROR] Invalid number passed to snafu map, %d\n", (int)times);
        exit(1);
      }
      snafu_temp[i] = temp;
      printf("[INFO] After allocating snafu is == `%s`\n", snafu_temp);
      printf("[INFO] reminder before new calc is %lld\n", reminder);
      printf("current times = %f\n", times);
      reminder = reminder - (times * pow(5, power - i));
      printf("[INFO] reminder after new calc is %lld\n", reminder);
      if (reminder) {
        continue;
      } else {
        // no reminder, we can fill the rest of array with zeros
        for (int j = i + 1; j <= power; j++) {
          snafu_temp[j] = '0';
        }
        break;
      }
    } else {
      times = 1; // pass 1 & move to next iteration where w handle negative
                 // reminder
      char temp = decimal_to_snafu_map(times);
      // times is below 0, so we take one & handle negatives
      snafu_temp[i] = temp;
      printf("[INFO] After allocating snafu is == `%s`\n", snafu_temp);
      reminder = reminder - (times * pow(5, power - i));
      if (reminder) {
        continue;
      } else {
        // no reminder, we can fill the rest of array with zeros
        for (int j = i + 1; j <= power; j++) {
          snafu_temp[j] = '0';
        }
        break;
      }
    }
    snafu_temp[power + 1] = '\0';
  }
  printf("after cal snafu is %s for input %lld\n", snafu_temp, input);
  strcpy(output, snafu_temp);
}

void run_lowerbound(long long input, int power, char *output) {
  power--;
  printf("[INFO] Lower bound available for input %lld, power = %d \n", input, power);
  long long reminder;
  char snafu_temp[100] = {0};
  for (int i = 0; i <= power; i++) {
    // how many 5s can we fit into this bit?
    float times = input / pow(5, power - i);
    printf("[INFO] How many 5s can we fit ?\n");
    printf("[INFO] pow(5, power (%d) - index (%d)? ==> %f \n", power, i, times);

        if (times < 2.0 && times > 1.5) {
          times = ceil(times);
          printf("[INFO] -3- times is now => %f\n", times);
        } else {
          times = floor(times);
          printf("[INFO] -4- times is now => %f\n", times);
        }
    if (((int)times) > 2) {
      printf("[INFO] Iteration %d, max power = %d, input = %lld\n.", i, power, input);
      printf("[ERROR] Exiting because we got 'times' == %d value higher than 2, which is "
             "illegal in snafu system", (int) times);
      exit(1);
    }
    printf("[INFO] times = %f, index = %d\n", times, i);
    if (times == 2 || times == 1 || times == -1 || times == -2) {
      char t = decimal_to_snafu_map((int) times);
      snafu_temp[i] = t;
      printf("[INFO] After allocating snafu is == %s\n", snafu_temp);
      reminder = input - (times * pow(5, power - i));
      printf("[INFO] Reminder is == %lld\n", reminder);
      if (reminder) {
        input = reminder;
        continue;
      } else {
        for (int j = i + 1; j <= power; j++) {
          snafu_temp[j] = '0';
        }
        break;
      }
      // most likely, input is lower than current max value for given index
      // ie. pow(5,power-i)
    } else {
      snafu_temp[i] = '0';
    }
    // tie off the result
    snafu_temp[power + 1] = '\0';
  }
  printf("[INFO] *** Final SNAFU number is ==> %s for input %lld ***\n", snafu_temp, input);
  strcpy(output, snafu_temp);
}
/*
 
      if (!strcmp(temp, "error")) {
        printf("[ERROR] Invalid number passed to snafu map, %d\n", (int)times);
        exit(1);
      }
      snafu_temp[i] = *temp;
      printf("[INFO] After allocating snafu is == `%s`\n", snafu_temp);
      printf("[INFO] reminder before new calc is %lld\n", reminder);
      printf("current times = %f\n", times);
      reminder = reminder - (times * pow(5, power - i));
      printf("[INFO] reminder after new calc is %lld\n", reminder);
      if (reminder) {
        continue;
      } else {
        // no reminder, we can fill the rest of array with zeros
        for (int j = i + 1; j <= power; j++) {
          snafu_temp[j] = '0';
        }
        break;
      }
 */
void decimal_to_snafu(long long input, char *output) {
  /*
  example : 61
  max pow(5,0)? 2 fits  61 ? no
  max pow(5,1) * 2 + pow(5,0) * 2 fits 61 ? no
  max pow(5,2) 2 + pow(5,1) * 2 + pow(5,0) * 2 fits 61 ? yes
  */
  printf("*****************************************************\n");
  printf("START NEW RUN \n");
  printf("Input : %lld\n", input);
  printf("*****************************************************\n");
  char temp = decimal_to_snafu_map(input);
  // strcmp returns 0 if equal, which is false in if statement
  // quick check if we can map input, if we get error, continue with more
  // complex cal
  if (temp != 'e') {
    printf("Input mapped to snafu, snafu result is : '%c'\n", temp);
    strcpy(output, &temp);
    output[1] = '\0'; // tie off, we compare to string in tests 
    return;
  }
  int power = max_power(input);
  // test if we can fit input into lower bound
  if (is_lower_bound_available(power, input)) {
    printf("[INFO] Starting lower bound run \n");
    run_lowerbound(input, power, output);
  } else {
    run_highbound(input, power, output);
  }
}
