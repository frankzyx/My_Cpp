#include "Sales_data.h"
#include <string>
using std::string;


int main() {
	Sales_data total(std::cin);
	if (!total.isbn().empty()) {		// read 1st transaction
		std::istream &is = std::cin;
		while (is) {
			Sales_data trans(is);
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
	} else {
		std::cerr << "No data?!" << std::endl;
	}
}