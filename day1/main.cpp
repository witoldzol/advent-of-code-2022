#include "d1.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fp;
  int bufferLength = 50;
  char buffer[bufferLength];
  long snafu_total = 0;

  fp = fopen("input", "r");
  while (fgets(buffer, bufferLength, fp)) {
    snafu_total += snafu_to_int(buffer);
  }
  char result_as_snafu[100];
  snafu_total = 10;
  decimal_to_snafu(snafu_total, result_as_snafu);
  fclose(fp);
  printf("result is %ld\n", snafu_total);
  // printf("expected : %ld\n", 32005641587247);
  printf("snafu total : %s\n", result_as_snafu);
}
