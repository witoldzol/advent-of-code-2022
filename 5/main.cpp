#include "stack.h"
#include <bits/types/FILE.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

/* sample input
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3
 */
void create_sample_input() {
  char s1[100] = {'Z', 'N'};
  Stack stack1 = {.top = 1, .size = 100, .data = s1};
  char s2[100] = {'M', 'C', 'D'};
  Stack stack2 = {.top = 2, .size = 100, .data = s2};
  char s3[100] = {'P'};
  Stack stack3 = {.top = 0, .size = 100, .data = s3};
  Stack stacks[] = {stack1, stack2, stack3};
}
/*
 * input

            [C]         [N] [R]
[J] [T]     [H]         [P] [L]
[F] [S] [T] [B]         [M] [D]
[C] [L] [J] [Z] [S]     [L] [B]
[N] [Q] [G] [J] [J]     [F] [F] [R]
[D] [V] [B] [L] [B] [Q] [D] [M] [T]
[B] [Z] [Z] [T] [V] [S] [V] [S] [D]
[W] [P] [P] [D] [G] [P] [B] [P] [V]
 1   2   3   4   5   6   7   8   9

 */
int main() {
  char s1[100] = {'W', 'B', 'D', 'N', 'C', 'F', 'J'};
  char s2[100] = {'P', 'Z', 'V', 'Q', 'L', 'S', 'T'};
  char s3[100] = {'P', 'Z', 'B', 'G', 'J', 'T'};
  char s4[100] = {'D', 'T', 'L', 'J', 'Z', 'B', 'H', 'C'};
  char s5[100] = {'G', 'V', 'B', 'J', 'S'};
  char s6[100] = {'P', 'S', 'Q'};
  char s7[100] = {'B', 'V', 'D', 'F', 'L', 'M', 'P', 'N'};
  char s8[100] = {'P', 'S', 'M', 'F', 'B', 'D', 'L', 'R'};
  char s9[100] = {'V', 'D', 'T', 'R'};
  Stack stack1 = {.top = 6, .size = 100, .data = s1};
  Stack stack2 = {.top = 6, .size = 100, .data = s2};
  Stack stack3 = {.top = 5, .size = 100, .data = s3};
  Stack stack4 = {.top = 7, .size = 100, .data = s4};
  Stack stack5 = {.top = 4, .size = 100, .data = s5};
  Stack stack6 = {.top = 2, .size = 100, .data = s6};
  Stack stack7 = {.top = 7, .size = 100, .data = s7};
  Stack stack8 = {.top = 7, .size = 100, .data = s8};
  Stack stack9 = {.top = 3, .size = 100, .data = s9};

  Stack stacks[] = {
      stack1, stack2, stack3, stack4, stack5, stack6, stack7, stack8, stack9,
  };
  FILE *fh = fopen("input", "r");
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
    for (int i = 0; i < move; i++) {
      char c = pop(&stacks[from - 1]);
      push(&stacks[to - 1], c);
    }
    for (int i = 0; i < 9; i++) {
      printf("%c", top(&stacks[i]));
    }
  }
}
