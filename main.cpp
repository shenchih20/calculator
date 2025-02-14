#include <iostream>
#include <string>
#include "calculator.hpp"


int main()
{
    std::string str;
    std::cout << "please enter : \n\n";
    std::getline(std::cin, str);
    calc::Calculator calc;
    return calc.parse_string(str);
}
