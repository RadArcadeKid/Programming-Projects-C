#include <iostream>
#include <string>
#include <vector>

// Names:
// Jake Henson
// Danny Camarena


struct new_struct{
    int new_int_;
};

//solve the problem of generalizing things in a statically typed language
//prevents copy + pasting
//templates allow new/custom objects

template <typename T>
// T Add(T i1, T i2){
//   return i1 + i2;
// }

// 6) implement a templated version of AddToValues, "AddToValues2".
std::vector<T> AddToValues2(std::vector<T> v1, T v2){
  for(unsigned int i = 0; i < v1.size(); i++){
    v1[i] = v1[i] + v2;
  }
  return v1;
}

int main() {
    // 7) call AddToValues2, passing in an int vector and another int.
    std::vector<int> v_new = {0, 1, 2, 3, 4, 5, 6};
    AddToValues2(v_new, 2);

    // 8) compile this file to object code (g++ -std=c++11 -Wall exercises2.cpp -o exercises2.o),
    // then run `nm -C exercises2.o`. How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here:
    //
    //0000000000000dcc W std::vector<int, std::allocator<int> > AddToValues2<int>(std::vector<int, std::allocator<int> >, int)


    // 9) call AddToValues2, passing in a vector of a non-int type and a value that you can add
    // successfully to the elements
    std::vector<double> v_new2 = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    AddToValues2(v_new2, 2.5);

    // 10) compile this file to object code (g++ -std=c++11 -Wall exercises2.cpp -o exercises2.o),
    // then run `nm -C exercises2.o`. How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here: called twice
    // 00000000000011ce W std::vector<double, std::allocator<double> > AddToValues2<double>(std::vector<double, std::allocator<double> >, double)
    // 0000000000000ec6 W std::vector<int, std::allocator<int> > AddToValues2<int>(std::vector<int, std::allocator<int> >, int)

    //

    // 11) Experiment to find calls to this function that you would like to work but that do
    // not yet work. for each function call that doesn't work, comment about what type of
    // error is produced.
    // AddToValues2(v_new2, "two"); -- note:   deduced conflicting types for parameter ‘T’ (‘double’ and ‘const char*’)
    //AddToValues2(v_new2, 7); --  deduced conflicting types for parameter ‘T’ (‘double’ and ‘int’)


    // 12) Create a struct that has an int field. Instantiate a vector of these structs.
    // Instantiate another instance of this struct.
    std::vector<new_struct> v3;
    new_struct s1;
    s1.new_int_ = 5;
    for(int i = 0; i < 4; i++){
      v3[i]=s1;
    }



    // 13) Call AddToValues2 w/ the vector of structs and single struct from #12
    // Is there an error? If yes, what is it?
    AddToValues2<new_struct>(v3, s1);
    //
    // Answer: Yes, there's an error - no match for ‘operator+’ (operand types are ‘__gnu_cxx::__alloc_traits<std::allocator<new_struct> >::value_type {aka new_struct}’ and ‘new_struct’)
    // v1[i] = v1[i] + v2;


    // 14) If there was an error, attempt to fix it.
    //use friend and override the operator "+"

}



/// -- // sytax for templates class:
// template <class T>
// class Name{
//
// };
