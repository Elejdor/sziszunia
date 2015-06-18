#include <Windows.h>
#include <cstdio>
#include <vector>
#include <emmintrin.h>
#include <malloc.h>

#include "Globals.h"
#include "HRTimer.h"

void Iterator();
void FindIf();
void RegularFor();

const unsigned long size = 10000000; //10 000 000 B = 10 MB
const int countMul = 1;

void ResetArrays();

Data a[size];
Data b[size];
Data result[size];
std::vector<int>* numbers = new std::vector<int>(size);


int main()
{
	Tester("Iterators", &Iterator);
	Tester("FindIf", &FindIf);

	Tester("Regular", &RegularFor);

	delete(numbers);
	system("pause");

	return 0;
}

void RegularFor()
{

}

void FindIf()
{

}

void Iterator()
{

}

void ResetArrays()
{
	for (unsigned int i = 0; i < size; ++i)
	{
		a[i].x = (float)i;
		a[i].y = (float)i  * 0.1f;
		a[i].z = (float)i  * 0.2f;
		a[i].w = (float)i  * 0.3f;

		b[i].x = (float)i;
		b[i].y = (float)i * 0.2f;
		b[i].z = (float)i * 0.3f;
		b[i].w = (float)i * 0.4f;
	}
}