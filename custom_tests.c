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
  // TODO: Implement this function.
  if (!assert_true("is_tail_1", is_tail('w'))) {
    return false;
  }
  if (!assert_true("is_tail_2", is_tail('a'))) {
    return false;
  }
  if (!assert_true("is_tail_3", is_tail('s'))) {
    return false;
  }
  if (!assert_true("is_tail_4", is_tail('d'))) {
    return false;
  }
  if (!assert_false("is_tail_5", is_tail('W'))) {
    return false;
  }
  if (!assert_false("is_tail_6", is_tail('<'))) {
    return false;
  }
  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  if (!assert_true("is_head_1", is_head('W'))) {
    return false;
  }
  if (!assert_true("is_head_2", is_head('A'))) {
    return false;
  }
  if (!assert_true("is_head_3", is_head('S'))) {
    return false;
  }
  if (!assert_true("is_head_4", is_head('D'))) {
    return false;
  }
  if (!assert_false("is_head_5", is_head('s'))) {
    return false;
  }
  if (!assert_false("is_head_6", is_head('<'))) {
    return false;
  }
  if (!assert_true("is_head_7", is_head('x'))) {
    return false;
  }
  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  if (!assert_true("is_snake_1", is_snake('W'))) {
    return false;
  }
  if (!assert_true("is_snake_2", is_snake('A'))) {
    return false;
  }
  if (!assert_true("is_snake_3", is_snake('S'))) {
    return false;
  }
  if (!assert_true("is_snake_4", is_snake('D'))) {
    return false;
  }
  if (!assert_true("is_snake_5", is_snake('w'))) {
    return false;
  }
  if (!assert_true("is_snake_6", is_snake('a'))) {
    return false;
  }
  if (!assert_true("is_snake_7", is_snake('s'))) {
    return false;
  }
  if (!assert_true("is_snake_8", is_snake('d'))) {
    return false;
  }
  if (!assert_true("is_snake_9", is_snake('^'))) {
    return false;
  }
  if (!assert_true("is_snake_10", is_snake('v'))) {
    return false;
  }
  if (!assert_true("is_snake_11", is_snake('<'))) {
    return false;
  }
  if (!assert_true("is_snake_12", is_snake('>'))) {
    return false;
  }
  if (!assert_true("is_snake_13", is_snake('x'))) {
    return false;
  }
  if (!assert_false("is_snake_14", is_snake('#'))) {
    return false;
  }
  if (!assert_false("is_snake_15", is_snake('*'))) {
    return false;
  }
  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  if (!assert_true("body_to_tail_1", body_to_tail('^') == 'w')) {
    return false;
  }
  if (!assert_true("body_to_tail_2", body_to_tail('<') == 'a')) {
    return false;
  }
  if (!assert_true("body_to_tail_3", body_to_tail('>') == 'd')) {
    return false;
  }
  if (!assert_true("body_to_tail_4", body_to_tail('v') == 's')) {
    return false;
  }
  if (!assert_true("body_to_tail_5", body_to_tail('w') == '?')) {
    return false;
  }
  if (!assert_true("body_to_tail_6", body_to_tail('a') == '?')) {
    return false;
  }
  if (!assert_true("body_to_tail_7", body_to_tail('s') == '?')) {
    return false;
  }
  if (!assert_true("body_to_tail_8", body_to_tail('d') == '?')) {
    return false;
  }
  if (!assert_false("body_to_tail_9", body_to_tail('^') == '?')) {
    return false;
  }
  if (!assert_false("body_to_tail_10", body_to_tail('V') == 's')) {
    return false;
  }
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  if (!assert_true("head_to_body_1", head_to_body('W') == '^')) {
    return false;
  }
  if (!assert_true("head_to_body_2", head_to_body('A') == '<')) {
    return false;
  }
  if (!assert_true("head_to_body_3", head_to_body('S') == 'v')) {
    return false;
  }
  if (!assert_true("head_to_body_4", head_to_body('D') == '>')) {
    return false;
  }
  if (!assert_true("head_to_body_5", head_to_body('w') == '?')) {
    return false;
  }
  if (!assert_true("head_to_body_6", head_to_body('a') == '?')) {
    return false;
  }
  if (!assert_true("head_to_body_7", head_to_body('s') == '?')) {
    return false;
  }
  if (!assert_true("head_to_body_8", head_to_body('d') == '?')) {
    return false;
  }
  if (!assert_true("head_to_body_9", head_to_body('^') == '?')) {
    return false;
  }
  if (!assert_true("head_to_body_10", head_to_body('V') == '?')) {
    return false;
  }
  return true;
}

bool test_get_next_x() {
  // TODO: Implement this function.
  if (!assert_true("get_next_row_1", get_next_row(10, 'W') == 9)) {
    return false;
  }
  if (!assert_true("get_next_row_2", get_next_row(10, 'A') == 10)) {
    return false;
  }
  if (!assert_true("get_next_row_3", get_next_row(10, 'S') == 11)) {
    return false;
  }
  if (!assert_true("get_next_row_4", get_next_row(10, 'D') == 10)) {
    return false;
  }
  if (!assert_true("get_next_row_5", get_next_row(10, 'w') == 9)) {
    return false;
  }
  if (!assert_true("get_next_row_6", get_next_row(10, 'a') == 10)) {
    return false;
  }
  if (!assert_true("get_next_row_7", get_next_row(10, 's') == 11)) {
    return false;
  }
  if (!assert_true("get_next_row_8", get_next_row(10, 'd') == 10)) {
    return false;
  }
  if (!assert_true("get_next_row_9", get_next_row(10, '^') == 9)) {
    return false;
  }
  if (!assert_true("get_next_row_10", get_next_row(10, 'V') == 10)) {
    return false;
  }
  return true;
}

bool test_get_next_y() {
  // TODO: Implement this function.
  if (!assert_true("get_next_col_1", get_next_col(10, 'W') == 10)) {
    return false;
  }
  if (!assert_true("get_next_col_2", get_next_col(10, 'A') == 9)) {
    return false;
  }
  if (!assert_true("get_next_col_3", get_next_col(10, 'S') == 10)) {
    return false;
  }
  if (!assert_true("get_next_col_4", get_next_col(10, 'D') == 11)) {
    return false;
  }
  if (!assert_true("get_next_col_5", get_next_col(10, 'w') == 10)) {
    return false;
  }
  if (!assert_true("get_next_col_6", get_next_col(10, 'a') == 9)) {
    return false;
  }
  if (!assert_true("get_next_col_7", get_next_col(10, 's') == 10)) {
    return false;
  }
  if (!assert_true("get_next_col_8", get_next_col(10, 'd') == 11)) {
    return false;
  }
  if (!assert_true("get_next_col_9", get_next_col(10, '<') == 9)) {
    return false;
  }
  if (!assert_true("get_next_col_10", get_next_col(10, '>') == 11)) {
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
