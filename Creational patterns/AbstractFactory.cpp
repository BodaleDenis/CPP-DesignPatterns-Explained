/**
 * @file AbstractFactory.cpp
 * @author Denis
 * @brief 
 * AbstractFactory design pattern, revolve around the creating an Interface (Abstract class in C++) in order to create a family of related/dependent
   objects without specifing it's concrete class (using runtime polymorphism in C++).
   This is mostly used when we need a runtime value to construct a depency, multiple classes form some sort of specific "family" of objects and are designed
   to be used together
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Operation
{
    public:
        virtual void calculate(int firstNumber, int secondNumber) const = 0;
};

class Addition : public Operation
{
    public:
        void calculate(int firstNumber, int secondNumber) const override
        {
            std::cout << "Addition of the numbers is " << firstNumber + secondNumber << "\n";
        }
};

class Substraction : public Operation 
{
    public:
        void calculate(int firstNumber, int secondNumber) const override
        {
            std::cout << "Substraction of the numbers is " << firstNumber - secondNumber << "\n";
        }    
};

class Exponentiation : public Operation 
{
    public:
        void calculate(int base, int exponent) const override
        {
            int product=1;
            for (auto i=0; i<exponent; i++)
            {
                product = product * base;  
            }
            std::cout << "Exponentiation of the numbers is " << product << "\n";
        }
};

class Factory 
{
    public:
        virtual Operation* createAddition() = 0;
        virtual Operation* createSubstraction() = 0;
        virtual Operation* createExponentiation() = 0;

};

class BasicCalculator : public Factory
{
    public:
        Operation* createAddition() override
        {
            return new Addition();
        }

        Operation* createSubstraction() override
        {
            return new Substraction();
        }

        Operation* createExponentiation() override
        {
            return new Exponentiation();
        }
};

int main()
{
    int VALUE1 = 2, VALUE2 = 5;
    auto factory = std::make_shared<BasicCalculator>();
    auto operations = std::vector<Operation*>();
    
    operations.push_back(factory->createAddition());
    operations.push_back(factory->createSubstraction());
    operations.push_back(factory->createExponentiation());

    for(auto& operation : operations)
    {
        operation->calculate(VALUE1, VALUE2);
    }
    return 0;
}