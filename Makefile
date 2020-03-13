all: maze

maze: maze.cpp
	$(CXX) -o maze maze.cpp

clean:
	rm -f maze

.PHONY: all clean
