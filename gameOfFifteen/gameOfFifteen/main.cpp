#include "common.h"
#include "VisitedCollection.h"
#include <thread>

std::vector<Node> visitedNodes;

Node graph = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	0, 0
};

Node solved = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	0, 0
};

inline Node* MoveZeroFromTo(byte2 & const to, Node* const graph)
{
	Node* result = new Node(); //make a copy
	memcpy(result, graph, sizeof(Node));
	result->board[result->whitePosition.y][result->whitePosition.x] = result->board[to.y][to.x];
	result->board[to.y][to.x] = 0;
	result->whitePosition = to;
	return result;
}

void PrintNode(Node* n)
{
	printf("%i %i %i %i\n", n->board[0][0], n->board[0][1], n->board[0][2], n->board[0][3]);
	printf("%i %i %i %i\n", n->board[1][0], n->board[1][1], n->board[1][2], n->board[1][3]);
	printf("%i %i %i %i\n", n->board[2][0], n->board[2][1], n->board[2][2], n->board[2][3]);
	printf("%i %i %i %i\n\n", n->board[3][0], n->board[3][1], n->board[3][2], n->board[3][3]);
}

_declspec(align(16))
typedef struct IntrinInt
{
	union
	{
		__m128i m128i;
		int values[4];
	};
};

void IterativeDFS()
{
	HRTimer timer;

	std::stack<Node*> stack;
	stack.push(&graph);
	unsigned int depth = 0u;

	byte2 zero_position;
	size_t size;
	bool visited;
	Node* current;
	byte2 test_position;
#ifdef USE_INTRINSINCS
	IntrinInt* ress = (IntrinInt*)_aligned_malloc(sizeof(IntrinInt), 16);
#endif

	timer.Start();
	while (!stack.empty())
	{
		current = stack.top();
		stack.pop();

#ifdef USE_INTRINSINCS
		ress->m128i = _mm_cmpeq_epi8(current->m128i, solved.m128i);
		if (ress->m128i.m128i_i64[0] == -1 && ress->m128i.m128i_i64[1] == -1)
#else
		if (*current == solved)
#endif
		{
			break;
		}
		else
			++depth;

		zero_position = CalculateWhitePosition(current);

#ifdef USE_INTRINSINCS
		size = visitedNodes.size();
		visited = true;
		for (size_t i = 0; i < size; ++i)
		{
			ress->m128i = _mm_cmpeq_epi8(current->m128i, visitedNodes[i].m128i);
			if (ress->m128i.m128i_i64[0] == -1 && ress->m128i.m128i_i64[1] == -1)
			{
				visited = false; 
				break;
			}
		}
		if(visited)
#else
		if (std::find(visitedNodes.begin(), visitedNodes.end(), *current) == visitedNodes.end())
#endif
		{
			visitedNodes.push_back(*current);

			test_position = zero_position;
			++test_position.x;
			if (FieldExists(test_position))
				stack.push(MoveZeroFromTo(test_position, current));

			test_position = zero_position;
			++test_position.y;
			if (FieldExists(test_position))
				stack.push(MoveZeroFromTo(test_position, current));

			test_position = zero_position;
			--test_position.y;
			if (FieldExists(test_position))
				stack.push(MoveZeroFromTo(test_position, current));

			test_position = zero_position;
			--test_position.x;
			if (FieldExists(test_position))
				stack.push(MoveZeroFromTo(test_position, current));

		}
	}
	timer.Stop();
	printf("DFS \nPath length: %i\nTime: %i\n\n", depth, timer.ElapsedTime());
}

#pragma region BFS
std::queue<Node*> bfsQueue;

_declspec(align(16))
typedef struct NodePair
{
	Node* key;
	Node* value;
};



std::vector<NodePair*> paths2;
IntrinInt* ress = (IntrinInt*)_aligned_malloc(sizeof(IntrinInt), 16);

bool IsVisited(Node* node)
{
	int visitedSize = visitedNodes.size();
	
	for (int i = 0; i < visitedSize; ++i)
	{
#ifdef USE_INTRINSINCS
		_mm_store_si128(&ress->m128i, _mm_cmpeq_epi8(node->m128i, visitedNodes[i].m128i));
		//ress->m128i = _mm_cmpeq_epi8(current->m128i, visitedNodes[i].m128i);

		if (ress->m128i.m128i_i64[0] == -1 && ress->m128i.m128i_i64[1] == -1)
		{
			return true;
		}
#else
		if (visitedNodes[i] == *node)
		{
			return true;
		}
#endif
	}
	return false;
}


