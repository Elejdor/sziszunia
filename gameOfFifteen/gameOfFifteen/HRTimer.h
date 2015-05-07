#pragma once
#include <Windows.h>
#include <cstdio>

class HRTimer
{
public:
	HRTimer();
	~HRTimer();

	double GetFrequency() const;
	void Start();
	void Stop();
	__int64 ElapsedTime() const;

private:
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	double frequency;
};

