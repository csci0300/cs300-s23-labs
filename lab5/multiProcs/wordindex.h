#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

using namespace std;

/*
 * A class to contain the search results for a word in a file
 */
class wordindex {
 public:
  int count = 0;    // the total occurrences of the search term in this file
  string filename;  // the name of the file corresponding to this index object
  vector<int> indexes;  // the indices of each occurrence of the search term in
                        // this file
  vector<string> phrases;  // all of the phrases in which the search term was
                           // found in this file
};

/* Helper function to clean up a word read from file
 * makes the word all lower case and removes extraneous punctuation
 *
 * Arguments: a string, word
 * Return value: the cleaned up version of the argument string
 */
string clean_word(string word) {
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  int trailing = 0;
  for (int i = word.length() - 1; i >= 0; i--) {
    if (word[i] != 39 && ispunct(word[i])) {  // 39 = '
      trailing++;
    } else {
      break;
    }
  }
  if (trailing > 0) {
    word.erase(word.length() - trailing, trailing);
  }

  return word;
}

/* Helper function which joins a list of individual words into a single phrase
 *
 * Arguments: a list of strings, words
 * Return value: a single string containing all of the contents of words
 * seperated by spaces
 */
string join_string(list<string> words) {
  string phrase = "";
  for (auto& str : words) {
    phrase += str + " ";
  }
  phrase.pop_back();  // removes last space
  return phrase;
}

/* Reads individual words from a file and compares them with a target search
 * term.
 *
 * When a matching word is found, the location of word and phrase in which
 * the word is contained is added to the index argument.
 *
 * Arguments: a pointer to a wordindex class object to contain the results
 *            of the search, i
 *            a string representing the search term, target
 * Return value: none
 */
void find_word(wordindex* i, string target) {
  FILE* file = fopen(i->filename.c_str(), "r");
  if (!file) {
    return;
  } else {
    int loc = 1;
    std::list<int> indices;
    std::list<string> context;

    while (1) {
      char buf[255];
      if (fscanf(file, "%s", buf) != EOF) {
        string word(buf);
        string edited_word = clean_word(word);
        // keep track of matching indices
        if (target.compare(edited_word) == 0) {
          indices.push_back(loc);
        }

        // keep a running list of the last 5 words as context
        if (loc > 5) {
          context.pop_front();
        }
        context.push_back(word);

        // once the current location is two words past a
        // matching index add the matching index and phrase to target.
        if (indices.size() > 0 && loc == (indices.front() + 2)) {
          string phrase = join_string(context);
          i->phrases.push_back(phrase);
          i->indexes.push_back(indices.front());
          indices.pop_front();
        }

        // increment the location
        loc++;
      } else {
        break;
      }
    }
    while (indices.size() > 0) {
      string phrase = join_string(context);
      i->phrases.push_back(phrase);
      i->indexes.push_back(indices.front());
      indices.pop_front();
    }
    fclose(file);
    i->count = i->indexes.size();

    return;
  }
}

/* Function to print the results of a given search term on a directory of files
 *
 * Prints total occurrences of the search term in the directory, as well as each
 * file's name followed by the locations in which the word was found and the
 * phrase it was found in at that location
 *
 * Arguments: a string containing the search term, term
 *            an integer representing the total number of instances of
 *            term in the directory, num_occurrences
 *            a vector of index class objects containing the search results of
 *            each file, files
 * Return value: None
 */
void printOccurrences(string term, int num_occurrences,
                      vector<wordindex>& files) {
  printf("Found %d instances of %s.\n", num_occurrences, term.c_str());
  for (auto& f : files) {
    if (f.indexes.size()) {
      printf("%s found in %s at locations:\n", term.c_str(),
             f.filename.c_str());
      int num = 0;
      for (auto itr = f.indexes.begin(); itr != f.indexes.end(); itr++) {
        printf("Index %d: %s\n", *itr, f.phrases[num].c_str());
        num++;
      }
      printf("\n");
    } else {
      printf("%s not found in %s\n", term.c_str(), f.filename.c_str());
    }
    f.indexes.clear();
    f.phrases.clear();
  }
}

/* A function to get all of the filenames of files in a directory
 *
 * Arguments: a reference to a vector of strings to contain the filenames,
 *            filenames
 *            a char* refering to the name of the directory, dirname
 */
void get_files(vector<string>& filenames, char* dirname) {
  DIR* dir = opendir(dirname);
  if (dir == NULL) {
    fprintf(stderr, "Opening directory failed\n");
    exit(1);
  }

  string dirname_base = string(dirname) + "/";
  struct dirent* ent;
  while ((ent = readdir(dir)) != NULL) {
    if (ent->d_name[0] != '.') {
      string name(ent->d_name);
      filenames.push_back(dirname_base + name);
    }
  }
  closedir(dir);
}
