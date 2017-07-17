// inline and constexpr functions

#include <iostream>
#include <string>
#include <chrono>
using std::string;

inline const string &shorterString(const string &s1, const string &s2) {
	return s1.size() <= s2.size() ? s1 : s2;
}

constexpr int new_sz() {
	return 42;
}

int main() {
	string s1 = "water";
	string s2 = "computer";
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << shorterString(s1, s2) << std::endl;
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "Time elapsed = " << elapsed.count() << std::endl;

	int i = new_sz();
}