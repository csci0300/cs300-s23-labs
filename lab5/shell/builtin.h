#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>

using namespace std;

void cd_command(int argc, char** argv);
void ln_command(int argc, char** argv);
void rm_command(int argc, char** argv);
void exit_command(int argc);
