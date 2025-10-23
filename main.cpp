#include "figures.h"
#include <iostream>
#include <string>

void help() {
    std::cout << "    Команды\n";
    std::cout << "Ввести 5-угольник: add 5\n";
    std::cout << "Ввести 6-угольник: add 6\n";
    std::cout << "Ввести 8-угольник: add 8\n";
    std::cout << "Удалить фигуру по индексу: del n\n";
    std::cout << "Показать геометрические центры всех фигур: centers\n";
    std::cout << "Показать координаты вершин всех фигур: verts\n";
    std::cout << "Показать площади всех фигур: areas\n";
    std::cout << "Показать все сведения по каждой фигуре: list\n";
    std::cout << "Показать общую площадь: total\n";
    std::cout << "Показать эту справку снова: help\n";
    std::cout << "Выход из программы: exit\n";
}

int main() {
    FiguresList arr;
    help();
    while (true) {
        std::cout << "> ";
        std::string v;
        if (!std::getline(std::cin, v)) {
            break;
        }
        if (v.empty()) {
            continue;
        } else if (v == "exit") {
            break;
        } else if (v == "list") {
            arr.printAll(std::cout);
        } else if (v == "centers") {
            arr.printCenters(std::cout);
        } else if (v == "verts") {
            arr.printVertices(std::cout);
        } else if (v == "areas") {
            arr.printAreas(std::cout);
        } else if (v == "total") {
            std::cout << "Общая площадь = " << arr.totalArea() << "\n";
        } else if (v.rfind("add ", 0) == 0) {
            int n = 0;
            try {
                n = std::stoi(v.substr(4));
            } catch (const std::exception& ) {
                std::cout << "Неверная команда add\n";
                continue;
            }
            if (n != 5 && n != 6 && n != 8) {
                std::cout << "Допустимые значения сторон: 5, 6, 8\n";
                continue;
            }
            std::cout << "Ввод: центр_x центр_y радиус (через пробел): ";
            double cx;
            double cy;
            double r;
            if (!(std::cin >> cx >> cy >> r)) {
                std::cout << "Неверный ввод\n";
                std::string restOfLine;
                std::getline(std::cin, restOfLine);
                continue;
            } else {
                std::string restOfLine;
                std::getline(std::cin, restOfLine);
            }
            if (n == 5) {
                Figure* f = new Pentagon(cx, cy, r);
                arr.pushBack(f);
            } else if (n == 6) {
                Figure* f = new Hexagon(cx, cy, r);
                arr.pushBack(f);
            } else {
                Figure* f = new Octagon(cx, cy, r);
                arr.pushBack(f);
            }
            std::cout << "Добавлено n = " << n << "\n";
        } else if (v.rfind("del ", 0) == 0) {
            try {
                std::size_t index = static_cast<std::size_t>(std::stoul(v.substr(4)));
                arr.removeAt(index);
                std::cout << "Удалено " << index << "\n";
            } catch (const std::exception& exception) {
                std::cout << "Ошибка: " << exception.what() << "\n";
            }
        } else {
            std::cout << "Неизвестная команда\n";
        }
    }
    std::cout << "Выход.\n";
    return 0;
}
