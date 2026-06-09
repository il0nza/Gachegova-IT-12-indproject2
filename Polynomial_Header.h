#pragma once

class Node {
private:
	int coeff;
	int degree;
	Node* next;

public:
	Node(int c, int d) : coeff(c), degree(d), next(nullptr) {}

	int getValue() const { return coeff; }
	int getDegree() const { return degree; }
	Node* getNext() const { return next; }
	void setValue(int c) { coeff = c; }
	void setDegree(int deg) { degree = deg; }
	void setNext(Node* nextNode) { next = nextNode; }
};


class Polynomial {
private:
	Node* head;
	Node* tail;

	void removeZeroTerms();

public:
	Polynomial() : head(nullptr), tail(nullptr) {}

	Polynomial(const Polynomial& other);

	~Polynomial() {
		clear();
	}

	Polynomial& operator=(const Polynomial& other);

	bool isEmpty() const {
		return head == nullptr;
	}

	void clear();
	void pushBack(int coeff, int degree);
	void removeByDegree(int degree);
	void insertSorted(int coeff, int degree);
	void simplify();
	void parseFromString(const std::string& str);
	std::string toString() const;
};