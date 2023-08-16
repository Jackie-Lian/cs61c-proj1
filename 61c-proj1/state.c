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

const unsigned int DEFAULT_BOARD_ROWS = 18;
const unsigned int DEFAULT_BOARD_COLS = 20;
const unsigned int BUFFER_SIZE = 100050;

/* Task 1 */
game_state_t* create_default_state() {
  // Create default_state as pointer to default game state
  game_state_t* default_state = malloc(sizeof(game_state_t));

  // Set # of rows.
  default_state->num_rows = DEFAULT_BOARD_ROWS;

  // Populate new board with stuff.
  char** new_board = malloc(DEFAULT_BOARD_ROWS * sizeof(char*));
  for (int i = 0; i < DEFAULT_BOARD_ROWS; i++) {
    new_board[i] = (char*) malloc((DEFAULT_BOARD_COLS + 1) * sizeof(char));
    if (i == 0 || i == DEFAULT_BOARD_ROWS - 1) {
      strcpy(new_board[i], "####################");
    } else if (i == 2) {
      strcpy(new_board[i], "# d>D    *         #");
    } else {
      strcpy(new_board[i], "#                  #");
    }
  }
  default_state->board = new_board;

  // Deal with snake generation.
  default_state->num_snakes = 1;
  
  snake_t* first_snake = malloc(sizeof(snake_t));
  first_snake->tail_row = 2;
  first_snake->tail_col = 2;
  first_snake->head_row = 2;
  first_snake->head_col = 4;
  first_snake->live = true;

  default_state->snakes = first_snake;
  return default_state;
}

/* Task 2 */
void free_state(game_state_t* state) {
  free(state->snakes);
  for (int i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);
  free(state);
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  for (int i = 0; i < state->num_rows; i++) {
    fprintf(fp, "%s\n", state->board[i]);
  }
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

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  char* chars = "wasd";
  for (int i = 0; i < strlen(chars); i++) {
    if (chars[i] == c) {
      return true;
    }
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  char* chars = "WASDx";
  for (int i = 0; i < strlen(chars); i++) {
    if (chars[i] == c) {
      return true;
    }
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  char* chars = "wasd^<v>WASDx";
  for (int i = 0; i < strlen(chars); i++) {
    if (chars[i] == c) {
      return true;
    }
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  switch(c) {
    case '^':
      return 'w';
    case '<':
      return 'a';
    case 'v':
      return 's';
    case '>':
      return 'd';
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  switch(c) {
    case 'W':
      return '^';
    case 'A':
      return '<';
    case 'S':
      return 'v';
    case 'D':
      return '>';
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  if (c == 'v' || c == 's' || c == 'S') {
    return cur_row + 1;
  } else if (c == '^' || c == 'w' || c == 'W') {
    return cur_row - 1;
  } else {
    return cur_row;
  }
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A') {
    return cur_col - 1;
  } else {
    return cur_col;
  }
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  snake_t *snake = state->snakes + snum;
  char head_char = get_board_at(state, snake->head_row, snake->head_col);
  unsigned int next_row = get_next_row(snake->head_row, head_char);
  unsigned int next_col = get_next_col(snake->head_col, head_char);
  return get_board_at(state, next_row, next_col);
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  snake_t *snake = state->snakes + snum;
  char head_char = get_board_at(state, snake->head_row, snake->head_col);
  unsigned int next_row = get_next_row(snake->head_row, head_char);
  unsigned int next_col = get_next_col(snake->head_col, head_char);
  set_board_at(state, snake->head_row, snake->head_col, head_to_body(head_char));
  set_board_at(state, next_row, next_col, head_char);
  snake->head_row = next_row;
  snake->head_col = next_col;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  snake_t *snake = state->snakes + snum;

  // Get the tail character.
  char tail_char = get_board_at(state, snake->tail_row, snake->tail_col);

  // Get the body's location that is in front of the tail.
  unsigned int body_row = get_next_row(snake->tail_row, tail_char);
  unsigned int body_col = get_next_col(snake->tail_col, tail_char);
  char body_char = get_board_at(state, body_row, body_col);

  // Set the current tail position to empty on the board.
  set_board_at(state, snake->tail_row, snake->tail_col, ' ');

  // Convert body to tail on board.
  set_board_at(state, body_row, body_col, body_to_tail(body_char));

  // Update body position in the struct.
  snake->tail_row = body_row;
  snake->tail_col = body_col;
}

bool is_obstacle(char c) {
  char* obstacle_str = "^v<>#";
  for (int i = 0; i < strlen(obstacle_str); i++) {
    if (obstacle_str[i] == c) {
      return true;
    }
  }
  return false;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // For each snake ... 
  for (unsigned int i = 0; i < state->num_snakes; i++) {
    // If alive...
    // Moves one step in the direction of its head.
    snake_t* snake = state->snakes + i;
    if (snake->live) {

      // If the head crashes into the body of a snake or a wall, 
      char next = next_square(state, i);
      if (is_snake(next) || next == '#') {
        // The snake dies and stops moving
        snake->live = false;

        //When a snake dies, the head is replaced with an x.
        set_board_at(state, snake->head_row, snake->head_col, 'x');

      // If the head moves into a fruit, the snake eats the fruit and grows by 1 unit in length. 
      // Each time fruit is consumed, a new fruit is generated on the board.
      // Must check next square is food first before moving
      // Otherwise food may get overwritten
      } else if (next_square(state, i) == '*') {
        update_head(state, i);
        add_food(state);
      } else {
        update_head(state, i);
        update_tail(state, i);
      }
    }  
  }
}

/* Task 5 */
// typedef struct game_state_t {
//   unsigned int num_rows;
//   char** board;

//   unsigned int num_snakes;
//   snake_t* snakes;
// } game_state_t;
game_state_t* load_board(char* filename) {
  FILE *f = fopen(filename, "r");
  game_state_t *new_state = malloc(sizeof(game_state_t));
  new_state->board = NULL;
  unsigned int i = 0;
  char *cur_line = malloc(2 * sizeof(char));
  size_t chars_in_line = 0;
  while (getline(&cur_line, &chars_in_line, f) != -1) {
    new_state->board = realloc(new_state->board, (i + 1) * sizeof(char *));
    cur_line[strlen(cur_line) - 1] = '\0';
    new_state->board[i] = cur_line;
    i++;
    cur_line = malloc(2 * sizeof(char));
    chars_in_line = 0;
  }
  fclose(f);
  new_state->num_rows = i;
  return new_state;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  snake_t *snake = state->snakes + snum;
  unsigned int row = snake->tail_row;
  unsigned int col = snake->tail_col;
  char c = get_board_at(state, row, col);
  while (!is_head(c)) {
    row = get_next_row(row, c);
    col = get_next_col(col, c);
    c = get_board_at(state, row, col);
  }
  snake->head_row = row;
  snake->head_col = col;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  state->snakes = NULL;
  unsigned int count = 0;
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < strlen(state->board[i]); j++) {
      state->snakes = realloc(state->snakes, (count + 1) * sizeof(snake_t));
      if (is_tail(get_board_at(state, i, j))) {
        state->snakes[count].tail_row = i;
        state->snakes[count].tail_col = j;
        find_head(state, count);
        state->snakes[count].live = true;
        count++;
      }
    }
  }
  state->num_snakes = count;
  return state;
}
