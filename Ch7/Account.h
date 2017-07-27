// static members in class
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double rate() { return interestRate; }
	static void rate(double);
private:
	std::string owner;
	double amount;
	// static members exist outside any Object
	// There is no "this" pointer for static member and thus can't define const functions
	static double interestRate;
	static constexpr double todayRate = 0.042;
	static double initRate() { return todayRate; }
};

// static class member to be initialized outside the class

double Account::interestRate = initRate();

void Account::rate(double newRate) {
	interestRate = newRate;
}

#endif