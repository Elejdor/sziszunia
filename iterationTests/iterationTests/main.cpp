#include <Windows.h>
#include <cstdio>
#include <vector>
#include <emmintrin.h>
#include <malloc.h>
#include <algorithm>

#include "Globals.h"
#include "HRTimer.h"

void Iterator();
void FindIf();
void RegularFor();
void MyFindIf();


const unsigned long size = 10000000; //10 000 000 B = 10 MB
const int countMul = 1;

void ResetArrays();
void PropagateTestData();

Data a[size];
Data b[size];
Data result[size];
std::vector<Data> datas;
std::vector<int>* numbers = new std::vector<int>(size);

Data pattern = { 999.0f, 99.0f, 9.0f, 0.0f };

int main()
{
	PropagateTestData();

	Tester("Iterators", &Iterator);
	Tester("FindIf", &FindIf);

	Tester("Regular", &RegularFor);
	Tester("MyFindIf", &MyFindIf);


	delete(numbers);
	system("pause");

	return 0;
}

void PropagateTestData()
{
	datas.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		Data tmp;
		float a = 1000 / size;
		tmp.x = a;
		tmp.y = a;
		tmp.z = a;
		tmp.w = a;

		datas.push_back(tmp);
	}

	//datas.at(size - 100) = pattern;
}

void RegularFor()
{
	timer.Start();

	for (int i = 0; i < size; ++i)
	{
		if (datas.at(i) == pattern)
			break;
	}

	timer.Stop();
}

void FindIf()
{
	timer.Start();

	std::vector<Data>::iterator begin = datas.begin();
	std::vector<Data>::iterator end = datas.end();

	std::find_if(begin, end, [](Data data) {
		if (data == pattern)
		{
			return true;
		}
		return false;
	});

	timer.Stop();
}


template<class _InIt,
class _Pr> inline
	_InIt Find_if(_InIt _First, _InIt _Last, _Pr _Pred)
{	// find first satisfying _Pred
		for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			break;
		return (_First);
}

void Iterator()
{
	timer.Start();
	
	std::vector<Data>::iterator iter = datas.begin();
	std::vector<Data>::iterator end = datas.end();

	int i = 0;
	bool result = Find_if(_Unchecked(iter), _Unchecked(end), [&i](Data data) {
		if (data == pattern)
		{
			return true;
		}
		return false;
	});
	


	timer.Stop();

	printf(((result == true) ? "true" : "false"));
}

void MyFindIf()
{
	timer.Start();

	std::vector<Data>::iterator being = datas.begin();
	std::vector<Data>::iterator end = datas.end();

	//_Rechecked(being,
	/*	std::_Find_if(_Unchecked(being), _Unchecked(end), [](Data data) {
		if (data == pattern)
		{
			return true;
		}
		return false;
	}));
*/


	timer.Stop();
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