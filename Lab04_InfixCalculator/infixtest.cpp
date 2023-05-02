#include <iostream>
#include <string>
#include "MyInfixCalculator_c747b428.h"

int main(){
    MyInfixCalculator j;
    std::string s = "-268.639*294.942-322.883*199.061/(44.54--206.692)--86.817/(-141.676--227.806)+434.193/-173.796";
    std::cout << j.calculate(s) << std::endl;
    return 0;
}