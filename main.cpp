#include"Sudoku.h"
#include <iostream>
using namespace std;
int main()
{
	Sudoku s;
	s.GenSolutionGrid(2);
	s.sudoku_grids_->print();
	s.sudoku_grids_->next_grid->print();
	s.GenBaseGrid(20,55);
	s.GridWritter();
	s.GridReader(2);
	//s.BackTrace(s.sudoku_grids_, 0, 0);
	//s.BackTrace(s.sudoku_grids_->next_grid, 0, 0);
	s.Solution(s.sudoku_grids_, 2);
	//cout << endl << s.sudoku_grids_->solutions << endl << s.sudoku_grids_->next_grid->solutions << endl;
	//s.sudoku_grids_->print();
	//s.sudoku_grids_->next_grid->print();
}