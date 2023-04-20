#include <fcntl.h>
#include <sys/mman.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include "wordindex.h"

using namespace std;

int process_input(string term, vector<string>& filenames) {
  int workers = filenames.size();
  int num_occurrences = 0;
  vector<wordindex> fls;
  for (int w = 0; w < workers; w++) {
    wordindex file;
    file.filename = filenames[w];
    find_word(&file, term);
    num_occurrences += file.indexes.size();
    fls.push_back(file);
  }
  printOccurrences(term, num_occurrences, fls);
  return 0;
}

void repl(char* dirname) {
  // read dir
  vector<string> filenames;
  get_files(filenames, dirname);

  printf("Enter search term: ");
  for (string term = ""; getline(cin, term);) {
    int err = process_input(term, filenames);
    if (err < 0) {
      printf("%s: %d\n", "ERROR", err);
    }
    printf("\nEnter search term: ");
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Expected arguments: files to search through\n");
    exit(1);
  }

  char* dirname = argv[1];

  repl(dirname);

  exit(0);
}
