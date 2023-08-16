#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function
  char c1 = ' ';
  bool output_1 = is_tail(c1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  char c2 = 'W';
  bool output_2 = is_tail(c2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  char c3 = 'b';
  bool output_3 = is_tail(c3);
  if (!assert_false("output_3", output_3)) {
    return false;
  }


  return true;
}

bool test_is_head() {
  char c1 = ' ';
  bool output_1 = is_head(c1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  char c2 = 'Z';
  bool output_2 = is_head(c2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  char c3 = 'w';
  bool output_3 = is_head(c3);
  if (!assert_false("output_3", output_3)) {
    return false;
  }
  return true;
}

bool test_is_snake() {
  char c1 = ' ';
  bool output_1 = is_tail(c1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  char c2 = 'Z';
  bool output_2 = is_tail(c2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  char c3 = 'b';
  bool output_3 = is_tail(c3);
  if (!assert_false("output_3", output_3)) {
    return false;
  }

  char c4 = '*';
  bool output_4 = is_tail(c4);
  if (!assert_false("output_4", output_4)) {
    return false;
  }

  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  if (!assert_true("", 'w' == body_to_tail('^'))) {
    return false;
  };
  if (!assert_true("", 'a' == body_to_tail('<'))) {
    return false;
  };
  if (!assert_true("", 's' == body_to_tail('v'))) {
    return false;
  };
  if (!assert_true("", 'd' == body_to_tail('>'))) {
    return false;
  };
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  if (!assert_true("", '^' == head_to_body('W'))) {
    return false;
  }
  if (!assert_true("", '<' == head_to_body('A'))) {
    return false;
  }
  if (!assert_true("", 'v' == head_to_body('S'))) {
    return false;
  }
  if (!assert_true("", '>' == head_to_body('D'))) {
    return false;
  }
  return true;
}

bool test_get_next_x() {
  // TODO: Implement this function.
  if (!assert_true("", 4 == get_next_col(3, '>'))) {
    return false;
  }
  if (!assert_true("", 4 == get_next_col(3, 'd'))) {
    return false;
  }
  if (!assert_true("", 4 == get_next_col(3, 'D'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(9, '<'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(9, 'a'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(9, 'A'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, '^'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, 'w'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, 'W'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, 'v'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, 's'))) {
    return false;
  }
  if (!assert_true("", 8 == get_next_col(8, 'S'))) {
    return false;
  }
  return true;
}

bool test_get_next_y() {
  unsigned int row = 4;
  char c1 = ' ';
  unsigned int output_1 = get_next_row(row, c1);
  if (!assert_true("output_1", row == output_1)) {
    return false;
  }
  
  char c2 = '^';
  unsigned int output_2 = get_next_row(row, c2);
  if (!assert_true("output_1", row - 1 == output_2)) {
    return false;
  }

  char c3 = 's';
  unsigned int output_3 = get_next_row(row, c3);
  if (!assert_true("output_1", row + 1 == output_3)) {
    return false;
  }

  char c4 = 'W';
  unsigned int output_4 = get_next_row(row, c4);
  if (!assert_true("output_1", row - 1 == output_4)) {
    return false;
  }
  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_x()) {
    printf("%s\n", "test_get_next_x failed");
    return false;
  }
  if (!test_get_next_y()) {
    printf("%s\n", "test_get_next_y failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
