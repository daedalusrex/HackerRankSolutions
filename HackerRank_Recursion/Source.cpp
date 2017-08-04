#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


long long MostDigs = 0;


long long number_sum(long long myeighteen)
{
	if (myeighteen < 10)
		return myeighteen;

	return (myeighteen % 10) + number_sum(myeighteen / 10);
}

long long sum_digits(string digits)
{
	//First attempt, but integral types are too small
	//if (digits.size() == 1)
	//	return digits;

	//return (digits % 10 + sum_digits(digits / 10));

	//Causes a stack overflow before the limits of the problem
	/*if (digits.size() == 1)
		return stoi(digits);

	long long back_digit = atoi(&digits.back());
	digits.pop_back();*/


	//Two possible solutions. Cut back 18 or so digits off and use long long, then recurse on that...maybe not actually better
	//Solution two, split it into two even strings , doing logrithmic recursive calls at once

	/*if (digits.size() < MostDigs)
		return number_sum(stoll(digits));
	

	return sum_digits(digits.substr(0, digits.size()/2)) + sum_digits(digits.substr(digits.size()/2, digits.size()));*/


	//Revision 3, iterative
	long long val = 0;
	while (digits.size() > 0)
	{
		val += stoll(&digits.back());
		digits.pop_back();
	}

	return val;
}



string super_digit(string input)
{
	if (input.size() == 1)
		return input;

	long long sum = sum_digits(input);

	return super_digit(to_string(sum));

}

long long howmanydigits(long long num)
{
	if (num < 10)
		return 1;

	return 1 + howmanydigits(num / 10);
}

string buildnum(string n, long k)
{
	/*if (k == 1)
		return to_string(n);

	return to_string(n) + buildnum(n, k - 1);*/
	

	string building;
	while (k > 0)
	{
		building.append(n);
		k--;
	}

	return building;
}


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	
	long k;
	string n;
	cin >> n >> k;

	MostDigs = howmanydigits(LLONG_MAX);
	MostDigs--;
	//It must be a string since long is not big enough to hold 10^10000
	string mydigit = buildnum(n, k);

	cout << super_digit(mydigit);

	cin >> k;

	return 0;
}
