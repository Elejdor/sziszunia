#pragma once
#include "common.h"

struct Chunk
{
	void Init(byte blocks);
	void Destroy();
	byte Add(Node * element);
	Node *(*pData);
	byte firstAvailableBlock, blocksAvailable;
};

class VisitedCollection
{
private:
	Chunk** chunks;
	int firstAvailableChunk = 0;
	const int blockSize = 5;
	const int extension = 5;
	int numberOfChunks = 0;

public:
	void ExtendTo(int size);
	void Add(Node * element);
	Chunk* At(int n);
	VisitedCollection();
	~VisitedCollection();
};

