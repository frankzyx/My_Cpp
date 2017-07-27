#include "Account.h"
#include <iostream>
#include <string>

int main() {
	Account ac1;
	Account *ac2 = &ac1;
	double r1 = Account::rate();
	double r2 = ac2->rate();
	std::cout << r2 << std::endl;
}