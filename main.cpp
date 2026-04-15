#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "QuadraticEquation.h"
#include "Student.h"
#include "Teacher.h"

std::vector<QuadraticEquation> loadEquations(const std::string& filename) //уравнения из eq.txt
{
    std::vector<QuadraticEquation> equations;
    std::ifstream file(filename);
    double a, b, c;
    while (file >> a >> b >> c) 
    {
        equations.emplace_back(a, b, c);
    }
    return equations;
}

void printEquations(const std::vector<QuadraticEquation>& eqs) //печать уравнений
{
    std::cout << "\n  Уравнения из файла:\n";
    for (int i = 0; i < (int)eqs.size(); i++)
    {
        std::cout << "  [" << i + 1 << "] " << eqs[i].toString() << "\n";
    }
    std::cout << "\n";
}

int main() 
{
    srand((unsigned)time(nullptr));

    std::vector<std::unique_ptr<Student>> students;
    students.push_back(std::make_unique<GoodStudent>("Аня"));
    students.push_back(std::make_unique<GoodStudent>("Ксюша"));
    students.push_back(std::make_unique<AverageStudent>("Лёша", 0.7));
    students.push_back(std::make_unique<AverageStudent>("Артём", 0.5));
    students.push_back(std::make_unique<BadStudent>("Гриша"));

    Teacher teacher;

    std::vector<QuadraticEquation> equations = loadEquations("equations.txt"); //загрузка уравнений
    std::cout << "--- симуляция зачёта по математике ---\n";

    int choice = 0; //интерактивное меню
    while (true) 
    {
        std::cout << "\nменю:\n";
        std::cout << "  1. показать уравнения из файла\n";
        std::cout << "  2. студенты решают все задачи и отправляют ответы\n";
        std::cout << "  3. преподаватель проверяет все письма\n";
        std::cout << "  4. опубликовать таблицу успеваемости\n";
        std::cout << "  0. выйти\n";
        std::cout << "ваш выбор: ";
        std::cin >> choice;

        if (choice == 0) 
        {
            std::cout << "до свидания!\n";
            break;
        }

        switch (choice) 
        {
        case 1:
            printEquations(equations);
            break;

        case 2:
            // Каждый студент решает каждое уравнение и отправляет ответ
            for (const auto& student : students) 
            {
                for (const auto& eq : equations) 
                {
                    SolveResult answer = student->solve(eq);
                    teacher.receiveAnswer(student->getName(), eq, answer);
                }
                std::cout << "  " << student->getName() << " отправил(а) ответы.\n";
            }
            std::cout << "  все ответы отправлены в очередь.\n";
            break;

        case 3:
            std::cout << "  преподаватель проверяет письма...\n";
            teacher.checkAll();
            break;

        case 4:
            teacher.printTable();
            break;

        default:
            std::cout << "  неверный выбор, попробуйте снова.\n";
        }
    }
}
