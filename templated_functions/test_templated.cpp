#include <iostream>
#include <string>
#include <vector>


//template SWAP
template <class T>
T Swap(T & a, T & b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}

main(){
   int a = 1;
   double b = 2.99;

   int * a_ptr = &a;
   int * b_ptr = &b;

   std::cout<< "a =" << a << ", b =" << b << std::endl;
   Swap(a, b);
   std::cout<< "a =" << a << ", b =" << b << std::endl;


   Swap(*a_ptr, *b_ptr);
   std::cout<< "a =" << a << ", b =" << b << std::endl;


   float c = 2.3453;
   float d = 3.3234;
   std::cout<< "c= " << c << "d= " << d << std::endl;
   Swap(c, d);
   std::cout<< "c= " << c << "d= " << d << std::endl;
}
