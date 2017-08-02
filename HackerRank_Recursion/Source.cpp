#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long sum_digits(long digits)
{
	if (digits<10)
		return digits;

	return (digits % 10 + sum_digits(digits / 10));
}


long super_digit(long input)
{
	if (input < 10)
		return (int)input;

	return super_digit(sum_digits(input));

}

long howmanydigits(long num)
{
	if (num < 10)
		return 1;

	return 1 + howmanydigits(num / 10);
}

long buildnum(long n, long k, long digitsize)
{
	if (k == 1)
		return n;

	return n + buildnum(pow(10,digitsize) * n, k - 1, digitsize);
}


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	
	long k, n;
	cin >> n >> k;

	long numdigitsn = howmanydigits(n);
	long mydigit = buildnum(n, k,numdigitsn);

	cout << super_digit(mydigit);

	cin >> k;

	return 0;
}
