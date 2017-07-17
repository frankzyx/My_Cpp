// debugging
#include <iostream>
#include <vector>
using std::vector;
using Iter = vector<int>::iterator;

void print(Iter beg, Iter end) {
	if (beg != end) {
		// using 'g++ -D NDEBUG xxx.cpp' in command line to skip debugging here
		#ifndef NDEBUG
		std::cout << "size = " << end - beg << std::endl;
		#endif
		std::cout << *beg << std::endl;
		print(std::next(beg), end);
	}
}

int main() {
	vector<int> vec{1,3,5,7,9,11};
	print(vec.begin(), vec.end());
}