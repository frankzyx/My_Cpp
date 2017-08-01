#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
using std::vector;
using std::string;
using std::cout;
using std::endl;


void elimDups(vector<string> &words) {
	std::sort(words.begin(), words.end());
	for (auto s : words)
		cout << s << " ";
	cout << endl;

	auto end_unique = std::unique(words.begin(), words.end());
	for (auto s : words)
		cout << s << " ";
	cout << endl;

	words.erase(end_unique, words.end());
	for (auto s : words)
		cout << s << " ";
	cout << endl;
} 

int main() {
	vector<string> vec{"the", "quick", "fox", "jumps", 
			"over", "the", "slow", "red", "turtle"};
	elimDups(vec);
}
