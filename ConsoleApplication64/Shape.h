#pragma once
#include <string>

class Point {
public: int x = 0, y = 0;
};

class Shape {
protected: 
	Point* arc = 0; 
public: 
	std::string id = "";
	virtual ~Shape() {}
};

class Parallelogram : public Shape {
public:
	Parallelogram() {
		arc = new Point[4];
		id = "Parallelogram";
	}

	~Parallelogram() {
		delete[] arc;
	}
};

class Hexagon : public Shape{
public:
	Hexagon() {
		arc = new Point[6];
		id = "Hexagon";
	}

	~Hexagon() {
		delete[] arc;
	}
};

class FactoryShape {
public:
	static Shape* createShape(char Ch) {
		switch (Ch) {
		case 'P' :
			return new Parallelogram();
		case 'H' :
			return new Hexagon();
		default: 
			return nullptr;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");  
	Shape* s1 = nullptr;  
	bool cond = true;  
	while (cond) {
		cout << "Тип фигуры?\n";   
		char type;   
		cin >> type;   
		s1 = FactoryShape::createShape(type);   
		if (s1) { cout << s1->ID << endl; }
		else  cout << "Такой фигуры нет\n";       
		//Ввод координат вершин  
		cout << "Продолжим? (1/0)\n";   
		cin >> cond;   
		if (s1) delete s1;   
	} 