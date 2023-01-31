#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reverse.h"

static int total_tests = 0;
static int num_correct = 0;
static int num_incorrect = 0;

#define USAGE "\"./reverse_test\" runs reverse tests"

/**
 * checks if the elements are properly reversed and returns an
 * error message if not
 */
void assert_equal(char** expected, char** actual, const char* message,
                  int len) {
  total_tests++;
  int element_correct = 0;
  int element_incorrect = 0;

  for (int i = 0; i < len; i++) {
    if (!strcmp(expected[i], actual[i])) {
      element_correct++;
      if (element_correct == len) num_correct++;
    } else {
      element_incorrect++;
      if (element_correct == len) num_incorrect++;
      printf("\033[0;31m"); //set color to red
      printf(
          "[FAILED Test %d: %s]: At index: %d, expected string: %s, actual "
          "string: %s\n",
          total_tests, message, i, expected[i], actual[i]);
      printf("\033[0m"); //reset text to default color
    }
  }

  //If no elements are wrong, the test passed! Print a message that says this :)
  if (element_incorrect == 0){
    printf("\033[0;32m"); //set color to green
    printf("[PASSED Test %d: %s]\n", total_tests, message);
    printf("\033[0m"); //reset text to default color
  }

}

/**
 * Runs tests for student implementation of reverse
 */
void test_reverse() {
  // test 1: test single element
  char* str[] = {"hello"};
  reverse_arr(str, 1);
  assert_equal(str, str, "one element test", 1);

  // test 2: test three elements (odd number of elements)
  char* str2[] = {"hello", "my", "name"};
  char* reverse2[] = {"name", "my", "hello"};
  reverse_arr(str2, 3);
  assert_equal(str2, reverse2, "three element test", 3);

  // test 3: test four elements (even number of elements)
  char* str3[] = {"hello", "my", "name", "is"};
  char* reverse3[] = {"is", "name", "my", "hello"};
  reverse_arr(str3, 4);
  assert_equal(str3, reverse3, "four element test", 4);

  // test 4: test five elements
  char* str4[] = {"i", "love", "systems", "csci", "300"};
  char* reverse4[] = {"300", "csci", "systems", "love", "i"};
  reverse_arr(str4, 5);
  assert_equal(str4, reverse4, "five element test", 5);

  // test 5: test 2 elements
  char* str5[] = {"csci", "300"};
  char* reverse5[] = {"300", "csci"};
  reverse_arr(str5, 2);
  assert_equal(str5, reverse5, "two element test", 2);

  // to write your own tests
  // 1. declare a char* array to be reversed (actual)
  // 2. declare a char* array which is the expected result of the reversed array
  // (expected)
  // 3. pass in the first char* arry to the function reverse_arr
  // 4. call the function assert_equal and pass in actual, expected, a message
  // for the test, and
  //    number of elements to be reversed
}

/**
 * prints a summary based on the number of tests passed and failed
 */
void print_test_summary() {
  printf("Passed %d tests, Failed %d tests | %f%%\n", num_correct,
         num_incorrect,
         100 * ceil((float)num_correct) / (total_tests == 0 ? 1 : total_tests));
  total_tests = 0;
  num_incorrect = 0;
  num_correct = 0;
}

/**
 * runs the function passed in and prints a test summary
 */
void run_test(void (*func)(), const char* message) {
  printf("=================== Running %s Tests. ===================\n",
         message);
  func();
  printf("%s: ", message);
  print_test_summary();
}

/**
 * In part 2 of this lab, you will change main so that if argc is > 1 then you
 * reverse the use inputted array but if the argc is less than or equal to one,
 * then the test suite will be run.
 *
 * You will also need to error check to make sure that the number of elements is
 * the same as the number of elements to be reversed.
 *
 * ./reverse_test 1 hello --> is fine
 * ./reverse_test 2 hello --> not fine, missing one element
 * In the second case you would print out the message "Incorrect number of
 * arguments" you should also return 1 to let the operating system know that
 * there is an error.
 *
 * i.e. argv[1] --> number of elements, thus argc - 2 == atoi(argv[1])
 */
int main(int argc, char** argv) {
  int num_elements = atoi(argv[1]);

  char* arr[num_elements];
  for (int i = 0; i < num_elements; i++) {
    arr[i] = argv[i + 2];
  }

  reverse_arr(arr, num_elements);

  for (int i = 0; i < num_elements; i++) {
    printf("%s ", arr[i]);
  }
  printf("\n");

  printf("Testing for correctness...\n");
  // passes the function test_reverse to run_test
  run_test(&test_reverse, "Reverse");

  return 0;
}