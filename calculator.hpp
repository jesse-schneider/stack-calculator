#include <cstdlib>
#include <iostream>
#include "stack.hpp"

class calculator {

    public:
        //6 essential methods
        //default ctor
        calculator();
        calculator(int pSize);
        //copy ctor
        calculator(calculator const & that);
        //cpy assignment
        calculator(calculator && that) noexcept;
        //move ctor
        calculator & operator = (calculator const & that);
        //move assignment
        calculator & operator = (calculator && that) noexcept;
        //dtor
        ~calculator();

        std::string getEquation();
        void setEquation(std::string equation);
        stack getOperators();
        void setOperators(stack operators);
        stack getOperands();
        void setOperands(stack operands);

        void readInEquation(std::string equation);
        void processEquation(std::string equation);

        void displaystacks();

    private:
        int *integers = new int[256];
        int precedence[7];
        std::string equation;
};