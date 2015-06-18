#include "Globals.h"



HRTimer timer;

std::vector<int>* const GenerateIArray(const u_int* const size)
{
	std::vector<int>* result = new std::vector<int>();

	std::srand((unsigned int)time(NULL));

	for (int i = 0; i < *size; ++i)
	{
		//result->push_back(std::rand());
		result->push_back(i);
	}
		
	
	return result;
}

std::vector<float>* const GenerateFArray(const int* const size)
{
	std::vector<float>* result = new std::vector<float>();

	std::srand((unsigned int)time(NULL));

	for (int i = 0; i < *size; ++i)
	{
		//result->push_back(std::rand());
		result->push_back(i);
	}


	return result;
}

void Tester(char* testName, void(*test)())
{
	__int64 timeMS = 0;

	test();
	timeMS = timer.ElapsedTime();
	printf("%s: %i ms\n", testName, timeMS);
}