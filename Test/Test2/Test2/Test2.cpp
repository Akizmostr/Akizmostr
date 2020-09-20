#include <iostream>
#include <string>

class Numbers {
	double m_a, m_b, m_c;

public:
	void setValues(double a, double b, double c) {
		m_a = a;
		m_b = b;
		m_c = c;
	}

	void print() {
		std::cout << "<" << m_a << "," << m_b << "," << m_c << ">" << std::endl;
	}

	bool isEqual(Numbers& point) {
		if (m_a == point.m_a && m_b == point.m_b && m_c == point.m_c)
			return true;
		else
			return false;
	}
};


int main() {
	Numbers point1;
	point1.setValues(3.0, 4.0, 5.0);

	Numbers point2;
	point2.setValues(3.0, 4.0, 5.0);

	if (point1.isEqual(point2))
		std::cout << "point1 and point2 are equal\n";
	else
		std::cout << "point1 and point2 are not equal\n";

	Numbers point3;
	point3.setValues(7.0, 8.0, 9.0);

	if (point1.isEqual(point3))
		std::cout << "point1 and point3 are equal\n";
	else
		std::cout << "point1 and point3 are not equal\n";

	return 0;
}