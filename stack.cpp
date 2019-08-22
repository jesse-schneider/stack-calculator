#include "stack.hpp"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <algorithm>

//default ctor
stack::stack() : stackSize{0}, stackArr{new int[256]} { }

//copy ctor
stack::stack(stack const & that) : stackSize{that.stackSize}, stackArr{new int [256]{}} 
{  for(int i = 0; i < stackSize; i++) { stackArr[i] = that.stackArr[i]; }}

//move ctor
stack::stack(stack && that) noexcept : stackSize{std::move(that.stackSize)}, stackArr{std::move(that.stackArr)}
{   that.stackArr = nullptr; }

//copy assignment
stack & stack::operator = (stack const & that)
    {
        if(this == &that) return *this;
        if (stack::stackSize != that.stackSize)
        { delete [] stackArr; stackSize = that.stackSize; stackArr = new int [256];
            for(int i = 0; i < stackSize; i++)
            { stackArr[i] = that.stackArr[i]; }
        }
    }

 //move assignment
stack & stack::operator = (stack && that) noexcept
{
    stackSize = std::move(that.stackSize); stackArr = std::move(that.stackArr);
    that.stackArr = nullptr;
    return *this;
}

//dtor
stack::~stack() { delete [] stackArr; }

int stack::getStackSize()
{
    return stackSize;
}

void stack::setStackSize(int stackSize)
{
    this->stackSize = stackSize;
}

int stack::getNextInt(int deduct)
{
    if (stackSize == 0)
    {
        return stackArr[0];
    }
    else
    {
        return stackArr[stackSize-deduct];
    }
}

void stack::push(int number)
{ 
    stackArr[getStackSize()] = number;
    setStackSize(getStackSize()+1);
}

int stack::pop()
{
    if(getNextInt(-1) == -1)
    {
        std::cout << "Stack empty" << std::endl;
        return -1;
    }

    int pop = stackArr[getStackSize()-1];
    stackArr[getStackSize()-1] = '\0';
    setStackSize(getStackSize()-1);
    return pop;
}

void stack::print()
{
    for(int i = 0; i < getStackSize(); i++)
    {
        std::cout << stackArr[i] << " ";
    }
    std::cout << std::endl;
}

void stack::printC()
{
    for(int i = 0; i < getStackSize(); i++)
    {
        std::cout << static_cast<char>(stackArr[i]) << " ";
    }
    std::cout << std::endl;
}