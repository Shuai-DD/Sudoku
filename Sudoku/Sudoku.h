#pragma once
#include<string>
//���Դ���������
struct SudokuGrids
{
	int solutions = 0;
	bool solution_sign = 0;//�Ƿ��н�
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
	int grid_num_;//������Ŀ
public:
	void RandomLine(int line[]);
	bool JudgeLegitimacy(SudokuGrids* sudoku_grid, int row, int col, int val);//����ʱ����жϸ���
	bool JudgeLegitimacy1(SudokuGrids* sudoku_grid, int row, int col, int val);//���ʱ��������ж�
	bool FillNum(SudokuGrids* sudoku_grid, int row, int col);
	void GenSolutionGrid(int grid_num);
	void GenBaseGrid(int lower_limit, int upper_limit);//��ȥ��������ֵ��ʹ���Ϊ����
	void GridWritter(char* writter_path);//������ɵ�����/���
	void GridReader(char* reader_path);//��ָ��·����ȡ��Ŀ
	void BackTrace(SudokuGrids* sudoku_grid, int n);//���ݷ������� n = row * 9 + col��ֻ�ҳ�һ����
	void BackTrace1(SudokuGrids* sudoku_grid, int n);//�ҳ����н�ĸ���
	void Solution();
	void GenUniqeBaseGrid(int grid_num);
};