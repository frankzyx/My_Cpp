#include <iostream>
#include <string>

class Sales_data {
// make auxillary functions friend, to access non-public members of the class
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);

// ***I/O operators are normally declared as friends***
friend std::istream &operator>>(std::istream&, Sales_data&);
friend std::ostream &operator<<(std::ostream&, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
friend bool operator==(const Sales_data&, const Sales_data&);
friend bool operator!=(const Sales_data&, const Sales_data&);
	
public:
	// constructors
	Sales_data(const std::string &s, unsigned n, double p):
				bookNo(s), units_sold(n), revenue(p*n) {}
	// delegating constructors
	Sales_data(): Sales_data("", 0, 0) {}
	Sales_data(const std::string &s): Sales_data(s, 0, 0) {}
	Sales_data(std::istream &is): Sales_data() { is >> *this; }

	// member functions -- must be DECLARED inside class
	// implicit use of this (constant pointer) this->bookNo
	// A const following the parameter list indicates that "this" is a pointer to const
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);

	/* operator overloading
	 */
	Sales_data operator+=(const Sales_data&);
	
private:
	// data members
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

	double avg_price() const {
		return units_sold ? revenue / units_sold : 0;
	}
};




// ==============================================================
// definitions outside the class
Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
// ==============================================================
// Overloading operators
// 1. I/O -- must be references, and non-member 
// because the LHS is not of current class-type.
std::istream &operator>>(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	// deal with potential input error
	if (is)
		item.revenue = price * item.units_sold;
	else
		item = Sales_data();
	return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " "
   		<< item.revenue << " " << item.avg_price();
	return os;
}

// 2. Arithmetic and relational operators -- nonmember functions
// in order to allow conversions for LHS or RHS operand.
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	// Tip: implement the arithmetic operator by using compound assignment!!!
	sum += rhs;
	return sum;
}


Sales_data Sales_data::operator+=(const Sales_data &rhs) {
	// LHS operatand is bound to the implicit this pointer
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn() &&
		   lhs.units_sold == rhs.units_sold &&
		   lhs.revenue == rhs.revenue;
}

// != should be defined together with ==
bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
	return !(lhs == rhs);
}
