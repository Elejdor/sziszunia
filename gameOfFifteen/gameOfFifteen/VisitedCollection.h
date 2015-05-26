#pragma once
#include "common.h"
#include <assert.h>

struct Chunk
{
	void Init(byte blocks);
	void Destroy();
	byte Add(Node & const element);
	Node* pData;
	byte firstAvailableBlock, blocksAvailable;
};

class VisitedCollection
{
private:
	Chunk* chunks;
public:
	void Reallocate();
	VisitedCollection();
	~VisitedCollection();
};

