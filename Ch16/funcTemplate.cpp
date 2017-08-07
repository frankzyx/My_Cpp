#include <iostream>
#include <string>

template <typename T>
int compare(const T &v1, const T &v2) {
	if (v1 < v2) return -1;
	if (v1 > v2) return 1;
	return 0;
}

int main() {
	std::string s1 = "hello", s2 = "coco";
	std::cout << compare(s1, s2) << std::endl;
}
