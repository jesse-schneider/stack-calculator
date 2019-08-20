#include "stack.hpp"
#include <cstdlib>
#include <iostream>


main() 
{
    stack operators;
    stack operands;

    std::string equation;

    std::cout << "Please enter the maths equation: " << std::endl;
    std::cin >> equation;

    operators.push(static_cast<int>('$'));

    operators.printC();

}