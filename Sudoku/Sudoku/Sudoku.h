#pragma once
//用以储存多个棋盘
struct SudokuGrids
{
	int suduku_grid[9][9];
	SudokuGrids* next_grid;
	SudokuGrids();
	void print();
};
class Sudoku {
public:
	SudokuGrids* sudoku_grids_;
	int first_line_[9] = { 1,2,3,4,5,6,7,8,9 };
	int grid_num_;//棋盘数目
public:
	void RandomLine(int line[]);
	bool JudgeLegitimacy(SudokuGrids* sudoku_grid, int row, int col, int val);
	bool FillNum(SudokuGrids* sudoku_grid, int row, int col);
	void GenSolutionGrid(int grid_num);
	void GenBaseGrid(int lower_limit, int upper_limit);//挖去终盘中数值以使其成为初盘
	void GridWritter();//输出生成的终盘至solution.txt
};