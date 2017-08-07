#include <iostream>
#include <string>
#include <cstddef>

// base class
class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):
					bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }

	// virtual functions: derived classes will override
	virtual double net_price(std::size_t n) const {
		return n * price;
	}

	virtual ~Quote() = default; 	// virtual destructor for the base class

private:
	std::string bookNo;
protected:	// can be accessed by derived classes
	double price = 0.0;  // normal, undiscounted price
};


/* Pure virtual functions and abstract base classes
   -- All pricing classes inherit from this class
 */
class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double p, std::size_t qty, double disc):
					Quote(book, p), quantity(qty), discount(disc) {}

	double net_price(std::size_t) const = 0;	// this is a pure virtual function
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

// derived from Disc_quote
class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;

	// respect the Interface in the base class by using its constructor
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc):
					Disc_quote(book, price, qty, disc) {}
	// overriding, implicitly virtual
	double net_price(std::size_t cnt) const override {
		return cnt >= quantity ? cnt * (1 - discount) * price : cnt * price;
	}
};




// Non-member functions
double print_total(std::ostream &os, const Quote &item, std::size_t n) {
	double ret = item.net_price(n);		// dynamic binding
	os << "ISBN: " << item.isbn()
	   << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}