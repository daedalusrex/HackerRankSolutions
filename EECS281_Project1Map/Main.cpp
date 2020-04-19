#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <filesystem>

#include "Map.h"

using namespace std;


int main(void) {

	Map quicktest(8,4,4);

	quicktest.print_map_to_output(cout);

	return 0;
}



/*
Can I do this in C++??  -- Basically no, but the templates trick allows it 

After much reading, I have determined that indeed if doing a flat array
there is no way to use the brackets instead of pointer math
because the compiler has no way of knowing the size of the dynamic array provided 
at run time, and so it cannot translate the brackets into actual math operations on memory
which is what the programmer must do. Casting will not work for the same reason.
Templates also occur at compile time.
Or, of course, just use an STL/boost class which have already been built to solve these problems

C has VLA's and C++ does not 
So in fact they are sort of making us do this the hard or wrong way
because they wanted us to learn, and not just get the STL


void arr_alloc (size_t x, size_t y, int(**aptr)[x][y])
{
  *aptr = malloc( sizeof(int[x][y]) ); // allocate a true 2D array
  assert(*aptr != NULL);
}


template<size_t size1, size_t size2>
int sub (int (&a)[size1][size2]) {
    // ...
}
int main() {
    int a[2][2];
    sub(a);
}

void arr_fill (size_t x, size_t y, int array[x][y])
{
  for(size_t i=0; i<x; i++)
  {
    for(size_t j=0; j<y; j++)
    {
      array[i][j] = (int)j + 1;
    }
  }
}

void arr_print (size_t x, size_t y, int array[x][y])
{
  for(size_t i=0; i<x; i++)
  {
    for(size_t j=0; j<y; j++)
    {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}

#include <iostream>

// X x Y x Z matrix
#define X 2
#define Y 3
#define Z 4

// Dynamic Memory Allocation in C++ for 3D Array
int main()
{
	// dynamically allocate memory of size X*Y*Z
	int* A = new int[X * Y * Z];

	// assign values to allocated memory
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
				*(A + i*Y*Z + j*Z + k) = rand() % 100;

	// print the 3D array
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			for (int k = 0; k < Z; k++)
				std::cout << *(A + i*Y*Z + j*Z + k) << " ";

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	// deallocate memory
	delete[] A;

	return 0;
}

*/