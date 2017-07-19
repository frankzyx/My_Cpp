// pointers to functions

#include <iostream>
#include <string>
using std::string;

bool lengthCompare(const string &s1, const string &s2) {
	return s1.size() <= s2.size();
}

void pointerToFunction() {
	bool (*pf)(const string &, const string &);		// declares pf as pointer to a function
	pf = lengthCompare;		// it's ok to assign function name to pf directly
	std::cout << pf("Hello", "Watermelon") << std::endl;
}


typedef bool Func(const string&, const string&);
// function pointer as parameters
void useBigger(const string &s1, const string &s2, Func) {
	std::cout << Func(s1, s2) ? s2 : s1 << std::endl;
}

int main() {
	pointerToFunction();
	string s1 = "hello", s2 = "good";
	useBigger(s1, s2, lengthCompare);
}
