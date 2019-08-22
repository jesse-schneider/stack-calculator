#include "calculator.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

//default ctor
calculator::calculator() : integers{new int[256]}, intLength{0}, precedence{0, 1, 1, 2, 2, 3, 3, 4}, equation{""} { }

//copy ctor
calculator::calculator(calculator const & that) : integers{new int[256]}, intLength{that.intLength}, equation{that.equation} 
{  for(int i = 0; i < 256; i++) { integers[i] = that.integers[i]; }}

//move ctor
calculator::calculator(calculator && that) noexcept : integers{std::move(that.integers)}, intLength{std::move(that.intLength)}, equation{std::move(that.equation)}
{   that.integers = nullptr; }

//copy assignment
calculator & calculator::operator = (calculator const & that)
    {
        if(this == &that) return *this;
        if (calculator::equation != that.equation)
        { delete [] integers; intLength = that.intLength; equation = that.equation; integers = new int [256];
            for(int i = 0; i < 256; i++)
            { integers[i] = that.integers[i]; }
        }
    }

 //move assignment
calculator & calculator::operator = (calculator && that) noexcept
{
    intLength = std::move(that.intLength);equation = std::move(that.equation); integers = std::move(that.integers);
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

int calculator::getIntLength()
{
    return intLength;
}
void calculator::setIntLength(int intLength)
{
    this->intLength = intLength;
}


void calculator::readInEquation(std::string equation)
{
    std::cout << "Please enter the maths equation: " << std::endl;
    std::getline(std::cin, equation);
    setEquation(equation);
}

void calculator::processEquation(std::string equation)
{
    std::string fullNum;
    for(int i = 0; i <= equation.length(); i++)
    {
        char c = equation[i];
        char d = equation[i+1];
        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^')
        {
            switch (c)
            {
                case '(':
                    integers[getIntLength()] = -2;
                    setIntLength(getIntLength()+1);
                    break;
                case ')':
                    integers[getIntLength()] = -3;
                    setIntLength(getIntLength()+1);
                    break;
                case '+':
                    integers[getIntLength()] = -4;
                    setIntLength(getIntLength()+1);
                    break;
                case '-':
                    integers[getIntLength()] = -5;
                    setIntLength(getIntLength()+1);
                    break;
                case '*':
                    integers[getIntLength()] = -6;
                    setIntLength(getIntLength()+1);
                    break;
                case '/':
                    integers[getIntLength()] = -7;
                    setIntLength(getIntLength()+1);
                    break;
                case '^':
                    integers[getIntLength()] = -8;
                    setIntLength(getIntLength()+1);
                    break;
            }
        }

        if(isdigit(c) != 0)
        {
            if(isdigit(d) != 0)
            {
                fullNum += c;
            }
            else 
            {
                fullNum += c;
                std::stringstream ss(fullNum);
                int variable = 0;
                ss >> variable;
                integers[getIntLength()] = variable;
                setIntLength(getIntLength()+1);
                fullNum = "";
            } 
        }
    }
    for (int i = 0; i < getIntLength(); i++)
        std::cout << integers[i] << std::endl;
}

void calculator::calculate()
{
    //create stacks
    stack operators;
    stack operands;
    operators.push(-1);

    //iterate over integers array
    for (int i = 0; i < getIntLength(); i++)
    {
        if(integers[i] < 0)
        {
            if(integers[i] == -3)
            {
                //keep popping until '(', then pop 2 operands for each operator
                int pop[10];
                int temp;
                while(1)
                {
                    pop[temp] = operators.pop();
                    if(pop[temp] == -2)
                        break;
                    temp++;
                }
                for(int i = 0; i < temp; i++)
                {
                    //perform calculation
                    int operandOne = operands.pop();
                    int operandTwo = operands.pop();
                    int operate = pop[i];
                    int result = performCalc(operandOne, operandTwo, operate);
                    //push back to operand stack
                    operands.push(result);
                }  
            }
            if(checkPrecedence(i, precedence, integers, operators) == true)
            {
                operators.push(integers[i]);
             }
            else 
            {
                while(checkPrecedence(i, precedence, integers, operators) == false)
                {
                    //pop last operator, 2 operands, perform calculation, and push result back into operands
                    if(operands.getStackSize() <= 1 || operators.getNextInt(1) == -2 || operators.getNextInt(1) == -3)
                        break;
                    int operate = operators.pop();
                    int operandOne = operands.pop();
                    int operandTwo = operands.pop();
                    int result = performCalc(operandOne, operandTwo, operate);
                    operands.push(result);
                }
                operators.push(integers[i]);
            }
        }
        else if(integers[i] > 0)
        {
            operands.push(integers[i]);
        }
    }
    while(operands.getStackSize() > 1)
    {
        int operate = operators.pop();
        int operandOne = operands.pop();
        int operandTwo = operands.pop();
        int result = performCalc(operandOne, operandTwo, operate);
        operands.push(result);
    }
    std::cout << "The answer is ";
    operands.print();
}

int calculator::performCalc(int opOne, int opTwo, int operate)
{  
    int result;
     switch (operate)
            {
                case -4:
                    result = opTwo + opOne;
                    break;
                case -5:
                    result = opTwo - opOne;
                    break;
                case -6:
                    result = opTwo * opOne;
                    break;
                case -7:
                    result = opTwo / opOne;
                    break;
                case -8:
                result = opTwo;
                    for(int i = 0; i < opOne-1; i++)
                    {
                        result *= opTwo;
                    }
                    break;
            }
        return result;
}

bool calculator::checkPrecedence(int i, int precendence[], int integers[], stack operators)
{
   if(precedence[-integers[i]-1] > precedence[-operators.getNextInt(1)-1])
   {
       return true;
   }
   else 
   {
       return false;
   }
}

void calculator::displayString()
{
    //create stacks
    stack operators;
    stack operands;
    operators.push(-1);
    std::string postfix;

    //iterate over integers array
    for (int i = 0; i < getIntLength(); i++)
    {
        if(integers[i] < 0)
        {
            if(integers[i] == -3)
            {
                int pop[10];
                int temp;
                while(1)
                {
                    pop[temp] = operators.pop();
                    if(pop[temp] == -2)
                        break;
                    temp++;
                }
                for(int i = 0; i < temp; i++)
                {
                    int operate = pop[i];
                    operands.push(operate);
                }
                continue;
            }
            if(checkPrecedence(i, precedence, integers, operators) == true)
            {
                operators.push(integers[i]);
             }
            else 
            {
                while(checkPrecedence(i, precedence, integers, operators) == false)
                {
                    if(operands.getStackSize() <= 1 || operators.getNextInt(1) == -2 || operators.getNextInt(1) == -3)
                        continue;
                    int operate = operators.pop();
                    operands.push(operate);
                }
                operators.push(integers[i]);
            }
        }
        else if(integers[i] > 0)
        {
            operands.push(integers[i]);
        }
    }
    for (int i = 0; i < operands.getStackSize(); i ++)
    {
        if(operands.getStack()[i] < 0)
        {
            switch (operands.getStack()[i])
            {
                case -4:
                    operands.getStack()[i] = '+';
                    break;
                case -5:
                    operands.getStack()[i] = '-';
                    break;
                case -6:
                    operands.getStack()[i] = '*';
                    break;
                case -7:
                    operands.getStack()[i] = '/';
                    break;
                 case -8:
                    operands.getStack()[i] = '^';
                    break;
            }
        }
    }
    std::cout << "The Post-fix Notation ";
    operands.printC();
}