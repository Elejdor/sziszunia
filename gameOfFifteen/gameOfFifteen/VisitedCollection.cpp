#include "VisitedCollection.h"

void Chunk::Init(byte blocks)
{
	pData = (Node**)_aligned_malloc(sizeof(Chunk) * blocks, 16);
	firstAvailableBlock = 0;
	blocksAvailable = blocks;		
}

void Chunk::Destroy()
{
	delete[] pData;
}

byte Chunk::Add(Node * element)
{
	if (!blocksAvailable) return 0;
	*(pData + firstAvailableBlock) = element;
	++firstAvailableBlock;
	--blocksAvailable;

	return blocksAvailable;
}

void VisitedCollection::ExtendTo(int size)
{
	chunks = (Chunk**)_aligned_realloc(chunks, sizeof(Chunk) * size, 16);
	int newChunks = size - numberOfChunks;
	for (int i = 0; i < newChunks; i++)
	{
		chunks[numberOfChunks + i] = new Chunk();
		chunks[numberOfChunks + i]->Init(blockSize);
	}
	
	numberOfChunks = size;
	printf("Extended collection \n");
}

void VisitedCollection::Add(Node * element)
{
	if (firstAvailableChunk == numberOfChunks)
		ExtendTo(numberOfChunks + extension);
	
	if (chunks[firstAvailableChunk]->Add(element) == 0)
	{
		++firstAvailableChunk;
		Add(element);
	}

}

Chunk* VisitedCollection::At(int n)
{
	return chunks[n];
}

VisitedCollection::VisitedCollection()
{
	numberOfChunks = 0;
	firstAvailableChunk = 0;
	chunks = nullptr;
}


VisitedCollection::~VisitedCollection()
{
}
