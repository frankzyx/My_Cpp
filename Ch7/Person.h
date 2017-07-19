#include <iostream>
#include <string>
using std::string;

struct Person {
	string name;
	string address;

	string getName() const { return name; }
	string getAddress() const { return address; }
};

// auxillary functions
std::istream &read(std::istream &is, Person &p) {
	is >> p.name >> p.address;
	return is;
}

std::ostream &print(std::ostream &os, const Person &p) {
	os << p.name << " " << p.address;
	return os;
}