#include "calculator.hpp"
#include <cstdlib>
#include <iostream>

main() 
{
    calculator calc;

    calc.readInEquation(calc.getEquation());
    calc.processEquation(calc.getEquation());

}