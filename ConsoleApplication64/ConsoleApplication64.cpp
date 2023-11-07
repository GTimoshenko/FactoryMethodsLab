#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Point {
public:
	double x = 0;
	double y = 0;
};

class Shape : public Point {
public:
	Point* points = nullptr;
	std::string id = "";
	int s = 0;
	//функция для задания координат фигуры
	virtual Point setPoints() { return *this->points; }
	//функция для рассчета площади фигур
	virtual double calculateSquare() { return this->s; }
	//функция для поворота фигуры
	virtual void rotate(double alpha, double x0, double y0) {}
	//функция для перемещения фигуры
	virtual void move(double dx, double dy) {}
	//функция для нахождения центра тяжести
	virtual Point findGraviCenter() {}
	virtual ~Shape() {}
};

class Parallelogram : public Shape{
public:
	Parallelogram() {
		points = new Point[4];
		id = "Parallelogram";
	}

	Point setPoints() override {
		cout << "Enter coords below" << endl;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ")" << endl;
			cout << "x: "; cin >> this->points[i].x; cout << endl;
			cout << "y: "; cin >> this->points[i].y; cout << endl;
		}
		return this->points[4];
	}
	double calculateSquare() override {
		double x_A = this->points[0].x;
		double y_A = this->points[0].y;
		double x_B = this->points[1].x;
		double y_B = this->points[1].y;
		double x_C = this->points[2].x;
		double y_C = this->points[2].y;
		double x_D = this->points[3].x;
		double y_D = this->points[3].y;

		double area = std::abs((x_A * y_B + x_B * y_C + x_C * y_D + x_D * y_A) -
			(x_B * y_A + x_C * y_B + x_D * y_C + x_A * y_D)) / 2.0;

		return area;
	}
	void rotate(double alpha, double x0, double y0) override {
		for (int i = 0; i < 4; i++) {
			double x_rotated = (this->points[i].x - x0) * cos(alpha) - (this->points[i].y - y0) * sin(alpha) + x0;
			double y_rotated = (this->points[i].x - x0) * sin(alpha) + (this->points[i].y - y0) * cos(alpha) + y0;
			this->points[i].x = x_rotated;
			this->points[i].y = y_rotated;
		}
	}
	void move(double dx, double dy) {
		for (int i = 0; i < 4; i++) {
			this->points[i].x += dx;
			this->points[i].y += dy;
		}
	}
	Point findGraviCenter() override {
		Point p = Point();

		double totalX = 0, totalY = 0;
		for (int i = 0; i < 4; i++) {
			totalX += this->points[i].x;
			totalY += this->points[i].y;
		}
		p.x = totalX / 4;
		p.y = totalY / 4;
		
		return p;
	}

	~Parallelogram() {
		delete[] points;
	}
};

class Hexagon : public Shape {
public:
	Hexagon() {
		points = new Point[6];
		id = "Hexagon";
	}

	Point setPoints() override {
		cout << "Enter coords below" << endl;
		for (int i = 0; i < 6; i++) {
			cout << i+1 << ")" << endl;
			cout << "x: "; cin >> this->points[i].x; cout << endl;
			cout << "y: "; cin >> this->points[i].y; cout << endl;
		}
		return points[6];
	}
	double calculateSquare() override {
		double area = 0.0;
		for (int i = 0; i < 6; i++) {
			int j = (i + 1) % 6;
			area += (this->points[i].x * this->points[j].y) - (this->points[j].x * this->points[i].y);
		}
		area = 0.5 * std::abs(area);
		return area;
	}
	void rotate(double alpha, double x0, double y0) override {
		for (int i = 0; i < 6; i++) {
			double x_rotated = (this->points[i].x - x0) * cos(alpha) - (this->points[i].y - y0) * sin(alpha) + x0;
			double y_rotated = (this->points[i].x - x0) * sin(alpha) + (this->points[i].y - y0) * cos(alpha) + y0;
			this->points[i].x = x_rotated;
			this->points[i].y = y_rotated;
		}
	}
	void move(double dx, double dy) {
		for (int i = 0; i < 6; i++) {
			this->points[i].x += dx;
			this->points[i].y += dy;
		}
	}
	Point findGraviCenter() override {
		Point p = Point();

		double totalX = 0, totalY = 0;
		for (int i = 0; i < 6; i++) {
			totalX += this->points[i].x;
			totalY += this->points[i].y;
		}
		p.x = totalX / 6;
		p.y = totalY / 6;

		return p;
	}

