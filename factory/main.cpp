#include <iostream>
#include <vector>

#include "Disease.h"
#include "Creature.h"

// Names: Jacob (Jake) Henson
//
//


int main() {
    // Part 1 (factory)
    // ---------------
    // 4) get pointers to one of each type of your Disease objects via your DiseaseFactory. Then,
    // call the Disease's get_count method to see how many Disease objects have been instantiated.
    Disease * flu = DiseaseFactory::GetFlu();
    Disease * cold = DiseaseFactory::GetCold();
    Disease * malaria = DiseaseFactory::GetMalaria();
    //syntax is DiseaseFacoty::GetCold because the methods are static

    // 5) are your DiseaseFactory's Get____() methods static or non-static? Do you think that they should
    // be one or the other? Justify your answer. If your methods are static, what would change if they were
    // non-static? If they are non-static, what would change if they were static?
    //they are static, I think they should be static so you don't have to make a disease object every time!
    //I don't think they *have to* be static, it's just easier to make them that way

    // 6) Feel free to create more creatures here
    Creature original_creature(14);
    Creature second_creature(28);
    Creature third_creature(4);
    Creature human(25);

    // 7) Infect your creatures with your diseases. Test out the Creature Spread method.
    // Warning: Spread is an _UNTESTED_ method.

    std::cout<<"original_creature: " << std::endl;
    for (Disease * d : original_creature.get_diseases() ) {
        std::cout << *(d) << std::endl;
    }

    std::cout<<"second_creature: " << std::endl;
    for (Disease * d : second_creature.get_diseases() ) {
        std::cout << *(d) << std::endl;
    }

    std::cout<<"third_creature: " << std::endl;
    for (Disease * d : third_creature.get_diseases() ) {
        std::cout << *(d) << std::endl;
    }

    std::cout<<"human: " << std::endl;
    for (Disease * d : huamn.get_diseases() ) {
        std::cout << *(d) << std::endl;
    }


    // STOP! Turn in Disease.h, Disease.cpp, and main.cpp on canvas


    // Part 2 (prototype)
    // ---------------
    // 3) Create some new Creature * objects by using the Creature's Clone() method. Does this method use dynamic dispatch?
    // Answer:
    // How did you test this?





    // If you finish:
    // -------------
    // 4) Write a new function in this file void ScienceLab(Creature * original) (not associated with any classes)
    // that takes an original creature and conducts experiments by cloning it and measuring the spread of disease.
    // You have complete creative freedom here. Feel free to add methods to the Disease/Creature classes.
    // (The only requirements are the function definition and that you must call Clone() within that function).
    //
    // Call your ScienceLab function as many times as is necessary for your experiments.
}