void IterativeBFS()
{
	HRTimer timer;
	
	bfsQueue.push(&graph);
	
	Node* current = new Node();
	byte2 currentPosition;
	byte2 newPosition;

	short visitedSize;
	bool visited;
	int depth = 0;
	 
	timer.Start();
	
#ifdef USE_INTRINSINCS
	visitedNodes.reserve(100000); //1.8 MB

#endif // USE_INTRINSINCS

	while (!bfsQueue.empty())
	{
		
		current = bfsQueue.front();
		bfsQueue.pop();

		visited = false;
		visitedSize = visitedNodes.size();
		
		if (IsVisited(current))
			continue;

		visitedNodes.push_back(*current);
		
#ifdef USE_INTRINSINCS
		//ress->m128i = _mm_cmpeq_epi8(current->m128i, solved.m128i);
		_mm_store_si128(&ress->m128i, _mm_cmpeq_epi8(current->m128i, solved.m128i));
		if (ress->m128i.m128i_i64[0] == -1 && ress->m128i.m128i_i64[1] == -1)
		{
			break;
		}
#else
		if (*current == solved)
			break;
#endif
		currentPosition = current->whitePosition;
		newPosition = current->whitePosition;

		++newPosition.x;
		if (FieldExists(newPosition))
		{
			//tmp = ;
			bfsQueue.push(MoveZeroFromTo(newPosition, current));
			paths2.push_back(new NodePair{ bfsQueue.back(), current });
		}

		newPosition.x -= 2;
		if (FieldExists(newPosition))
		{
			bfsQueue.push(MoveZeroFromTo(newPosition, current));
			paths2.push_back(new NodePair{ bfsQueue.back(), current });
		}

		++newPosition.x;
		newPosition.y += 1;
		if (FieldExists(newPosition))
		{
			bfsQueue.push(MoveZeroFromTo(newPosition, current));
			paths2.push_back(new NodePair{ bfsQueue.back(), current });
		}

		newPosition.y -= 2;
		if (FieldExists(newPosition))
		{
			bfsQueue.push(MoveZeroFromTo(newPosition, current));
			paths2.push_back(new NodePair{ bfsQueue.back(), current });
		}
	}
	timer.Stop();

	std::vector<Node*> path;
	int pathsSize = paths2.size();
	while (!(*current == graph))
	{
		for (int i = 0; i < pathsSize; i++)
		{
			if (paths2[i]->key == current)
			{
				path.push_back(paths2[i]->value);
				current = paths2[i]->value;
				break;
			}
		}
	}

	paths2.clear();

	printf("BFS \nPath length: %i\nTime: %i\n\n", path.size(), timer.ElapsedTime());
}
#pragma endregion

void RandomRoot( const int& const difficultLevel)
{
	int x = 0,
		y = 0;

	byte lastMove = 0;

	for (int i = 0; i < difficultLevel; ++i)
	{
		byte possibleMoves = ~0;
		if (x == 0) possibleMoves &= ~(1 << 0);
		if (y == 0) possibleMoves &= ~(1 << 1);
		if (x == 3) possibleMoves &= ~(1 << 2);
		if (y == 3) possibleMoves &= ~(1 << 3);
		possibleMoves &= ~(1 << lastMove);

		byte move = 0;
		byte m;
		do
		{
			m = rand() % 4;
			move = possibleMoves & (1 << m);
		} while (move == 0);

		if (m == 0) lastMove = 2;
		else if (m == 1) lastMove = 3;
		else if (m == 2) lastMove = 0;
		else if (m == 3) lastMove = 1;

		byte tmp;
		switch (move){
		case (1 << 0) :
			tmp = graph.board[x - 1][y];
			graph.board[x - 1][y] = graph.board[x][y];
			graph.board[x][y] = tmp;
			--x;
			break;
		case (1 << 1):
			tmp = graph.board[x][y - 1];
			graph.board[x][y - 1] = graph.board[x][y];
			graph.board[x][y] = tmp;
			--y;
			break;
		case (1 << 2):
			tmp = graph.board[x + 1][y];
			graph.board[x + 1][y] = graph.board[x][y];
			graph.board[x][y] = tmp;
			++x;
			break;
		case (1 << 3):
			tmp = graph.board[x][y + 1];
			graph.board[x][y + 1] = graph.board[x][y];
			graph.board[x][y] = tmp;
			++y;
			break;
		}
	}
}

int main()
{
	RandomRoot(12);
	graph.whitePosition = CalculateWhitePosition(&graph);

	//visitedNodes.clear();
	//IterativeDFS();
	visitedNodes.clear();
	IterativeBFS();
	//Node n1 = 
	//{
	//	0, 1, 2, 3,
	//	4, 5, 6, 7,
	//	8, 9, 10, 11,
	//	12, 13, 14, 15,
	//	0, 0	
	//};

	/*Chunk ch;
	ch.Init(5);
	ch.Add(&n1);*/
	//VisitedCollection vc;
	//vc.Add(&n1);
	//n1.board[0][0] = 5;
	//printf("%i", ch.pData[0]->board[0][0]);

	system("pause");
	return 0;
}