#define _CRT_SECURE_NO_WARNINGS
#include"Sudoku.h"
#include<time.h>
#include<cstdlib>
#include<iostream>
#include<fstream>
// #include<stdio.h>
using namespace std;

SudokuGrids::SudokuGrids() {
	this->next_grid = NULL;
}

void SudokuGrids::print() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << this->suduku_grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Sudoku::RandomLine(int line[]) {
	int temp_num, random_num;
	for (int i = 0; i < 9; i++) {
		random_num = rand() % 9;
		temp_num = line[random_num];
		line[random_num] = line[i];
		line[i] = temp_num;
	}
}

bool Sudoku::JudgeLegitimacy(SudokuGrids* sudoku_grid,
	int row, int col, int val) {
	for (int i = 0; i < col; i++) {
		if (val == sudoku_grid->suduku_grid[row][i]) {
			return false;
		}
	}
	for (int i = 0; i < row; i++) {
		if (val == sudoku_grid->suduku_grid[i][col]) {
			return false;
		}
	}
	int count = col % 3 + row % 3 * 3;
	while (count--) {
		if (val == sudoku_grid->suduku_grid[row / 3 * 3
			+ count / 3][col / 3 * 3 + count % 3]) {
			return false;
		}
	}
	return true;
}

bool Sudoku::JudgeLegitimacy1(SudokuGrids* sudoku_grid,
	int row, int col, int val) {
	for (int i = 0; i < 9; i++) {
		if (val == sudoku_grid->suduku_grid[row][i]) {
			return false;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (val == sudoku_grid->suduku_grid[i][col]) {
			return false;
		}
	}
	int count = col % 3 + row % 3 * 3;
	while (count--) {
		if (val == sudoku_grid->suduku_grid[row / 3 * 3
			+ count / 3][col / 3 * 3 + count % 3]) {
			return false;
		}
	}
	return true;
}

bool Sudoku::FillNum(SudokuGrids* sudoku_grid, int row, int col) {
	int new_col, new_row;
	if (row > 8) {
		return true;
	}
	int random_num = rand() % 9 + 1;
	for (int i = 9; i > 0; i--) {
		int filling_num = (random_num + i) % 9 + 1;
		if (JudgeLegitimacy(sudoku_grid, row, col, filling_num)) {
			sudoku_grid->suduku_grid[row][col] = filling_num;
			if (col == 8) {
				new_row = row + 1;
				new_col = 0;
			} else {
				new_row = row;
				new_col = col + 1;
			}
			if (FillNum(sudoku_grid, new_row, new_col)) {
				return true;
			}
		}
	}
	return false;
}

void Sudoku::GenSolutionGrid(int grid_num) {
	grid_num_ = grid_num;
/*于此处产生随机数种子*/
	srand(time(NULL));
	SudokuGrids* temp_grid_s = new SudokuGrids;
	sudoku_grids_ = temp_grid_s;
	RandomLine(first_line_);
	for (int j = 0; j < 9; j++) {
		temp_grid_s->suduku_grid[0][j] = first_line_[j];
	}
	FillNum(temp_grid_s, 1, 0);
	SudokuGrids* next_grid;
	for (int i = 0; i < grid_num_-1; i++) {
		next_grid = new SudokuGrids;
		temp_grid_s->next_grid = next_grid;
		RandomLine(first_line_);
		for (int j = 0; j < 9; j++) {
			next_grid->suduku_grid[0][j] = first_line_[j];
		}
		FillNum(next_grid, 1, 0);
		temp_grid_s = next_grid;
	}
	temp_grid_s = sudoku_grids_;
}

void Sudoku::GenBaseGrid(int lower_limit, int upper_limit) {
	int blank_num, blank_point;
	int test = 0;
	SudokuGrids* temp_grid_g = sudoku_grids_;
	while (temp_grid_g->next_grid) {
		temp_grid_g = temp_grid_g->next_grid;
		test++;
	}
	temp_grid_g = sudoku_grids_;
	for (int i = 0; i < grid_num_; i++) {
		blank_num = lower_limit + rand() % (upper_limit - lower_limit);
		int blank_num_oneline = blank_num / 9;
		for (int j = 0; j < 9; j++) {
			for (int m = 0; m < blank_num_oneline; m++) {
				blank_point = rand() % 9;
				if (temp_grid_g->suduku_grid[j][blank_point] == 0) {
					m--;
				} else {
					temp_grid_g->suduku_grid[j][blank_point] = 0;
				}
			}
		}
		blank_num_oneline = blank_num % 9;
		for (int m = 0; m < blank_num_oneline; m++) {
			int blank_point = rand() % 9;
			if (temp_grid_g->suduku_grid[m][blank_point] == 0) {
				m--;
			} else {
				temp_grid_g->suduku_grid[m][blank_point] = 0;
			}
		}
		temp_grid_g = temp_grid_g->next_grid;
	}
}

void Sudoku::GridWritter(char* writter_path) {
	ofstream writter(writter_path);
	SudokuGrids* temp_grid_w = sudoku_grids_;
	if (writter.is_open()) {
		for (int i = 0; i < grid_num_; i++) {
			for (int j = 0; j < 9; j++) {
				for (int k = 0; k < 9; k++) {
					writter << temp_grid_w->suduku_grid[j][k] << " ";
				}
				writter << endl;
			}
			writter << endl;
			temp_grid_w = temp_grid_w->next_grid;
		}
	}
}

void Sudoku::GridReader(char* reader_path) {
	char all_grids[170000];  // 用数组存整个txt文档
	int length = 0;  // 数组长度
	FILE* reader;
	fopen_s(&reader, reader_path, "r");
	if (reader == NULL)return;
	while (1) {
		char c;
		c = fgetc(reader);
		if (c == EOF) break;
		all_grids[length] = c;
		length++;
	}
	fclose(reader);
	// 读取文件
	SudokuGrids* temp_grid_r = new SudokuGrids;
	SudokuGrids* new_grid = new SudokuGrids;
	grid_num_ = 0;
	int tail = 0;  // 数组下标
	int n = 0;

	while (tail < length) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				temp_grid_r->suduku_grid[i][j] = all_grids[tail] - '0';
				tail += 2;
			}
			tail++;
		}
		tail++;
		if (grid_num_ == 0) {
			temp_grid_r->next_grid = new_grid;
			sudoku_grids_ = temp_grid_r;
			temp_grid_r = temp_grid_r->next_grid;
			grid_num_++;
			continue;
		}
		new_grid = new SudokuGrids;
		temp_grid_r->next_grid = new_grid;
		temp_grid_r = temp_grid_r->next_grid;
		grid_num_++;
	}
}

