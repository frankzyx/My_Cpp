#include "Sales_data.h"
#include <string>
using std::string;


int main() {
	Sales_data total;
	if (read(std::cin, total)) {		// read 1st transaction
		Sales_data trans;
		while (read(std::cin, trans)) {
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
		print(std::cout, total) << std::endl;
	} else {
		std::cerr << "No data?!" << std::endl;
	}
}