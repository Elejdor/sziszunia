#include "VisitedCollection.h"

void Chunk::Init(byte blocks)
{
	pData = (Node*)_aligned_malloc(sizeof(Chunk) * blocks, 16);
	firstAvailableBlock = 0;
	blocksAvailable = blocks;		
}

void Chunk::Destroy()
{
	delete[] pData;
}

byte Chunk::Add(Node & const element)
{
	if (!blocksAvailable) return 0;
	pData[firstAvailableBlock] = element;
	--blocksAvailable;
}

void VisitedCollection::Reallocate()
{

}

VisitedCollection::VisitedCollection()
{
}


VisitedCollection::~VisitedCollection()
{
}
