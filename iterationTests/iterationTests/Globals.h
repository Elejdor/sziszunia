#pragma once
#include "HRTimer.h"
#include <vector>
#include <ctime>
#include <random>

extern HRTimer timer;
extern std::vector<int>* const GenerateIArray(const u_int* const size);
extern std::vector<float>* const GenerateFArray(const int* const size);
extern void Tester(char* testName, void(*test)());

typedef  struct Data
{
	float x, y, z, w;

};

extern bool operator ==(Data & const A, Data & const B);