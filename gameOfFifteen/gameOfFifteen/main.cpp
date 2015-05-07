#include <vector>
#include <queue>
#include <stack>

#define U_CHAR unsigned char
typedef U_CHAR byte;

struct Node
{
	byte board[4][4];
};

std::vector<Node> visitedNodes;

Node root = {
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

	while (!queue.empty())
	{

	}
}

int main()
{
	IterativeBFS();
	return 0;
}