	~Hexagon() {
		delete[] points;
	}
};

class FactoryShape {
public: 
	static Shape* createShape(string id) {
		if (id == "Parallelogram") return new Parallelogram();
		else if (id == "Hexagon") return new Hexagon();
		else return nullptr;
	}
};
class Operations {
public:
	//функция для проверки, включает ли одна фигура другую
	static bool isInclude(Shape* s1, Shape* s2){
		double x1least = s1->points[0].x, x2least = s2->points[0].x, x1greatest = s1->points[0].x, x2greatest = s2->points[0].x,
			y1least = s1->points[0].y, y2least = s2->points[0].y, y1greatest = s1->points[0].y, y2greatest = s2->points[0].y;
		int size1 = (s1->id == "Parallelogram") ? 4 : 6;
		int size2 = (s1->id == "Parallelogram") ? 4 : 6;

		for (int i = 1; i < size1; i++) {
			if (s1->points[i].x < x1least) x1least = s1->points[i].x;
			if (s1->points[i].x > x1greatest) x1greatest = s1->points[i].x;
			if (s1->points[i].x < y1least) y1least = s1->points[i].x;
			if (s1->points[i].x > y1greatest) y1greatest = s1->points[i].x;
		}

		for (int i = 1; i < size2; i++) {
			if (s1->points[i].x < x2least) x2least = s1->points[i].x;
			if (s1->points[i].x > x2greatest) x2greatest = s1->points[i].x;
			if (s1->points[i].x < y2least) y2least = s1->points[i].x;
			if (s1->points[i].x > y2greatest) y2greatest = s1->points[i].x;
		}

		if (x1least < x2least && x1greatest > x2greatest && y1least < y2least && y1greatest > y2greatest) return true;
		return false;
	}
	//функция для проверки, пересекает ли один объект другой
	static bool isIntersect(Shape* s1, Shape* s2) {
		double x1least = s1->points[0].x, x1greatest = s1->points[0].x, 
			   y1least = s1->points[0].y, y1greatest = s1->points[0].y;
		int size1 = (s1->id == "Parallelogram") ? 4 : 6;
		int size2 = (s1->id == "Parallelogram") ? 4 : 6;

		for (int i = 1; i < size1; i++) {
			if (s1->points[i].x < x1least) x1least = s1->points[i].x;
			if (s1->points[i].x > x1greatest) x1greatest = s1->points[i].x;
			if (s1->points[i].x < y1least) y1least = s1->points[i].x;
			if (s1->points[i].x > y1greatest) y1greatest = s1->points[i].x;
		}

		for (int i = 0; i < size2; i++) {
			if (s2->points[i].x > x1least && s2->points[i].x < x1greatest && s2->points[i].y > y1least && s2->points[i].y < y1greatest) return true;
		}
		return false;
	}
	//функция для сравнения двух объектов по площади
	static int compareSquare(Shape* s1, Shape* s2) {
		s1->calculateSquare();
		s2->calculateSquare();
		if (s1->s < s2->s) return 2;
		else if (s1->s == s2->s) return 0;
		return 1;
	}
};
int main() {
	setlocale(LC_ALL, "1251");
	string parall = "Parallelogram";
	string hex = "Hexagon";
	Shape* s1 = nullptr;
	Shape* s2 = nullptr;
	s1 = FactoryShape::createShape(parall);
	s1->setPoints();
	s2 = FactoryShape::createShape(hex);
	s2->setPoints();

	switch (Operations::compareSquare(s1, s2)) {
	case '1': cout << "площадь первой фигуры больше второй";
	case '2':cout << "площадь первой фигуры меньше второй";
	case '0': cout << "площади обеих фигур равны";
	default: return 1;
	}
	
	cout << endl;

	if (Operations::isInclude(s1, s2)) { cout << "первая фигура включает в себя вторую"; }
	else cout << "фигуры не включаются друг в друга";

	if (Operations::isInclude(s1, s2)) { cout << "фигуры пересекаются"; }
	else cout << "фигуры не пересекаются";


}