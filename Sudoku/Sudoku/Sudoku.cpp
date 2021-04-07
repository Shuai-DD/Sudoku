#include"Sudoku.h"
#include<time.h>
#include<cstdlib>
#include<iostream>
using namespace std;

SudokuGrids::SudokuGrids()
{
	this->next_grid = NULL;
}

void SudokuGrids::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << this->suduku_grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Sudoku::RandomLine(int line[])
{
	int temp_num, random_num;
	for (int i = 0; i < 9; i++)
	{
		random_num = rand() % 9;
		temp_num = line[random_num];
		line[random_num] = line[i];
		line[i] = temp_num;
	}
}

bool Sudoku::JudgeLegitimacy(SudokuGrids* sudoku_grid, int row, int col, int val)
{
	for (int i = 0; i < col; i++)
	{
		if (val == sudoku_grid->suduku_grid[row][col])
		{
			return false;
		}
	}
	for (int i = 0; i < row; i++)
	{
		if (val == sudoku_grid->suduku_grid[i][col])
		{
			return false;
		}
	}
	int count = col % 3 + row % 3 * 3;
	while (count--)
	{
		if (val == sudoku_grid->suduku_grid[row / 3 * 3 + count / 3][col / 3 * 3 + count % 3])
		{
			return false;
		}
	}
	return true;
}
bool Sudoku::FillNum(SudokuGrids* sudoku_grid,int row, int col)
{
	int new_col, new_row;
	if (row > 8)
	{
		return true;
	}
	int random_num = rand() % 9 + 1;
	for (int i = 9; i > 0; i--)
	{
		int filling_num = (random_num + i) % 9 + 1;
		if (JudgeLegitimacy(sudoku_grid, row, col, filling_num))
		{
			sudoku_grid->suduku_grid[row][col] = filling_num;
			if (col == 8)
			{
				new_row = row + 1;
				new_col = 0;
			}
			else 
			{
				new_row = row;
				new_col = col + 1;
			}
			if (FillNum(sudoku_grid, new_row, new_col))
			{
				return true;
			}
		}
	}
	return false;
}

void Sudoku::GenSolutionGrid(int grid_num)
{
	grid_num_ = grid_num;
	srand(time(NULL));
	SudokuGrids* temp_grid = new SudokuGrids;
	sudoku_grids_ = temp_grid;
	RandomLine(first_line_);
	for (int j = 0; j < 9; j++)
	{
		temp_grid->suduku_grid[0][j] = first_line_[j];
	}
	FillNum(temp_grid, 1, 0);
	SudokuGrids* next_grid;
	for (int i = 0; i < grid_num_-1; i++)
	{
		next_grid = new SudokuGrids;
		temp_grid->next_grid = next_grid;
		RandomLine(first_line_);
		for (int j = 0; j < 9; j++)
		{
			next_grid->suduku_grid[0][j] = first_line_[j];
		}
		FillNum(next_grid, 1, 0);
		temp_grid = next_grid;
		
	}
	temp_grid = sudoku_grids_;
	while (temp_grid)
	{
		temp_grid->print();
		temp_grid = temp_grid->next_grid;
	}
	
}