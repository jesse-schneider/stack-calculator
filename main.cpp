#include "stack.hpp"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>

main() 
{
    stack operators;
    stack operands;
    operators.push(static_cast<int>('$'));

    std::string equation;

    std::cout << "Please enter the maths equation: " << std::endl;
    std::getline(std::cin, equation);

    std::string variable = "";
    int variableInt;
    for(int i = 0; i <= equation.length(); i++)
    {
        if( equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '(' || equation[i] == ')')
            {
                operators.push(static_cast<int>(equation[i]));
                continue;
            }
        if(equation[i] == ' ' || i == equation.length())
        {
            std::stringstream ss (variable);
            ss >> variableInt;
            if(variableInt == 0)
                continue;
            operands.push(variableInt);
            variable = ""; variableInt = 0;
        }
        else
        {
            variable = variable + equation[i];
        }
    }

    operators.printC();
    operands.print();

}