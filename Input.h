#pragma once
#include <iostream>
#include <limits>
#include <string>

class Input {
public:
    static int readInt(int min, int max) {
        int value;

        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            throw "Введённые данные не являются числом!";
        }

        if (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            throw "Ошибка: введите целое число (без точек, запятых и букв)!";
        }

        if (value < min || value > max) {
            throw "Ошибка: число вышло за допустимый диапазон!";
        }

        return value;
    }
};
