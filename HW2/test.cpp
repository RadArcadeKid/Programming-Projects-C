/**
	JAKE HENSON
	Homework 2
	test.cpp - UNIT TESTS - run using ./test after compiling
*/
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Counter.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE ("Checking that the maps work when implemented with integers") {

  Counter<int> numbers;

  numbers.Increment(5);
  SECTION("Check that the increment by 1 works"){
    REQUIRE(numbers.TotalCounts() == 1);
  }
  numbers.Increment(5, 7);
  SECTION("Check that the increment by n works"){
    REQUIRE(numbers.TotalCounts() == 8);
  }
  numbers.Decrement(5);
  SECTION("Check that the decrement by 1 works"){
    REQUIRE(numbers.TotalCounts() == 7);
  }
  numbers.Decrement(5, 6);
  SECTION("Check that decrement by n works"){
    REQUIRE(numbers.TotalCounts() == 1);
  }
  numbers.Decrement(5, 27);
  SECTION("Check that decrement by n is successful in removing"){
    REQUIRE(numbers.TotalCounts() == 0);
  }

  //now actually add a few elements, make sure the most/least common ones work
  numbers.Increment(5, 27);
  numbers.Increment(2, 12);
  numbers.Increment(4, 20);
  numbers.Increment(6, 9);
  //map should look like { 5 : 27 } { 2 : 12 } { 4 : 20 } { 6 : 9 }

  std::vector<int> test_vector_most_common;
  test_vector_most_common.push_back(5);
  test_vector_most_common.push_back(2);
  //std::vector<int> actual_most_common = numbers.MostCommon(2);

  // SECTION("Check that n most common works"){
  //   REQUIRE(numbers.AreVectorsEqual(actual_most_common, test_vector_most_common));
  //   REQUIRE(numbers.AreVectorsEqual(actual_most_common, test_vector_most_common));
  // }

  //crap - where am I getting sefaults from?
}
