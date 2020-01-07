/**
  JAKE HENSON
	Homework 2
	main.cpp - run using ./main after compiling
*/
#include "Counter.h" //need to include the header file to access the functions
#include <string>
#include <iostream>

int main(){
    Counter<int> numbers;
    Counter<std::string> words;

    std::map<int,int> int_test_map;
    std::map<std::string,int> words_test_map;

    int_test_map.insert({1, 5}); //insert 5 at key value 1

    numbers.Increment(5);
    numbers.Increment(4, 2);

    words.Increment("cats", 1);

    std::cout << numbers << std::endl; //prints out the map
}
