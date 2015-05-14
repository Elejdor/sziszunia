#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <emmintrin.h>
#include <Windows.h>
#include "HRTimer.h"
#define USE_INTRINSINCS

__declspec(align(16))
struct byte2
{
	byte x;
	byte y;

	inline byte2* operator +=(byte2 & const a)
	{
		this->x += a.x;
		this->y += a.y;

		return this;
	}
};

__declspec(align(16))
typedef struct float2
{
	float x, y;

	inline float2* operator +=(float2 & const a)
	{
		this->x += a.x;
		this->y += a.y;

		return this;
	}
};

_declspec(align(16))
struct Node
{
	union
	{
		byte board[4][4];
		__m128i m128i;
	};

	byte2 whitePosition;
};

extern inline bool operator ==(Node const & const a, Node const & const b);
extern inline byte2 CalculateWhitePosition(const Node* node);
extern inline bool FieldExists(byte2 & const position);