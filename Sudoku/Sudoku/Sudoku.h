#pragma once
class Sudoku {
public:
	int sudoku_[9][9];
	int first_line_[9] = { 1,2,3,4,5,6,7,8,9 };
	int grid_num_;
public:
	void RandomLine(int line[]);
	bool JudgeLegitimacy(int row, int col, int val);
	bool FillNum(int row, int col);
	void GenSolutionGrid(int grid_num);
};