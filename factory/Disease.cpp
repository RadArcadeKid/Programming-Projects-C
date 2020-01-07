#include <iostream>
#include <string>

#include "Disease.h"

int Disease::counter_ = 0; //because this is static you have to initialize it here


std::ostream& operator<<(std::ostream &os, const Disease &d) {
    os << d.get_name();
    // TODO: print out more information if you want to
    os << d.get_count();
    return os;
}



Disease * DiseaseFactory::GetFlu(){
    return new Disease("flu", true, false, false, true, 0.5, 0.5, 0.5, 0.1, "Denver");
}

Disease * DiseaseFactory::GetCold(){
    return new Disease("cold", true, false, true, true, 0.1, 0.2, 0.4, 0.3, "Boston");
}


Disease * DiseaseFactory::GetMalaria(){
    return new Disease("malaria", true, true, false, true, 0.8, 0.8, 0.9, 0.9, "Africa");
}
