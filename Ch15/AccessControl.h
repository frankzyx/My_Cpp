#include <iostream>
#include <string>
#include <cstddef>

class Base {
public:
	void pub_mem() {};
protected:
	int prot_mem;
private:
	char priv_mem;
};

class Sneaky : public Base {
	friend void clobber(Sneaky&); 
	friend void clobber(Base&); 
	int j;
};

void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }
// void clobber(Base &b) { b.prot_mem = 0; }


struct Pub_Derv : public Base {
	// ok: derived classes can access protected members
	int f() { return prot_mem; }
	// error: no access to private members
	// char g() { return priv_mem; }
};


/* Purpose of derivation access specifier: 
	- control the access of the USERS of the derived class to the members
	  inherited from the base class.
 */
struct Priv_Derv : private Base {
	// private derivation does NOT affect access in the derived class
	int f1() const { return prot_mem; }
};
