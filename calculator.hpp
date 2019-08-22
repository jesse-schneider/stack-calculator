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
        int getIntLength();
        void setIntLength(int intLength);


        void readInEquation(std::string equation);
        void processEquation(std::string equation);

        void calculate();
        int performCalc(int opOne, int opTwo, int operate);
        bool checkPrecedence(int i, int precendence[], int integers[], stack operators);

        void displayString();

    private:
        int *integers = new int[256];
        int intLength;
        int precedence[8];
        std::string equation;
};