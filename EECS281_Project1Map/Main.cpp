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

using namespace std;

//#define Levels 3
//#define Rows 4
//#define Columns 6

int main(void) {

	size_t Levels = 3;
	size_t Rows = 4;
	size_t Columns = 6;


    int* map = new int[Levels * Rows * Columns];
	int counter = 0;
    	// assign values to allocated memory
	for (int i = 0; i < Levels; i++)
	{
		cout << "Level " << i << endl;
		for (int j = 0; j < Rows; j++)
		{
			for (int k = 0; k < Columns; k++)
			{
				map[i * Rows * Columns + j * Columns + k] = counter;
				//map[i*Rows*Columns + j*Columns + k] = 'a' + counter;
				//*(map + i * Rows * Columns + j * Columns + k) = 'a' + counter;
				cout << *(map + i * Rows * Columns + j * Columns + k) << " ";
				//counter = (counter+1) % ('z'-'a' + 1);
				counter++;
			}
			cout << "\n";
		}
	}
	

	//conversion from flat array index to 3 indexs
	//size_t flat_indext_test = (Levels - 1) * (Rows - 1) * (Columns - 1) +15;
	size_t flat_indext_test = 1;
	size_t origin = flat_indext_test;
	size_t lev =0, row= 0, col = 0;
	while (flat_indext_test > (Columns * Rows * (lev+1))) //use more modululs
		lev++;

	flat_indext_test = flat_indext_test % (Columns * Rows); //could also subtract calculation
	
	while (flat_indext_test > ((row+1) * Columns))
		row++;

	col = flat_indext_test % Columns;


	cout << "\n\n\ncomplex index of " << origin << " is \n" << lev << " " << row << " " << col << "\n\n\n"<<endl;

	//better way
	flat_indext_test = origin;
	lev = row = col = 0;
	
	//col = flat_indext_test % Columns; //maybe need to subtract
	//row = ((flat_indext_test - col) % (Rows * Columns)) / Columns;
	//lev = (flat_indext_test - row - col + 1) / (Rows * Columns);

	col = flat_indext_test % Columns; 
	row = ((flat_indext_test) % (Rows * Columns)) / Columns;
	lev = (flat_indext_test) / (Rows * Columns);


	cout << "\n\n\nBetter way with mod complex index of " << origin << " is \n" << lev << " " << row << " " << col << "\n\n\n" << endl;

	//test memset, confirmed it works
	memset(map, 'X', Levels * Rows * Columns);
	for (int i = 0; i < Levels; i++)
	{
		cout << "Level " << i << endl;
		for (int j = 0; j < Rows; j++)
		{
			for (int k = 0; k < Columns; k++)
				cout << *(map + i * Rows * Columns + j * Columns + k) << " ";
			cout << "\n";
		}
	}


	delete[] map;
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