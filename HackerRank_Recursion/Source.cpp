#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;




int sum_digits(string digits)
{
	//First attempt, but integral types are too small
	//if (digits.size() == 1)
	//	return digits;

	//return (digits % 10 + sum_digits(digits / 10));

	if (digits.size() == 1)
		return stoi(digits);

	int back_digit = atoi(&digits.back());
	digits.pop_back();

	return back_digit + sum_digits(digits);

}



string super_digit(string input)
{
	if (input.size() == 1)
		return input;


	return super_digit(to_string(sum_digits(input)));

}

long howmanydigits(long num)
{
	if (num < 10)
		return 1;

	return 1 + howmanydigits(num / 10);
}

string buildnum(long n, long k)
{
	if (k == 1)
		return to_string(n);

	return to_string(n) + buildnum(n, k - 1);
}


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	
	long k, n;
	cin >> n >> k;

	long numdigitsn = howmanydigits(n);
	//It must be a string since long is not big enough to hold 10^10000
	string mydigit = buildnum(n, k);

	cout << super_digit(mydigit);

	cin >> k;

	return 0;
}
