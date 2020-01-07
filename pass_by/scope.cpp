#include <iostream>
//JAKE HENSON
//IN CLASS LECTURE

// 1) Write a function that tests whether ints are pass-by-value or pass-by-reference
// (do not use pointers or c++ references in this function)
void passByInt(int numPass){
    numPass += 1;
    std::cout << "INSIDE passByInt after modification: " << numPass << std::endl;
}

// 2) Write a function that tests whether strings (std::string) are pass-by-value or pass-by-reference
// (do not use pointers or c++ references in this function)
void passByString(std::string str){
    str = "...jumped over the lazy dog"; //test string
    std::cout << "INSIDE passByString after modification: " << std::endl;
}

// 3) Write a function that tests whether arrays are pass-by-value or pass-by-reference
// recall: to initialize an array-- type name[] = {comma separated elements};
// (do not use pointers or c++ references in this function)

void passByArray(int arr[3]){

    for(int i=0; i <=2; i++){
        arr[i] = i + 5; //some random value - just as long as it shows change...
    }
}

int main() {
    // code to test your functions goes here.

    //test int
    int num = 5;
    std::cout << "Value of num before calling function: " << num << std::endl;
    passByInt(num);
    std::cout << "Value of num AFTER calling passByInt function: " << num << std::endl;

    //test string
    std::string teststr = "The quick brown fox...";
    std::cout << "Value of string before calling function: " << teststr << std::endl;
    passByString(teststr);
    std::cout << "Value of string AFTER calling passByString function: " << teststr << std::endl;

    //test array
    int array[3] = {0,0,0};
    std::cout << "Values in array before calling function: " << array[0] << ", " << array[1] << ", "  << array[2] << std::endl;
    passByArray(array);
    std::cout << "Value in array AFTER calling passByArray function: " << array[0] << ", " << array[1] << ", "  << array[2] << std::endl;
}
