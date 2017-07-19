#include <iostream>
#include <string>

struct Sales_data {
	// members -- must be DECLARED inside class

	// implicit use of this (constant pointer) this->bookNo
	// A const following the parameter list indicates that "this" is a pointer to const
	std::string isbn() const { return bookNo; }

	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	// data members
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};


// ==============================================================
// definitions outside the class
double Sales_data::avg_price() const {
	// once scope of class is seen, the rest of coed is interpreted as being inside the class
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}


// ==============================================================
// auxillary functions
std::istream &read(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " "
	   << item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
// ==============================================================