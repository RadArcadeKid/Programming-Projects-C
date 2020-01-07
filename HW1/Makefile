CXX = g++
CXXFLAGS	= -std=c++11 -Wall

all: maze

clean:
	rm Player.o Maze.o maze

maze: Player.o Maze.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Player.o Maze.o -o maze

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

Maze.o: Maze.cpp
	$(CXX) $(CXXFLAGS) -c Maze.cpp
