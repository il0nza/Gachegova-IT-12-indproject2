#pragma once
#include <exception>
#include <string>

class PolynomialException : public std::exception {
private:
    std::string m_error{};

public:
    PolynomialException(const std::string& error)
        : m_error{ error }
    {
    }
    const char* what() const noexcept override { return m_error.c_str(); }
};

// 1. Ошибка: Файл не найден
class FileNotFoundException : public PolynomialException {
public:
    FileNotFoundException(const std::string& filename)
        : PolynomialException("Ошибка: Не удалось открыть файл '" + std::string(filename) + "'!")
    {
    }
};

// 2. Ошибка: Неверный формат многочлена
class InvalidPolynomialException : public PolynomialException {
public:
    InvalidPolynomialException(const std::string& details)
        : PolynomialException("Ошибка синтаксиса: " + std::string(details))
    {
    }
};

// 3. Ошибка: Файл пуст
class EmptyFileException : public PolynomialException {
public:
    EmptyFileException(const std::string& filename)
        : PolynomialException("Ошибка: Файл '" + std::string(filename) + "' пуст!")
    {
    }
};