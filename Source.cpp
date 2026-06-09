#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"
#include "Polynomial_Header.h"
#include "Project_Header.h"

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

    std::ofstream outFile(filename, std::ios::app);
    if (!outFile.is_open()) {
        throw FileNotFoundException(filename);
    }

    outFile << "\n" << resultStr;
    outFile.close();
}

void clearConsole() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cin.get();
    std::cout << "\033[2J\033[H" << std::flush;
}