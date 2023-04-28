#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

#define MAX_LINE_LEN 131072
/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  const char* board1 = "####################";
  const char* board2 = "#                  #";
  const char* board3 = "# d>D    *         #";
  const size_t default_row = 18;
  const size_t default_col = strlen(board1);

  game_state_t* ret = (game_state_t*)malloc(sizeof(game_state_t));

  ret->num_rows = (unsigned)default_row;
  ret->num_snakes = 1;

  /*fill board*/
  ret->board = (char**)malloc(default_row * sizeof(char*));
  for (int i = 0; i < 18; i++) {
    ret->board[i] = (char*)malloc((default_col + 1) * sizeof(char));
    if (ret->board[i] == NULL) {
      fprintf(stderr, "malloc: ");
      exit(-1);
    }

    ret->board[i][default_col] = '\0';
    if (i == 0 || i == 17) {
      strcpy(ret->board[i], board1);
    } else if (i == 2) {
      strcpy(ret->board[i], board3);
    } else {
      strcpy(ret->board[i], board2);
    }
  }

  /*set snake*/
  ret->snakes = (snake_t*)malloc(sizeof(snake_t));
  ret->snakes->head_col = 4;
  ret->snakes->head_row = 2;
  ret->snakes->tail_col = 2;
  ret->snakes->tail_row = 2;
  ret->snakes->live = true;

  return ret;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  /*free board*/
  if (state == NULL) return;

  for (int i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);

  /*free snake*/
  free(state->snakes);

  free(state);

  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  for (int i = 0; i < state->num_rows; i++) {
    fputs(state->board[i], fp);
    fputc('\n', fp);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

static inline bool in_chars(char c, char* chars) {
  while (*chars) {
    if (c == *chars) return true;
    chars++;
  }
  return false;
}
/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  return in_chars(c, "wasd");
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  return in_chars(c, "WASDx");
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  return in_chars(c, "wasd^<v>WASDx");
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  if (c == '>') {
    return 'd';
  } else if (c == '<') {
    return 'a';
  } else if (c == '^') {
    return 'w';
  } else if (c == 'v') {
    return 's';
  } else {
    fprintf(stderr, "body_to_tail: unknown body char: %c\n", c);
    return '?';
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  if (c == 'W') {
    return '^';
  } else if (c == 'A') {
    return '<';
  } else if (c == 'S') {
    return 'v';
  } else if (c == 'D') {
    return '>';
  } else {
    fprintf(stderr, "head_to_body: unknown head char: %c\n", c);
    return '?';
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (in_chars(c, "vsS")) {
    return cur_row + 1;
  } else if (in_chars(c, "^wW")) {
    return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (in_chars(c, "<aA")) {
    return cur_col - 1;
  } else if (in_chars(c, ">dD")) {
    return cur_col + 1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t* p = state->snakes + snum;
  unsigned x = p->head_row;
  unsigned y = p->head_col;
  unsigned nx = get_next_row(x, get_board_at(state, x, y));
  unsigned ny = get_next_col(y, get_board_at(state, x, y));
  return get_board_at(state, nx, ny);
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t* p = state->snakes + snum;
  unsigned x = p->head_row;
  unsigned y = p->head_col;
  char head_char = get_board_at(state, x, y);
  unsigned nx = get_next_row(x, head_char);
  unsigned ny = get_next_col(y, head_char);

  p->head_row = nx;
  p->head_col = ny;
  set_board_at(state, nx, ny, head_char);
  set_board_at(state, x, y, head_to_body(head_char));
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t* p = state->snakes + snum;
  unsigned x = p->tail_row;
  unsigned y = p->tail_col;
  char tail_char = get_board_at(state, x, y);
  unsigned nx = get_next_row(x, tail_char);
  unsigned ny = get_next_col(y, tail_char);

  p->tail_row = nx;
  p->tail_col = ny;
  set_board_at(state, nx, ny, body_to_tail(get_board_at(state, nx, ny)));
  set_board_at(state, x, y, ' ');
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  for (unsigned i = 0; i < state->num_snakes; i++) {
    char next_char = next_square(state, i);
    if (is_snake(next_char) || next_char == '#') { // snake crash
      state->snakes[i].live = false;
      set_board_at(state, state->snakes[i].head_row, state->snakes[i].head_col, 'x');
      continue;
    }
    update_head(state, i);
    if (next_char != '*') {
      update_tail(state, i);
    } else { // eat a fruit
      add_food(state);
    }
  }

  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "load_board: file not exist: %s\n", filename);
    return NULL;
  }
  game_state_t* ret = (game_state_t*)malloc(sizeof(game_state_t));
  char board_line[MAX_LINE_LEN], *p = NULL;
  char* board_row[MAX_LINE_LEN] = {0};
  unsigned row_idx = 0;

  while ((p = fgets(board_line, sizeof(board_line), f)) != NULL) {
    size_t len = strlen(board_line);
    if (board_line[len - 1] == '\n') board_line[len - 1] = '\0';
    char* bl = (char*)malloc((len + 1) * sizeof(char));
    strcpy(bl, board_line);
    board_row[row_idx++] = bl;
  }
  ret->num_rows = row_idx;
  ret->board = (char**)malloc((row_idx) * sizeof(char*));
  memcpy(ret->board, board_row, row_idx * sizeof(char*));

  return ret;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.

  snake_t* snake = state->snakes + snum;
  unsigned x = snake->tail_row;
  unsigned y = snake->tail_col;
  char cur_char = get_board_at(state, x, y);
  while (!is_head(cur_char)) {
    x = get_next_row(x, cur_char);
    y = get_next_col(y, cur_char);
    cur_char = get_board_at(state, x, y); 
  }
  snake->head_row = x;
  snake->head_col = y;

  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  unsigned snakes[MAX_LINE_LEN][2] = {};
  unsigned s_cnt = 0;
  for (int i = 0; i < state->num_rows; i++) {
    char *p = state->board[i];
    char *ch = p;
    while (*p) {
      if (is_tail(*p)) {
        snakes[s_cnt][0]= (unsigned)i;
        snakes[s_cnt][1] = (unsigned)(p - ch);
        s_cnt++;
      }
      p++;
    }
  }

  state->num_snakes = s_cnt;
  state->snakes = (snake_t*)malloc(s_cnt * sizeof(snake_t));
  for (unsigned i = 0; i < s_cnt; i++) {
    state->snakes[i].live = true;
    state->snakes[i].tail_row = snakes[i][0];
    state->snakes[i].tail_col = snakes[i][1];
    find_head(state, i);
  }

  return state;
}
