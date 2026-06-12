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

class FileNotFoundException : public PolynomialException {
public:
    FileNotFoundException(const std::string& filename)
        : PolynomialException("Ошибка: Не удалось открыть файл '" + std::string(filename) + "'!")
    {
    }
};

class InvalidPolynomialException : public PolynomialException {
public:
    InvalidPolynomialException(const std::string& details)
        : PolynomialException("Ошибка синтаксиса: " + std::string(details))
    {
    }
};

class EmptyFileException : public PolynomialException {
public:
    EmptyFileException(const std::string& filename)
        : PolynomialException("Ошибка: Файл '" + std::string(filename) + "' пуст!")
    {
    }
};