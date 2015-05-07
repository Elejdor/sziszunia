#include <vector>
#include <queue>
#include <stack>

typedef char byte;

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



struct Node
{
	byte2 whitePosition;
	byte board[4][4];

	inline bool operator ==(Node& a)
	{
		for (byte i = 0; i < 4; i++)
		{
			for (byte j = 0; j < 4; j++)
			{
				if (this->board[i][j] != a.board[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
};

std::vector<Node> visitedNodes;

Node graph = {
	0, 0,
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15
};

byte solved[4][4] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15
};

void IterativeDFS()
{

}

inline bool FieldExists(byte2 position)
{
	if (position.x == -1 | position.x == 4 | position.y == -1 | position.y == 4)
		return false;
	return true;
}

inline Node MoveZeroFromTo(byte2 to, Node* graph)
{
	Node result = *graph; //make a copy
	result.board[graph->whitePosition.y][graph->whitePosition.x] = result.board[to.y][to.x];
	result.board[to.y][to.x] = 0;
	result.whitePosition = to;
	return result;
}

inline byte2 CalculateWhitePosition(Node* node)
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
void IterativeBFS()
{
	std::queue<Node> queue;
	queue.push(graph);

	Node* current;
	byte2 currentPosition;
	byte2 newPosition;
	short visitedSize;
	bool visited;
	int depth = 0;

	while (!queue.empty())
	{
		current = &queue.front();
		queue.pop();

		visited = false;
		visitedSize = visitedNodes.size();

		for (short i = 0; i < visitedSize; i++)
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

		if (current->board == solved)
		{
			break;
		}

		currentPosition = current->whitePosition;
		newPosition = current->whitePosition;
		newPosition.x += 1;

		if (FieldExists(newPosition))
		{
			queue.push(MoveZeroFromTo(newPosition, current));
		}

		newPosition.x -= 2;
		if (FieldExists(newPosition))
		{
			queue.push(MoveZeroFromTo(newPosition, current));
		}

		newPosition.x = currentPosition.x;
		newPosition.y += 1;
		if (FieldExists(newPosition))
		{
			queue.push(MoveZeroFromTo(newPosition, current));
		}

		newPosition.y -= 2;
		if (FieldExists(newPosition))
		{
			queue.push(MoveZeroFromTo(newPosition, current));
		}
	}

	printf("%i", depth);
}

void RandomRoot(int difficultLevel)
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
	//IterativeBFS();
	system("pause");
	return 0;
}