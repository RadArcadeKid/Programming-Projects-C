#Jake Henson - HW2 Makefile
CXX = g++
CXXFLAGS    = -std=c++11 -Wall

all: main test
clean:
	rm test main TestTypes.o
main: main.cpp Counter.h TestTypes.o
	$(CXX) $(CXXFLAGS) main.cpp TestTypes.o -o main
TestTypes.o: TestTypes.cpp Counter.h
	$(CXX) $(CXXFLAGS) -c TestTypes.cpp
test: TestTypes.o Counter.h test.cpp
	$(CXX) $(CXXFLAGS) test.cpp TestTypes.o -o test
