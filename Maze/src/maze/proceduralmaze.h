#ifndef __PROCEDURALMAZE_H__
#define __PROCEDURALMAZE_H__

struct CellPos
{
	int x;
	int y;

	CellPos(int x = 0, int y = 0) : x(x), y(y) {}

	CellPos operator-(const CellPos& other)
	{
		CellPos result;
		result.x = (other.x - x)/2 + x;
		result.y = (other.y - y)/2 + y;

		return result;
	}

	bool operator==(const CellPos& other)
	{
		return (x == other.x && y == other.y);
	}
};

#endif