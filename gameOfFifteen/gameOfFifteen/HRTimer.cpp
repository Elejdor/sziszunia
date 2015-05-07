#include "HRTimer.h"

HRTimer::HRTimer() : start(), stop(), frequency()
{
	frequency = this->GetFrequency();
}


HRTimer::~HRTimer()
{
}


double HRTimer::GetFrequency() const
{
	LARGE_INTEGER proc_freq;

	if (!QueryPerformanceFrequency(&proc_freq))
		printf("\nFailed 0\n");

	//ms 1000
	return proc_freq.QuadPart / 1000;
}

void HRTimer::Start()
{
	QueryPerformanceCounter(&start);
}

void HRTimer::Stop()
{
	QueryPerformanceCounter(&stop);
}

__int64 HRTimer::ElapsedTime() const
{
	return (__int64)((stop.QuadPart - start.QuadPart) / frequency);
}