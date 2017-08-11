#include "Sales_data.h"
#include <string>
using std::string;

void test1() {
	Sales_data total;
	if (std::cin >> total) {		// read 1st transaction
		Sales_data trans;
		while (std::cin >> trans) {
			if (total.isbn() == trans.isbn())
				total += trans;
			else {
				std::cout << total << std::endl;	// using overloaded operator<<
				total = trans;
			}
		}
		std::cout << total << std::endl;	// last transaction
	} else {
		std::cerr << "No data?!" << std::endl;
	}
}

int main() {
	test1();
	// test2();
}