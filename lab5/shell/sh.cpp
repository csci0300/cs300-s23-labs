#include "builtin.h"

using namespace std;

#define MAX_BUF_SIZE 1024

/*
 * Counts the number of tokens in input_buf separated by characters in delim
 * Arguments:
 *      - input_buf: the string to count the number of tokens in
 *      - delim: a string containing the delimiting characters to split on
 * Return value:
 *      - the number of tokens in input_buf separated by characters in delim
 */
int num_tokens(char* input_buf, string delim) {
  int tokens = 0;

  size_t offset = strspn(input_buf, delim.c_str());
  input_buf += offset;

  while (*input_buf != '\0') {
    // Track to the next character in delim
    offset = strcspn(input_buf, delim.c_str());
    input_buf += offset;

    // Now track to the next character NOT in delim
    offset = strspn(input_buf, delim.c_str());
    input_buf += offset;

    tokens++;
  }

  return tokens;
}

/* TODO
 * Fill in this function to execute the not builtin commands (everything other
 * than cd, ln, rm, exit)
 * Arguments:
 *      - args: a null terminated  array of strings containing all tokens from
 *        the input string.
 *        The first element in args is the full path to the command to be run
 *        The following elements im args are any arguments to that command.
 *        For example, args could be the array: {"/bin/echo", "hello", NULL}
 * Return value: none
 */
void do_fork(char* args[]) {
  /* This function should
   * 1) fork into a child process to execute the function
   * 2) Outside of the child process, wait for the new process to finish
   */
}

/*
 * Executes the parsed input from the shell
 * Arguments:
 *      - args: an array containing all tokens from the input string
 *      - num_args: the total number of arguments
 * Return value: none
 */
void execute_command(char* args[], int num_args) {
  // Handle built in shell commands
  if (strcmp(args[0], "cd") == 0) {
    cd_command(num_args, args);
  } else if (strcmp(args[0], "exit") == 0) {
    exit_command(num_args);
  } else {
    // Hande all other commands
    do_fork(args);
  }
}

/*
 * Parses the input from the shell, and hands it off to be executed
 * Arguments:
 *      - input_buf: the input string from the shell
 * Return value: none
 */
void handle_input(char* input_buf) {
  int num_args = num_tokens(input_buf, "\t\n ");

  char* args[num_args + 1];

  // Tokenize input string and store tokens in array
  // Note that strtok automatically null-terminates the tokens it finds
  int token_num = 0;
  char* token = strtok(input_buf, "\t\n ");
  while (token) {
    args[token_num] = token;
    token = strtok(NULL, "\t\n ");
    token_num++;
  }

  // If there are no arguments, nothing will be executed
  if (num_args <= 0) {
    return;
  }

  // Set last argument to NULL, needed by execv
  args[num_args] = NULL;

  // Execute parsed command
  execute_command(args, num_args);
}

/*
 * The entry point for the shell program
 */
int main() {
  while (1) {
    // print prompt
    printf("300sh> ");
    fflush(stdout);

    // Read from standard input into the input buffer
    char input[MAX_BUF_SIZE];
    fgets(input, MAX_BUF_SIZE, stdin);

    if (ferror(stdin)) {
      // Exit shell if read fails
      fprintf(stderr, "failed to read from stdin\n");
      return 1;
    } else if (feof(stdin)) {
      // Exit shell if EOF is reached
      return 0;
    }

    // Evaluate the input string
    handle_input(input);
  }

  return 0;
}
