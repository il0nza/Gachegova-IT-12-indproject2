#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "Polynomial_Header.h"
#include "Exceptions.h"

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

	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->getValue() == 0) {
			Node* toDelete = current;
			current = current->getNext();

			if (toDelete == head) {
				head = current;
				if (head == nullptr) {
					tail = nullptr;
				}
			}
			else {
				previous->setNext(current);
				if (toDelete == tail) {
					tail = previous;
				}
			}
			delete toDelete;
		}
		else {
			previous = current;
			current = current->getNext();
		}
	}
}

void Polynomial::simplify() {
	if (isEmpty()) {
		return;
	}

	Node* current = head;

	while (current != nullptr && current->getNext() != nullptr) {
		Node* nextNode = current->getNext();

		if (current->getDegree() == nextNode->getDegree()) {
			current->setValue(current->getValue() + nextNode->getValue());
			current->setNext(nextNode->getNext());
			if (nextNode == tail) {
				tail = current;
			}
			delete nextNode;
		}
		else {
			current = current->getNext();
		}
	}
	removeZeroTerms();
}

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

std::string Polynomial::toString() const {
	if (isEmpty()) {
		return "0";
	}

	std::string result = "";
	Node* current = head;
	bool isFirst = true;

	while (current != nullptr) {
		int coeff = current->getValue();
		int degree = current->getDegree();

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
		current = current->getNext();
	}
	return result;
}