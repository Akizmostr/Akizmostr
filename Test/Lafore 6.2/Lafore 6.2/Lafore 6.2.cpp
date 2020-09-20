#include <iostream>

const double TOLL = 0.5;

class tollBooth {
public:
	tollBooth();
	~tollBooth();
	void paingCar();
	void nopayCar();
	const void display();
private:
	unsigned int cars_passed;
	double earning;
};

tollBooth::tollBooth(): cars_passed(0), earning(0) {
}

tollBooth::~tollBooth() {
}

void tollBooth::paingCar() {
	cars_passed++;
	earning += TOLL;
}

void tollBooth::nopayCar() {
	cars_passed++;
}

const void tollBooth::display() {
	std::cout << "Cars passed: " << cars_passed << std::endl;
	std::cout << "Total earnings: " << earning << std::endl;
}


int get_variant(int&, int);

int main()
{
	std::cout << "Enter numbers for navigation: " << std::endl;
	std::cout << "1)The driver passes with paying \n2)The driver passes without paying \n3)Display \n4)Exit" << std::endl;

	int variant;

	tollBooth drivers = tollBooth();

	do {
		variant = get_variant(variant, 4);
		switch (variant) {
		case 1:
			drivers.paingCar();
			break;
		case 2:
			drivers.nopayCar();
			break;
		case 3:
			drivers.display();
		default:
			break;
		}
	} while (variant!=4);
}

int get_variant(int& variant, int n) {
	std::cin >> variant;
	while (variant < 1 || variant > n) {
		std::cout << "Incorrect input. Try again." << std::endl;
		std::cin >> variant;
	}
	return variant;
}