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

char player_move_map_2(char enemy_move, char expected_result) {
  /*
   * S - scissor
   * R - rock
   * P - paper
   */
  // Y -- draw
  if (expected_result == 'Y')
    return enemy_move;
  // X -- loose
  if (enemy_move == 'R' && expected_result == 'X') {
    return 'S';
  }
  if (enemy_move == 'S' && expected_result == 'X') {
    return 'P';
  }
  if (enemy_move == 'P' && expected_result == 'X') {
    return 'R';
  }
  // Z -- win
  if (enemy_move == 'R' && expected_result == 'Z') {
    return 'P';
  }
  if (enemy_move == 'S' && expected_result == 'Z') {
    return 'R';
  }
  if (enemy_move == 'P' && expected_result == 'Z') {
    return 'S';
  }
  printf("[ERROR] Invalid input : expected_result = %c, enemy_move = %c",
         expected_result, enemy_move);
  exit(1);
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
  char player, enemy, expected_result;
  size_t score = 0;
  printf("[INFO] ========= START =========== \n");
  while (fgets(line, line_length, fp)) {
    printf("[INFO] Input line: %s", line);
    enemy = enemy_move_map(line[0]);
    expected_result = line[2];
    player = player_move_map_2(enemy, expected_result);
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
  assert(sample_score == 12);

  char input[] = "input";
  int score = calculate(input);
  assert(score == 14060);
}
