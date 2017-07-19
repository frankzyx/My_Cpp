#include <iostream>
#include <string>
using std::string;

std::istream &read(std::istream&, Person&);

class Person {
private:
	string name;
	string address;
public:
	Person() = default;
	Person(string sname, string saddress): name(sname), address(saddress) {}
	Person(std::istream &is) { read(is, *this); }

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