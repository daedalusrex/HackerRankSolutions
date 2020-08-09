/* A TO I Interview Question*/
#include <iostream>
#include <limits>
using namespace std;

int a_to_i_simple(char* str)
{
	int sum = 0;
	while (*str != '\0')
	{
		sum *= 10;
		sum += *str - '0';
		str++;
	}
	return sum;
}


// Please create a function that receives a null terminated c-string of chars and returns an integer. 
int atoi_complex(char* str)
{
	//Walk through string, shift previous numbers by 10, add new number
	int sum = 0;
	int sign = 1;

	//if it is negative, then recall this later
	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str != '\0')
	{
		//if char *a is not a numeric integral value return NAN, as error 
		if (*str < '0' || *str > '9')
			return NAN;

		//Overflow Detection (Simple), principle that if overflow occurs it wraps around. 
		int previous_sum = sum;
		//temp variable for readability
		int digit = *str - '0';

		//Overflow Detection (Correct), work backwards from limits
		//Signed integer overflow behavior is undefined
		if (sum > INT_MAX / 10) /* `sum * 10` would overflow */
			return NAN;
		else
			sum *= 10;
		//Overflow Detection (Correct), check operation based on limits
		if (sum > INT_MAX - digit) /* `sum + digit` would overflow */
			return NAN;
		else
			sum += digit;

		//Overflow Detection (Simple), Only works with unsigned integers, in C
		if (sum < previous_sum)
			return NAN;
		//increment through the string
		str++;
	}
	//Apply the previously determined sign.
	sum *= sign;
	return sum;
}

/*
More Details on Overflow
In C programming language, a computation of unsigned integer values can never overflow,
This means that UINT_MAX + 1 yields zero. According to the C standard unsigned integer operations do wrap around

The C Standard, 6.2.5, paragraph 9[ISO / IEC 9899:2011], states:
A computation involving unsigned operands can never overflow, because a result that cannot be represented
by the resulting unsigned integer type is reduced modulo the number
that is one greater than the largest value that can be represented by the resulting type.
*/
/*
Retarding Signed Integers, the behavior is technically undefined.
So you must check before overflow occurs, using Integer Limits
https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-multiply-overflow
*/

int main(void)
{
	char initlazy[20] = { '-','1','2','3','4','5','6','7','8','9','\0' };

	int result = atoi_complex(initlazy);

	cout << result << endl;

	return 0;
}