void Sudoku::BackTrace(SudokuGrids* sudoku_grid, int n) {
	if (n == 81) {
		sudoku_grid->solution_sign = 1;
		return;
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] != 0) {
		BackTrace(sudoku_grid, n + 1);
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] == 0) {
		for (int i = 1; i <= 9; i++) {
			if (JudgeLegitimacy1(sudoku_grid, n / 9, n % 9, i)) {
				sudoku_grid->suduku_grid[n / 9][n % 9] = i;
				BackTrace(sudoku_grid, n + 1);
				if (sudoku_grid->solution_sign == 1) {
					return;
				}
				sudoku_grid->suduku_grid[n / 9][n % 9] = 0;
			}
		}
	}
}

void Sudoku::BackTrace1(SudokuGrids* sudoku_grid, int n) {
	if (n == 81) {
		sudoku_grid->solutions++;
		sudoku_grid->solution_sign = 1;
		return;
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] != 0) {
		BackTrace1(sudoku_grid, n + 1);
	}
	if (sudoku_grid->suduku_grid[n / 9][n % 9] == 0) {
		for (int i = 1; i <= 9; i++) {
			if (JudgeLegitimacy1(sudoku_grid, n / 9, n % 9, i)) {
				sudoku_grid->suduku_grid[n / 9][n % 9] = i;
				BackTrace1(sudoku_grid, n + 1);
				sudoku_grid->suduku_grid[n / 9][n % 9] = 0;
			}
		}
	}
}

void Sudoku::Solution() {
	BackTrace(sudoku_grids_, 0);
	SudokuGrids* temp_grid_s = sudoku_grids_;
	for (int i = 0; i < grid_num_ - 1; i++) {
		temp_grid_s = temp_grid_s->next_grid;
		BackTrace(temp_grid_s, 0);
	}
}

void Sudoku::GenUniqeBaseGrid(int grid_num) {
	int gened_grid_num = 0;
	SudokuGrids* temp_grid_b = new SudokuGrids;
	SudokuGrids* result = new SudokuGrids;
	SudokuGrids* new_grid = new SudokuGrids;
	while (gened_grid_num != grid_num) {
		GenSolutionGrid(1);
		GenBaseGrid(20, 21);
		BackTrace1(sudoku_grids_, 0);
		if (sudoku_grids_->solutions > 1 || sudoku_grids_->solution_sign == 0) {
			continue;
		}
		if (gened_grid_num == 0) {
			temp_grid_b = sudoku_grids_;
			temp_grid_b->next_grid = new_grid;
			result = temp_grid_b;
			gened_grid_num++;
			continue;
		}
		new_grid = sudoku_grids_;
		temp_grid_b->next_grid = new_grid;
		temp_grid_b = temp_grid_b->next_grid;
		new_grid = new SudokuGrids;
		gened_grid_num++;
	}
	grid_num_ = grid_num;
	sudoku_grids_ = result;
}
