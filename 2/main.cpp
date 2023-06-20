#include <cstdlib>
#include <stdio.h>

char enemy_move_map(char a) {
  switch (a) {
  case 'A':
    return 'R';
  case 'B':
    return 'P';
  case 'C':
    return 'S';
  default:
    printf("[ERROR] Invalid input : %c, exiting game", a);
    exit(1);
  }
}

char player_move_map(char a) {
  switch (a) {
  case 'X':
    return 'R';
  case 'Y':
    return 'P';
  case 'Z':
    return 'S';
  default:
    return 'e';
  }
}

int scissor_game(char player, char enemy) {
  if (player == enemy)
    return 3;
  if (player == 'R' && enemy == 'S')
    return 6;
  if (player == 'R' && enemy == 'P')
    return 0;
  if (player == 'S' && enemy == 'R')
    return 0;
  if (player == 'S' && enemy == 'P')
    return 6;
  if (player == 'P' && enemy == 'R')
    return 6;
  if (player == 'P' && enemy == 'P')
    return 0;
  printf("[ERROR] Invalid input ( player = %c , enemy = %c ), exiting game",
         player, enemy);
  exit(1);
}

void sample_tests() {
  FILE *fp = fopen("sample_input", "r");
  if (fp == NULL) {
    exit(1);
  }
  int line_length = 255;
  char line[line_length];
  while (fgets(line, line_length, fp)) {
    printf("%s\n", line);
  }
  printf("the end\n");
}

int main() { sample_tests(); }
