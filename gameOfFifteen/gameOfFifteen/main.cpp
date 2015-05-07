#include <vector>
#include <queue>
#include <stack>

#define U_CHAR unsigned char
typedef U_CHAR byte;

struct Node
{
	byte board[4][4];

	bool operator ==(Node& a)
	{
		for (byte i = 0; i < 4; i++)
		{
			for (byte j = 0; j < 4; j++)
			{
				if (this->board[j][i] != a.board[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}
};

std::vector<Node> visitedNodes;

Node root = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15
};

Node solved = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15
};

void IterativeDFS()
{

}
void IterativeBFS()
{
	std::queue<Node> queue;
	queue.push(root);
	Node* current;

	while (!queue.empty())
	{
		current = &queue.back();
		queue.pop();

		if (*current == solved)
		{
			return;
		}
		else
		{

		}
	}
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
			tmp = root.board[x - 1][y];
			root.board[x - 1][y] = root.board[x][y];
			root.board[x][y] = tmp;
			--x;
			break;
		case (1 << 1):
			tmp = root.board[x][y - 1];
			root.board[x][y - 1] = root.board[x][y];
			root.board[x][y] = tmp;
			--y;
			break;
		case (1 << 2):
			tmp = root.board[x + 1][y];
			root.board[x + 1][y] = root.board[x][y];
			root.board[x][y] = tmp;
			++x;
			break;
		case (1 << 3):
			tmp = root.board[x][y + 1];
			root.board[x][y + 1] = root.board[x][y];
			root.board[x][y] = tmp;
			++y;
			break;
		}
	}
}

int main()
{
	IterativeBFS();
	return 0;
}