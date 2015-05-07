#include <vector>
#include <queue>
#include <stack>

#define U_CHAR unsigned char
typedef U_CHAR byte;

std::vector<byte[4][4]> visitedNodes;

byte root[4][4] = {
	{ 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 8, 9, 10, 11 },
	{ 12, 13, 14, 15 }
};
void IterativeDFS()
{

}
void IterativeBFS()
{
	std::queue<byte[4][4]> bfsQueue;
	bfsQueue.push(root);
}

int main()
{
	return 0;
}