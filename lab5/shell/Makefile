CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-align -g -fsanitize=address

.PHONY: all clean format

all: 300sh

format:
	clang-format -style=Google -i *.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

300sh: sh.o builtin.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f 300sh *.o
