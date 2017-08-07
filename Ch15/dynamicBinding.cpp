#include "Quote.h"
#include <iostream>
#include <string>

/* Conversion from derived to base applies 
	ONLY to pointers or references types.
 */

void dynamicBind() {
	Quote base("001", 10);
	Bulk_quote derived("001", 10, 5, .2);



	/* pointers/references --
		We can use an object of (or reference to) a derived type,
		when a reference to base type is required, i.e. use the derived class
		as if it were base class.
	 */

	Disc_quote *p = &derived;
	Quote &r_base = base;
	Disc_quote &r = derived;	

	// dynamic binding through references
	print_total(std::cout, r_base, 20);
	print_total(std::cout, r, 20);
}

void abstractTest() {
	// cannot construct an object of abstract base class!!!
	// Disc_quote abstract("001", 10, 5, .2);


}

int main() {
	dynamicBind();
	// abstractTest();
}
