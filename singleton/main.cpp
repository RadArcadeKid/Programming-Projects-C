#include <iostream>
#include "Earth.h"

//JAKE HENSON
//IN CLASS LECTURE

int main(int argc, char **argv){
    // 0) Implement your Earth's constructor in Earth.cpp

    // 1) Get an instance of your earth object
		Earth &earth1=Earth::GetInstance();
    // 2) Get another instance of your earth object
		Earth &earth2=Earth::GetInstance();
    // 3) Test to see if the two Earth instances from #1 and #2 are stored at the same
    // location in memory.
		if(&earth1 == &earth2){
			std::cout<<"Earth1 and Earth2 are stored in the same spot" << std::endl;
		}
		else{
			std::cout<<"Earth1 and Earth2 are NOT in the same spot" << std::endl;
		}

    // 3) Call IncreasePopulation from one of your Earth instances. Can you see this change
    // from your other Earth instance?
		std::cout<<"earth1 population before changing: " << earth1.get_population()<<std::endl;
		earth2.IncreasePopulation();
		std::cout<<"earth1 population after changing earth2: " << earth1.get_population()<<std::endl;

    // 4) Create a public field in your Earth object. Do you need an instance of an Earth object
    // to access this field?
		//if it's not static you can't access it without an instance
		//non-static

	return 0;
}
