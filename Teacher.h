#pragma once
#include "QuadraticEquation.h"
#include <queue>
#include <map>
#include <iostream>
#include <iomanip>

struct Letter 
{
    std::string studentName;
    QuadraticEquation equation;
    SolveResult answer;
};

class Teacher 
{
    std::queue<Letter> inbox;
    std::map<std::string, int> scoreTable;
public:

    void receiveAnswer(const std::string& studentName, const QuadraticEquation& eq, const SolveResult& answer) 
    {
        inbox.push({studentName, eq, answer});
    }

    void checkAll() 
    {
        if (inbox.empty()) 
        {
            std::cout << "нет писем для проверки\n";
            return;
        }
        int count = 0;
        while (!inbox.empty()) 
        {
            Letter letter = inbox.front();
            inbox.pop();
            if (letter.equation.checkAnswer(letter.answer))
                scoreTable[letter.studentName]++;
            count++;
        }
        std::cout << "проверено писем: " << count << "\n";
    }

    void printTable() const 
{
        if (scoreTable.empty()) 
        {
            std::cout << "таблица пустая (сначала проведите проверку)\n";
            return;
        }
        std::cout << "\n  --- таблица успеваемости ---\n";
        std::cout << "  " << std::left << std::setw(20) << "студент" << "правильных ответов\n";
        std::cout << "  " << std::string(38, '-') << "\n";
        for (const auto& entry : scoreTable) 
        {
            std::cout << "  " << std::left << std::setw(20) << entry.first << entry.second << "\n";
        }
        std::cout << "\n";
    }
};
