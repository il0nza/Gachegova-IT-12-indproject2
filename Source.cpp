#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Polynomial_Header.h"
#include "Project_Header.h"
#include "Input.h"

void executeProgramLogic(const std::string& filename) {
    Polynomial poly;

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw FileNotFoundException(filename);
    }

    std::string line;
    if (!std::getline(inFile, line)) {
        inFile.close();
        throw EmptyFileException(filename);
    }
    inFile.close();
    std::cout << "\nИсходный многочлен из файла: " << line << std::endl;

    poly.parseFromString(line);
    poly.simplify();
    std::string resultStr = poly.toString();
    std::cout << "\nРезультат после приведения подобных: " << resultStr << std::endl;

    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        throw FileNotFoundException(filename);
    }
    outFile << line << "\n" << resultStr;
    outFile.close();
}

void clearConsole() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    std::cin.get();
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');    
    std::cout << "\033[2J\033[H" << std::flush;
}

std::string chooseFile() {
    std::vector<std::string> files{ "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "file6.txt", "file7.txt"};
    std::cout << "\nВыберите файл для обработки: \n";
    std::cout << "1. file1.txt [Базовый тест: сортировка]\n";
    std::cout << "2. file2.txt [Базовый тест: приведение подобных]\n";
    std::cout << "3. file3.txt [Тест на пробелы]\n";
    std::cout << "4. file4.txt [Тест на большие степени]\n";
    std::cout << "5. file5.txt [Ошибка синтаксиса: пропущенная степень]\n";
    std::cout << "6. file6.txt [Тест на уничтожение степеней]\n";
    std::cout << "7. file7.txt [Ошибка: пустой файл]\n";
    while (true) {
        try {
            std::cout << ">> ";
            int c = Input::readInt(1, 7);
            return files[c - 1];
        }
        catch (const char* inputError) {
            std::cout << "\033[31m" << inputError << "\033[0m" << std::endl;
            std::cout << "Пожалуйста, введите корректный номер файла (от 1 до 7).\n" << std::endl;
        }
    }
}

void showInstruction() {
    std::cout << "\n  ~   ИНСТРУКЦИЯ   ~\n" << std::endl;
    std::cout << "1. Выберите пункт 1 в главном меню." << std::endl;
    std::cout << "\n2. Программа предложит список доступных файлов (от file1 до file7)." << std::endl;
    std::cout << "   Введите номер нужного файла и нажмите Enter." << std::endl;
    std::cout << "\n3. Программа автоматически выполнит следующие шаги:" << std::endl;
    std::cout << "   - Считает исходный многочлен из первой строки файла." << std::endl;
    std::cout << "   - Приведет подобные слагаемые и отсортирует их по убыванию степеней." << std::endl;
    std::cout << "   - Выведет результат «Было / Стало» на экран для проверки." << std::endl;
    std::cout << "\n4. Сохранение: результат автоматически перезапишет выбранный файл." << std::endl;
    std::cout << "   Первая строка файла останется исходной, а во вторую запишется результирующий многочлен." << std::endl;
    std::cout << "\n5. Обработка ошибок: если файл пуст или содержит некорректные символы," << std::endl;
    std::cout << "   программа выдаст предупреждение и безопасно вернет вас в меню." << std::endl;
}