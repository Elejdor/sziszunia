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

int main()
{
	IterativeBFS();
	return 0;
}