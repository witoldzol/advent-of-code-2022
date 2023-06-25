#include <cstring>
#include "stack.h"
#include <bits/types/FILE.h>
#include <cstdlib>
#include <stdio.h>

/* sample input
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3
 */
int main() {
  char s1[100] = {'Z', 'N'};
  Stack stack1 = {.top = 1, .size = 100, .data = s1};
  char s2[100] = {'M', 'C', 'D'};
  Stack stack2 = {.top = 2, .size = 100, .data = s2};
  char s3[100] = {'P'};
  Stack stack3 = {.top = 0, .size = 100, .data = s3};

  FILE *fh = fopen("sample_input", "r");
  int buffer_size = 255;
  char buffer[buffer_size];
  while (fgets(buffer, buffer_size, fh)) {
    printf("line: %s", buffer);
    char *_ = strtok(buffer, " ");
    int move = atoi(strtok(NULL, " "));
    printf("move: %d\n", move);
    char *__ = strtok(NULL, " ");
    int from = atoi(strtok(NULL, " "));
    printf("from: %d\n", from);
    char *___ = strtok(NULL, " ");
    int to = atoi(strtok(NULL, " "));
    printf("to: %d\n", to);
  }
}
