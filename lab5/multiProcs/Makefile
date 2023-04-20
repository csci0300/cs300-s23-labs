CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -fsanitize=address

EXECS = revindex_sequential revindex_parallel

all: $(EXECS)

books:
	wget --no-check-certificate https://cs.brown.edu/courses/csci1310/2020/assign/labs/assets/lab6-books.tar.gz
	tar -xzf lab6-books.tar.gz
	rm lab6-books.tar.gz

format:
	clang-format -style=Google -i revindex_procs.cpp

revindex_sequential: books revindex_sequential.cpp wordindex.h
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out $<,$^)

revindex_parallel: books revindex_procs.cpp wordindex.h
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out $<,$^)

check: revindex_sequential revindex_parallel books
	./revindex_sequential books < input.txt > output_sequential.txt
	./revindex_parallel books < input.txt > output_parallel.txt
	diff output_parallel.txt output_sequential.txt

clean:
	rm -f $(EXECS)

.PHONY: all check clean
