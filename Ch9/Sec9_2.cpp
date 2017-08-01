#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using std::vector;
using std::cout;
using std::endl;

void iterInit() {
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	vector<int> sublist(ivec.begin(), ivec.begin() + 3);
	for (int i : sublist)
		cout << i << " ";
	cout << endl;
}


/* Container adapters
1. stack and queue are implemented by Deque
2. priority_queue is implemented by Vector
*/
void stackAdapter() {
	std::stack<int> s;
	for (std::size_t ix = 0; ix != 10; ++ix)
		s.push(ix);
	while (!s.empty()) {
		int value = s.top();
		cout << value << " ";
		s.pop();	// pop() returns void
	}
	cout << endl;
}

void queueAdapter() {
	std::queue<int> q;
	for (std::size_t ix = 0; ix != 10; ++ix)
		q.push(ix);		// push to the end of queue
	while (!q.empty()) {
		int head = q.front();
		cout << head << " ";
		q.pop();
	}
	cout << endl;
}

int main() {
	// iterInit();
	stackAdapter();
	queueAdapter();
}
