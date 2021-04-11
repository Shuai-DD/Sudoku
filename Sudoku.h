#pragma once
//用以储存多个棋盘
struct SudokuGrids
{
	int solutions = 0;//解的个数
	bool unique_sign = 0;//是否唯一解
	bool solution_sign = 0;//是否有解
	int suduku_grid[9][9];
	SudokuGrids* next_grid;
	SudokuGrids* last_grid;
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
	bool JudgeLegitimacy(SudokuGrids* sudoku_grid, int row, int col, int val);//创建时这个判断更快
	bool JudgeLegitimacy1(SudokuGrids* sudoku_grid, int row, int col, int val);//求解时再用这个判断
	bool FillNum(SudokuGrids* sudoku_grid, int row, int col);
	void GenSolutionGrid(int grid_num);
	void GenBaseGrid(int lower_limit, int upper_limit);//挖去终盘中数值以使其成为初盘
	void GridWritter();//输出生成的终盘至solution.txt
	void GridReader(int grid_num);//从solution.txt读取终盘
	void BackTrace(SudokuGrids* sudoku_grid, int n);//回溯法解数独 n = row * 9 + col，只找出一个解
	void BackTrace1(SudokuGrids* sudoku_grid, int n);//找出所有解的个数
	void Solution(SudokuGrids* sudoku_grid, int grid_num);
	void GenUniqeBaseGrid(int grid_num);
};