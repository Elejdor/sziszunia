#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <thread>
#include "HRTimer.h"
#include <mmintrin.h>
#include <xmmintrin.h>

//typedef char byte;

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

_declspec(align(16))
struct Node
{
	byte board[4][4];
	byte2 whitePosition;
};

inline bool operator ==(Node const & const a, Node const & const b)
{
	for (byte i = 0; i < 4; i++)
	{
		for (byte j = 0; j < 4; j++)
		{
			if (a.board[i][j] != b.board[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

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


inline bool FieldExists(byte2 & const position)
{
	if (position.x == 255 | position.x == 4 | position.y == 255 | position.y == 4)
		return false;
	return true;
}

inline Node* MoveZeroFromTo(byte2 & const to, Node* const graph)
{
	Node* result = new Node(); //make a copy
	memcpy(result, graph, sizeof(Node));
	result->board[result->whitePosition.y][result->whitePosition.x] = result->board[to.y][to.x];
	result->board[to.y][to.x] = 0;
	result->whitePosition = to;
	return result;
}

inline byte2 CalculateWhitePosition(const Node* node)
{
	for (byte i = 0; i < 4; i++)
	{
		for (byte j = 0; j < 4; j++)
		{
			if (node->board[i][j] == 0)
				return{ j, i };
		}
	}
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


void IterativeDFS()
{
	std::stack<Node*> stack;
	stack.push(&graph);
	unsigned int depth = 0u;

	byte2 zero_position;

	while (!stack.empty())
	{
		Node* current = stack.top();
		stack.pop();
		if (*current == solved)
		{
			printf("DFS: %i\n", depth);
			break;
		}
		else
			++depth;

		zero_position = CalculateWhitePosition(current);
		if (std::find(visitedNodes.begin(), visitedNodes.end(), *current) == visitedNodes.end())
		{
			visitedNodes.push_back(*current);

			byte2 test_position;

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
		else
		{
			printf("hit\n");
		}
	}
}

void IterativeBFS()
{
	HRTimer timer;
	
	bfsQueue.push(&graph);
	
	Node* current = nullptr;
	byte2 currentPosition;
	byte2 newPosition;
	short visitedSize;
	bool visited;
	int depth = 0;
	//Node* tmp;

	timer.Start();
	while (!bfsQueue.empty())
	{
		
		current = bfsQueue.front();
		bfsQueue.pop();

		visited = false;
		visitedSize = visitedNodes.size();

		for (short i = 0; i < visitedSize; ++i)
		{
			if (visitedNodes[i] == *current)
			{
				visited = true;
				break;
			}
		}

		if (visited)
			continue;

		visitedNodes.push_back(*current);

		if (*current == solved)
			break;

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
	RandomRoot(14);
	graph.whitePosition = CalculateWhitePosition(&graph);

	visitedNodes.clear();
	IterativeDFS();
	visitedNodes.clear();
	//IterativeBFS();
	system("pause");
	return 0;
}