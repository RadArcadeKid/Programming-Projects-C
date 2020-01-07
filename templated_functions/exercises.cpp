#include <iostream>
#include <string>
#include <vector>

// Names:
// Jake Henson
// Danny Camarena


// 1) implement two functions, AddToValues(std::vector<int> v1, int v2)
// and AddToValues(std::vector<double> v1, double v2)

/**
  AddToValues (as an int) adds @int v2 to every element in the vector
*/
std::vector<int> AddToValues(std::vector<int> v1, int v2){
    for(unsigned int i = 0; i < v1.size(); i++){
      v1[i] += v2;
    }
    return v1;
}

/**
  AddToValues (as an int) adds @double v2 to every element in the vector
*/
std::vector<double> AddToValues(std::vector<double> v1, double v2){
    for(unsigned int i = 0; i < v1.size(); i++){
      v1[i] += v2;
    }
    return v1;
}


 // 2) Do your AddToValues functions have return values? why/ why not?
 // Answer: Vectors are pass by value, so both functions need return values


int main() {
    // 3) Instantiate an int vector

    std::vector<int> v_new = {0, 1, 2, 3, 4, 5, 6};

    // 4) call AddToValues, passing in your int vector and another int.
    AddToValues(v_new, 2);

    // 5) compile this file to object code (g++ -std=c++11 -Wall exercises.cpp -o exercises.o),
    // then run `nm -C exercises.o`. How many versions of the AddToValues function are in the
    // compiled object code? Copy + paste the relevant lines here:
        //       0000000000000c0e t _GLOBAL__sub_I__Z11AddToValuesSt6vectorIiSaIiEEi
        // 0000000000000a3d T AddToValues(std::vector<double, std::allocator<double> >, double)
        // 00000000000009ca T AddToValues(std::vector<int, std::allocator<int> >, int)

    // To making searching through the output easier, you can pipe the output of nm to grep
    // `nm -C exercises.o | grep "TextToFindHere"`
    //
    // If the -C flag isn't working, you can omit it and still complete the exercise--this flag
    // makes the output easier to read but isn't strictly necessary
}
