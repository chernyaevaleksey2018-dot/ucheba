#pragma once
#include <vector>
#include <string>
#include <cmath>

//результат решения уравнения
struct SolveResult 
{
    int rootCount;
    double x1, x2;
};

class QuadraticEquation 
{
public:
    double a, b, c;
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    //возвращает правильное решение
    SolveResult solve() const
    {
        SolveResult res = {0, 0, 0};
        double d = b * b - 4 * a * c;

        if (d < 0) 
        {
            res.rootCount = 0;
        } else if (d == 0) 
        {
            res.rootCount = 1;
            res.x1 = -b / (2 * a);
        } else
        {
            res.rootCount = 2;
            res.x1 = (-b + sqrt(d)) / (2 * a);
            res.x2 = (-b - sqrt(d)) / (2 * a);
        }
        return res;
    }

    //проверка совпадения присланного ответа с правильным
    bool checkAnswer(const SolveResult& answer) const 
    {
        SolveResult correct = solve();
        if (correct.rootCount != answer.rootCount) return false;
        const double EPS = 1e-6;
        if (correct.rootCount == 1)
            return fabs(correct.x1 - answer.x1) < EPS;
        if (correct.rootCount == 2)
            return (fabs(correct.x1 - answer.x1) < EPS && fabs(correct.x2 - answer.x2) < EPS)
                || (fabs(correct.x1 - answer.x2) < EPS && fabs(correct.x2 - answer.x1) < EPS);
        return true;
    }

    std::string toString() const 
    {
        return std::to_string(a) + "x^2 + " + std::to_string(b) + "x + " + std::to_string(c) + " = 0";
    }
};
