#include"Sudoku.h"
#include<time.h>
#include<cstdlib>
#include<iostream>
using namespace std;

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

bool Sudoku::JudgeLegitimacy(int row, int col, int val)
{
	for (int i = 0; i < col; i++)
	{
		if (val == sudoku_[row][col])
		{
			return false;
		}
	}
	for (int i = 0; i < row; i++)
	{
		if (val == sudoku_[i][col])
		{
			return false;
		}
	}
	int count = col % 3 + row % 3 * 3;
	while (count--)
	{
		if (val == sudoku_[row / 3 * 3 + count / 3][col / 3 * 3 + count % 3])
		{
			return false;
		}
	}
	return true;
}
bool Sudoku::FillNum(int row, int col)
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
		if (JudgeLegitimacy(row, col, filling_num))
		{
			sudoku_[row][col] = filling_num;
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
			if (FillNum(new_row, new_col))
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
	for (int i = 0; i < grid_num_; i++)
	{
		RandomLine(first_line_);
		for (int j = 0; j < 9; j++)
		{
			sudoku_[0][j] = first_line_[j];
		}
		FillNum(1, 0);
		for (int m = 0; m < 9; m++)
		{
			for (int n = 0; n < 9; n++)
			{
				cout << sudoku_[m][n] << " ";
			}
			cout << endl;
		}
	}
}