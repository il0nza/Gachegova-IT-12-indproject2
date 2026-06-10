#include <iostream>
#include <windows.h>
#include <string>
#include "Polynomial_Header.h"
#include "Exceptions.h"
#include "Project_Header.h"
#include "Input.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
    while (true) {
        std::cout << std::endl;
        std::cout << "       МЕНЮ УПРАВЛЕНИЯ ПРОГРАММОЙ        " << std::endl;
        std::cout << std::endl;
        std::cout << "1. Выполнить обработку многочлена из файла" << std::endl;
        std::cout << "2. Показать инструкцию" << std::endl;
        std::cout << "3. Выйти из программы" << std::endl;
        std::cout << "\n" << std::endl;

        int choice = 0;
        while (true) {
            try {
                std::cout << "Выберите пункт меню (1-3): ";
                choice = Input::readInt(1, 3);
                break;
            }
            catch (const char* inputError) {
                std::cout << "\033[31m" << inputError << "\033[0m" << std::endl;
                std::cout << "Пожалуйста,введите число от 1 до 3 ещё раз.\n" << std::endl;
            }
        }

        if (choice == 3) {
            std::cout << "\nВыполнение программы успешно завершено..." << std::endl;
            std::cout << R"(
                    /\       /\
                   /  ` """ `  \,    <MEOW>
                  /             ;
                 ;;     · w ·   ;;
                 :;  )         , )
                  `,           ,'
                    `,(/"'""\ U
                )" << std::endl;
            break;
        }

        if (choice == 2) {
            std::cout << "\033[2J\033[H" << std::flush;
            showInstruction();
        }
        else {
            try {
                std::string filename = chooseFile();
                std::cout << "\n ~  Запуск обработки файла  ~ " << std::endl;
                executeProgramLogic(filename);
                std::cout << "\n\033[32m[Успех]\033[0m Результат дозаписан в конец файла '" << filename << "'." << std::endl;
            }
            catch (const PolynomialException& e) {
                std::cout << "\n\033[31m[Перехвачено исключение]:\033[0m " << e.what() << std::endl;
                std::cout << "\nДействие отменено. Исправьте данные и попробуйте снова." << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "\n\033[31m[Системная ошибка]:\033[0m " << e.what() << std::endl;
            }
        }
        clearConsole();
    }

}
