#include"Sudoku.h"
int main()
{
	Sudoku s;
	s.GenSolutionGrid(2);
	s.GenBaseGrid(20, 55);
	s.GridWritter();
}