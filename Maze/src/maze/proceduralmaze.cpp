#include <iostream>
#include "proceduralmaze.h"

int main(void)
{
	CellPos cell1(5, 5);
	CellPos cell2(5, 7);
	CellPos cell3 = cell1 - cell2;

	std::cout << cell1.x << " " << cell1.y << std::endl;
	std::cout << cell2.x << " " << cell2.y << std::endl;
	std::cout << cell3.x << " " << cell3.y << std::endl;

	CellPos cell4 = cell3;
	std::cout << (cell4 == cell3 ? "true" : "false") << std::endl;
	return 0;
}