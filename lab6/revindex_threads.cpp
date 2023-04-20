#include <thread>
#include "wordindex.h"

using namespace std;

/*TODO
 * Fill in this function so that it creates a series of threads to execute
 * find_word over different files in parallel.
 *
 * Arguments:
 *     - files: a reference to a vector of wordindex class objects meant to hold
 *       the search results of all files.
 *     - filenames: a vector containing strings of all of filenames in the
 *       directory,
 *     - start_pos: an integer representing the index of the file in filenames
 *       that this batch of threads should start with.
 *     - num_threads: an integer representing the number of threads that should
 *       be created in this round.
 *     - word: a string containing the desired search term.
 * Return value: an integer representing the total occurrences of the search
 * term in this batch of files.
 */
int run_workers(vector<wordindex>& files, vector<string> filenames,
                int start_pos, int num_threads, string word) {
  // for each thread in num_threads:
  // 1) create a new index object for the file being processes by the thread and
  //    add it to the files vector
  // 2) create the thread to run find_word with the proper arguments

  // join with each thread and add the count field of each index to the total
  // sum

  // return the total sum for this batch of files
  return 0;
}

/* The main REPL for the program
 * continually reads input for stdin, searches for that input in a directory of
 * files, and prints the results
 *
 * Arguments: char* containing the name of the  * directory to search
 *            through, dirname
 * Return value: None
 */
void repl(char* dirname) {
  int num_files = 0;
  int workers = 8;
  vector<wordindex> files;
  vector<string> filenames;

  // read all files from directory
  get_files(filenames, dirname);
  num_files = filenames.size();

  files.reserve(num_files);

  printf("Enter search term: ");
  char buf[255];
  fgets(buf, 255, stdin);
  while (!feof(stdin)) {
    int len = char_traits<char>::length(buf) - 1;
    string term(buf, len);
    if (term.length() > 0) {
      int num_occurrences = 0;
      transform(term.begin(), term.end(), term.begin(), ::tolower);

      int completed = 0;
      while (completed < num_files) {
        // determine number of threads for this round
        int num_threads = 0;
        if ((num_files - completed) > workers) {
          num_threads = workers;
        } else {
          num_threads = num_files - completed;
        }

        // increment the total number of occurrences of the search term by the
        // sum of the occurrences from this batch of files files is passed by
        // reference so that additions to the vector in run_workers is visable
        // back in this function
        num_occurrences +=
            run_workers(files, filenames, completed, num_threads, term);

        // update the number of completed files
        completed += num_threads;

        // move on to next batch of "workers" amount of files
      }

      // print the results
      printOccurrences(term, num_occurrences, files);
    }

    printf("\nEnter search term: ");
    files.clear();

    fgets(buf, 255, stdin);
  }
  return;
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
