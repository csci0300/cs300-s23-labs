#include "builtin.h"

using namespace std;

/*
 * Changes the current working directory
 * Parameters:
 *      - argc: the number of arguments
 *      - argv: the command line arguments
 */
void cd_command(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "cd: syntax error\n");
  } else {
    if (chdir(argv[1]) < 0) {
      perror("cd");
    } else {
      printf("Current directory is now %s\n", argv[1]);
    }
  }
}

/*
 * Creates a symbolic link
 * Parameters:
 *      - argc: the number of arguments
 *      - argv: the command line arguments
 */
void ln_command(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "ln: syntax error\n");
  } else {
    if (link(argv[1], argv[2]) < 0) {
      perror("ln");
    }
  }
}

/*
 * Unlinks a file
 * Parameters:
 *      - argc: the number of arguments
 *      - argv: the command line arguments
 */
void rm_command(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "rm: syntax error\n");
  } else {
    if (unlink(argv[1]) < 0) {
      perror("rm");
    }
  }
}

/*
 * Exits the shell
 * Parameters:
 *      - argc: the number of arguments
 */
void exit_command(int argc) {
  if (argc < 1) {
    fprintf(stderr, "exit: syntax error\n");
  } else {
    exit(0);
  }
}
