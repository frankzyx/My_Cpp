#include "Screen.h"
#include <string>
#include <iostream>

int main() {
	Screen myScreen(3, 4, 'X');
	// myScreen.display(std::cout);
	myScreen.move(1, 1).set('#').display(std::cout);
}