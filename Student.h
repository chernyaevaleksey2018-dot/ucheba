#pragma once
#include "QuadraticEquation.h"
#include <string>
#include <cstdlib>

class Student 
{
protected:
    std::string name;
public:
    Student(const std::string& name) : name(name) {}
    virtual ~Student() {}

    std::string getName() const {return name;}
    virtual SolveResult solve(const QuadraticEquation& eq) const = 0;
};

class GoodStudent : public Student //хороший студент всегда решает правильно
{
public:
    GoodStudent(const std::string& name) : Student(name) {}

    SolveResult solve(const QuadraticEquation& eq) const override 
    {
        return eq.solve(); //берём правильный ответ
    }
};

class AverageStudent : public Student //средний студент решает правильно с вероятностью 70%
{
    double correctProbability; // от 0.0 до 1.0
public:
    AverageStudent(const std::string& name, double prob = 0.7)
        : Student(name), correctProbability(prob) {}

    SolveResult solve(const QuadraticEquation& eq) const override 
    {
        double roll = (double)rand() / RAND_MAX;
        if (roll < correctProbability) 
        {
            return eq.solve(); // повезло повезло, правильно
        } else 
        {
            //студент ошибается: возвращает случайный неверный ответ
            SolveResult wrong;
            wrong.rootCount = 2;
            wrong.x1 = (double)(rand() % 10) - 5;
            wrong.x2 = (double)(rand() % 10) - 5;
            return wrong;
        }
    }
};

class BadStudent : public Student //плохой студент пишет "один корень x = 0"
{
public:
    BadStudent(const std::string& name) : Student(name) {}

    SolveResult solve(const QuadraticEquation& eq) const override 
    {
        SolveResult lazy;
        lazy.rootCount = 1;
        lazy.x1 = 0;
        lazy.x2 = 0;
        return lazy;
    }
};  
