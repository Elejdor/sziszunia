#include "common.h"

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

inline bool FieldExists(byte2 & const position)
{
	if (position.x == 255 | position.x == 4 | position.y == 255 | position.y == 4)
		return false;
	return true;
}