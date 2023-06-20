#include <assert.h>
#include <cstdlib>
#include <cstring>
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

int move_score(char a) {
  switch (a) {
  case 'R':
    return 1;
  case 'P':
    return 2;
  case 'S':
    return 3;
  default:
    printf("[ERROR] Invalid input : %c, exiting game", a);
    exit(1);
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
  if (player == 'P' && enemy == 'S')
    return 0;
  printf("[ERROR] Invalid input ( player = %c , enemy = %c ), exiting game",
         player, enemy);
  exit(1);
}

int calculate(char file_name[]) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    exit(1);
  }
  int line_length = 5;
  char line[line_length];
  char player, enemy;
  size_t score = 0;
  printf("[INFO] ========= START =========== \n");
  while (fgets(line, line_length, fp)) {
    enemy = enemy_move_map(line[0]);
    player = player_move_map(line[2]);
    printf("[INFO] Input line: %s", line);
    printf("[INFO] player = %c, enemy = %c\n", player, enemy);
    score += move_score(player);
    score += scissor_game(player, enemy);
  }
  printf("[INFO] ========= END =========== \n");
  fclose(fp);
  return score;
}

int main() {
  char sample_input[] = "sample_input";
  int sample_score = calculate(sample_input);
  assert(sample_score == 15);
  
  char input[] = "input";
  int score = calculate(input);
  printf("%d\n",score);
}
