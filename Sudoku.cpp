#define _CRT_SECURE_NO_WARNINGS
#include"Sudoku.h"
#include<time.h>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<stdio.h>
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
		if (val == sudoku_grid->suduku_grid[row][i])
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

bool Sudoku::JudgeLegitimacy1(SudokuGrids* sudoku_grid, int row, int col, int val)
{
	for (int i = 0; i < 9; i++)
	{
		if (val == sudoku_grid->suduku_grid[row][i])
		{
			return false;
		}
	}
	for (int i = 0; i < 9; i++)
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
/*于此处产生随机数种子*/
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
	/*temp_grid = sudoku_grids_;
	while (temp_grid)
	{
		temp_grid->print();
		temp_grid = temp_grid->next_grid;
	}*/
	
}

void Sudoku::GenBaseGrid(int lower_limit, int upper_limit)
{
	int blank_num, blank_point;
	SudokuGrids* temp_grid = sudoku_grids_;
	for (int i = 0; i < grid_num_; i++)
	{
		blank_num = lower_limit + rand() % (upper_limit - lower_limit);
		int blank_num_oneline = blank_num / 9;
		for (int j = 0; j < 9; j++)
		{
			for (int m = 0; m < blank_num_oneline; m++)
			{
				blank_point = rand() % 9;
				if (temp_grid->suduku_grid[j][blank_point] == 0)
				{
					m--;
				}
				else
				{
					temp_grid->suduku_grid[j][blank_point] = 0;
				}
			}
		}
		blank_num_oneline = blank_num % 9;
		int random_line = rand() % 9;
		for (int m = 0; m < blank_num_oneline; m++)
		{
			int blank_point = rand() % 9;
			if (temp_grid->suduku_grid[random_line][blank_point] == 0)
			{
				random_line--;
			}
			else
			{
				temp_grid->suduku_grid[random_line][blank_point] = 0;
			}
		}
		temp_grid = temp_grid->next_grid;
	}
}

void Sudoku::GridWritter()
{
	ofstream writter("solution.txt");
	SudokuGrids* temp_grid = sudoku_grids_;
	if (writter.is_open())
	{
		for (int i = 0; i < grid_num_; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					writter << temp_grid->suduku_grid[j][k] << " ";
				}
				writter << endl;
			}
			writter << endl;
			temp_grid = temp_grid->next_grid;
		}
	}
	temp_grid = sudoku_grids_;
	while (temp_grid)
	{
		temp_grid->print();
		temp_grid = temp_grid->next_grid;
	}

}

void Sudoku::GridReader(int grid_num)
{
	grid_num_ = grid_num;

	char all_grids[2000];//用数组存整个txt文档
	int length = 0;//数组长度
	FILE* reader;
	reader = fopen("solution.txt", "r");
	if (reader == NULL)return;
	while (1) 
	{
		char c;
		c = fgetc(reader);
		if (c == EOF) break;
		all_grids [length] = c;
		length++;
	}
	fclose(reader);
	//读取文件


	//for (int i = 0; i <= length; i++)cout << all_grids[i];
	int tail = 0;//数组下标
	for (int n = 0; n < grid_num; n++)
	{
		
		SudokuGrids* temp_grid = sudoku_grids_;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				this->sudoku_grids_->suduku_grid[i][j] = all_grids[tail] - '0';
				//cout << this->sudoku_grids_->suduku_grid[i][j] << " ";
				tail += 2;
			}
			tail++;
			//cout << endl;
		}
		tail++;
		if (n == grid_num - 1)break;
		this->sudoku_grids_ = this->sudoku_grids_->next_grid;
		this->sudoku_grids_->last_grid = temp_grid;
		//cout << endl;
	}
	for (int i = 0; i < grid_num - 1; i++)
	{
		this->sudoku_grids_ = this->sudoku_grids_->last_grid;
	}
	//sudoku_grids_->print();
}

void Sudoku::BackTrace(SudokuGrids* sudoku_grid, int n)
{
	if (n == 81)
	{
		sudoku_grid->solution_sign = 1;
		return;
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] != 0)
	{
		BackTrace(sudoku_grid, n + 1);
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			if (JudgeLegitimacy1(sudoku_grid, n / 9, n % 9, i))
			{
				sudoku_grid->suduku_grid[n / 9][n % 9] = i;
				BackTrace(sudoku_grid, n + 1);
				if (sudoku_grid->solution_sign == 1)
				{
					return;
				}
				sudoku_grid->suduku_grid[n / 9][n % 9] = 0;
			}
		}
	}
}

void Sudoku::BackTrace1(SudokuGrids* sudoku_grid, int n)
{
	if (n == 81)
	{
		//sudoku_grid->solutions++;
		sudoku_grid->solution_sign = 1;
		return;
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] != 0)
	{
		BackTrace1(sudoku_grid, n + 1);
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			if (JudgeLegitimacy1(sudoku_grid, n / 9, n % 9, i))
			{
				sudoku_grid->suduku_grid[n / 9][n % 9] = i;
				BackTrace1(sudoku_grid, n + 1);
				if (sudoku_grid->solution_sign == 1) 
				{
					sudoku_grid->solutions++;
				}
				sudoku_grid->suduku_grid[n / 9][n % 9] = 0;
			}
		}
	}
}

void Sudoku::Solution(SudokuGrids* sudoku_grid, int grid_num)
{
	BackTrace(sudoku_grid, 0);
	sudoku_grid->print();
	for (int i = 0; i < grid_num - 1; i++) {
		sudoku_grid = sudoku_grid->next_grid;
		BackTrace(sudoku_grid, 0);
		sudoku_grid->print();
	}
}

void GenUniqeBaseGrid(int grid_num)
{

}