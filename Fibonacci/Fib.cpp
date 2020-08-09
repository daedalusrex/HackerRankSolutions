#include <iostream>
#include <vector>
using namespace std;

//Starting at the value of start, which should be in the Fib sequence, 
//Print to standard out the next "number" of the fibonacci sequence 
void Fibonacci(int start, int number)
{
	//Compiler correct
	int* f = new int[number + 2];
	//Acceptable in interview
	//int f[number + 2];

	f[0] = 0;
	f[1] = 1;

	//Count the Fib Sequence until we acquire the start value, or we pass it
	//while(!(f[1] > start)) Could also work
	while (f[1] != start && f[1] < start)
	{
		int temp = f[1];
		f[1] += f[0];
		f[0] = temp;
	}

	//if start is not in the fib sequence, abort
	if (f[1] != start)
		return;

	for (int i = 2; i <= number; i++)
	{

		f[i] = f[i - 1] + f[i - 2];
		cout << f[i] << " ";
	}

}

int fib(int n)
{
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

void Fibonacci_Rec(int start, int number)
{


	fib(number);
}

int main(void)
{

	Fibonacci(3, 3);

	return 0;
}