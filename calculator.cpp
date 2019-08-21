#include "calculator.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

//default ctor
calculator::calculator() : integers{new int[256]}, precedence{0, 1, 1, 2, 2, 3, 3}, equation{""} { }

//copy ctor
calculator::calculator(calculator const & that) : equation{that.equation}, integers{new int[256]}
{  for(int i = 0; i < 256; i++) { integers[i] = that.integers[i]; }}

//move ctor
calculator::calculator(calculator && that) noexcept : equation{std::move(that.equation)}, integers{std::move(that.integers)}
{   that.integers = nullptr; }

//copy assignment
calculator & calculator::operator = (calculator const & that)
    {
        if(this == &that) return *this;
        if (calculator::equation != that.equation)
        { delete [] integers; equation = that.equation; integers = new int [256];
            for(int i = 0; i < 256; i++)
            { integers[i] = that.integers[i]; }
        }
    }

 //move assignment
calculator & calculator::operator = (calculator && that) noexcept
{
    equation = std::move(that.equation); integers = std::move(that.integers);
    that.integers = nullptr;
    return *this;
}

//dtor
calculator::~calculator() { delete [] integers; }

std::string calculator::getEquation()
{
    return equation;
}

void calculator::setEquation(std::string equation)
{
    this->equation = equation;
}


void calculator::readInEquation(std::string equation)
{
    std::cout << "Please enter the maths equation: " << std::endl;
    std::getline(std::cin, equation);
    setEquation(equation);

    for(int i = 0; i < equation.length(); i++)
    {
        //fill array integers and precendence
    }
}


void calculator::processEquation(std::string equation)
{
    stack operators;
    stack operands;
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
            variable = ""; 
            variableInt = 0;
        }
        else
        {
            variable = variable + equation[i];
            std::cout << "variable: " << variable << std::endl;
        }
    }

    operands.print();
    operators.printC();
}