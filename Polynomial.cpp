#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "Polynomial_Header.h"
#include "Exceptions.h"

// конструктор копирования
Polynomial::Polynomial(const Polynomial& other) : head(nullptr), tail(nullptr) {
	Node* curr = other.head;
	while (curr != nullptr) {
		this->pushBack(curr->getValue(), curr->getDegree());
		curr = curr->getNext();
	}
}

void Polynomial::clear() {
	Node* curr = head;
	while (curr != nullptr) {
		Node* nextNode = curr->getNext();
		delete curr;
		curr = nextNode;
	}
	head = nullptr;
	tail = nullptr;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (this != &other) {
		clear();

		Node* curr = other.head;
		while (curr != nullptr) {
			this->pushBack(curr->getValue(), curr->getDegree());
			curr = curr->getNext();
		}
	}
	return *this;
}

void Polynomial::pushBack(int coeff, int degree) {
	if (coeff == 0) {
		return;
	}

	Node* newNode = new Node(coeff, degree);
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->setNext(newNode);
		tail = newNode;
	}
}

// удаление слагаемого по заданной степени 
void Polynomial::removeByDegree(int degree) {
	if (isEmpty()) {
		return;
	}
	Node* curr = head;
	Node* prev = nullptr;

	while (curr != nullptr && curr->getDegree() != degree) {
		prev = curr;
		curr = curr->getNext();
	}

	if (curr == nullptr) {
		return;
	}

	if (curr == head) {
		head = head->getNext();
		if (head == nullptr) {
			tail = nullptr;
		}
	}
	else {
		prev->setNext(curr->getNext());
		if (curr == tail) {
			tail = prev;
		}
	}
	delete curr;
}

// алгоритм упорядоченной вставки узла
void Polynomial::insertSorted(int coeff, int degree) {
	if (coeff == 0) {
		return;
	}

	Node* newNode = new Node(coeff, degree);
	
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
		return;
	}
	
	if (degree > head->getDegree()) {
		newNode->setNext(head);
		head = newNode;
		return;
	}

	if (degree <= tail->getDegree()) {
		tail->setNext(newNode);
		tail = newNode;
		return;
	}

	Node* prev = head;
	Node* curr = head->getNext();
	while (curr != nullptr && curr->getDegree() > degree) {
		prev = curr;
		curr = curr->getNext();
	}
	newNode->setNext(curr);
	prev->setNext(newNode);
}

void Polynomial::removeZeroTerms() {
	if (isEmpty()) {
		return;
	}

	Node* curr = head;
	Node* prev = nullptr;
	// последовательный обход для поиска и удаления узлов с нулевым значением
	while (curr != nullptr) {
		if (curr->getValue() == 0) {
			Node* toDelete = curr;
			curr = curr->getNext();

			if (toDelete == head) {
				head = curr;
				if (head == nullptr) {
					tail = nullptr;
				}
			}
			else {
				prev->setNext(curr);
				if (toDelete == tail) {
					tail = prev;
				}
			}
			delete toDelete;
		}
		else {
			prev = curr;
			curr = curr->getNext();
		}
	}
}

// приведения подобных слагаемых 
void Polynomial::simplify() {
	if (isEmpty()) {
		return;
	}

	Node* curr = head;
	// т.к. список отсортирован, равные степени идут подряд
	while (curr != nullptr && curr->getNext() != nullptr) {
		Node* nextNode = curr->getNext();
		// если степени соседних узлов совпадают - «схлопываем» их
		if (curr->getDegree() == nextNode->getDegree()) {
			curr->setValue(curr->getValue() + nextNode->getValue());
			curr->setNext(nextNode->getNext());
			if (nextNode == tail) {
				tail = curr;
			}
			delete nextNode;
		}
		else {
			curr = curr->getNext();
		}
	}
	removeZeroTerms();
}

// посимвольный разбор строки
void Polynomial::parseFromString(const std::string& str) {
	clear();

	size_t i = 0;
	size_t n = str.length();

	while (i < n) {
		while (i < n && (str[i] == ' ' || str[i] == '\t')) {
			i++;
		}
		if (i >= n) {
			break;
		}

		int sign = 1;
		if (str[i] == '+') {
			sign = 1;
			i++;
		}
		else if (str[i] == '-') {
			sign = -1;
			i++;
		}

		while (i < n && (str[i] == ' ' || str[i] == '\t')) {
			i++;
		}

		int coeff = 0;
		bool hasCoeff = false;
		while (i < n && std::isdigit(str[i])) {
			coeff = coeff * 10 + (str[i] - '0');
			hasCoeff = true;
			i++;
		}

		if (!hasCoeff) {
			coeff = 1;
		}
		coeff *= sign;

		int degree = 0;
		if (i < n && (str[i] == 'y' || str[i] == 'Y')) {
			i++;
			if (i < n && str[i] == '^') {
				i++;
				bool hasDegree = false;
				while (i < n && std::isdigit(str[i])) {
					degree = degree * 10 + (str[i] - '0');
					hasDegree = true;
					i++;
				}

				if (!hasDegree) {
					throw InvalidPolynomialException("Ошибка: пропущена степень после символа '^'");
				}
			}
			else {
				degree = 1;
			}
		}
		else {
			if (!hasCoeff) {
				throw InvalidPolynomialException("Ошибка: обнаружен недопустимый символ в строке многочлена");
			}
			degree = 0;
		}
		insertSorted(coeff, degree);
	}

	if (isEmpty()) {
		throw "Ошибка: строка пуста или имеет неверный формат";
	}
}

// формирование результирующей строки 
std::string Polynomial::toString() const {
	if (isEmpty()) {
		return "0";
	}

	std::string result = "";
	Node* curr = head;
	bool isFirst = true;

	while (curr != nullptr) {
		int coeff = curr->getValue();
		int degree = curr->getDegree();

		if (coeff > 0) {
			if (!isFirst) {
				result += " + ";
			}
		}
		else {
			if (isFirst) {
				result += "-";
			}
			else {
				result += " - ";
			}
			coeff = -coeff;
		}

		if (coeff != 1 || degree == 0) {
			result += std::to_string(coeff);
		}

		if (degree > 0) {
			result += "y";
			if (degree > 1) {
				result += "^" + std::to_string(degree);
			}
		}

		isFirst = false;
		curr = curr->getNext();
	}
	return result;
}