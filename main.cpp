#include"Sudoku.h"
#include <iostream>
#include<stdio.h>
using namespace std;
int main()
{
	int c = 1;//��������
	char s1[100] = { ' ' };//·��
	int n = 1;//��Ϸ����
	int m = 2;//��Ϸ�Ѷ�1-3
	char r[10] = { ' ' };
	bool r_sign = 0;
	int r_lowwer = 20;//�ڿշ�Χ����
	int r_upper = 55;//����
	bool u = 0;//�Ƿ�Ψһ��
	char buf[200] = { ' ' };
	cin.get(buf, 200);
	cout << "buf:";
	for (int i = 0; i < 200; i++)cout << buf[i];
	for (int i = 0; i < 200; i++)
	{
		if (buf[i] == ' ')continue;
		if (buf[i] == '-')
		{
			switch (buf[i+1])
			{
			case'c':
				c = 0;
				for (int j = i + 2;; j++)
				{
					if (buf[j] == ' ')continue;
					else if (buf[j] >= '0' && buf[j] <= '9')
					{
						int num = buf[j] - '0';
						c = c * 10 + num;
					}
					else
					{
						i = j - 1;
						break;
					}
				}
				break;
			case'n':
				n = 0;
				for (int j = i + 2;; j++)
				{
					if (buf[j] == ' ')continue;
					else if (buf[j] >= '0' && buf[j] <= '9')
					{
						int num = buf[j] - '0';
						n = n * 10 + num;
					}
					else
					{
						i = j - 1;
						break;
					}
				}
				break;
			case'm':
				m = 0;
				for (int j = i + 2;; j++)
				{
					if (buf[j] == ' ')continue;
					else if (buf[j] >= '0' && buf[j] <= '9')
					{
						int num = buf[j] - '0';
						m = m * 10 + num;
					}
					else
					{
						i = j - 1;
						break;
					}
				}
				break;
			case 'r':
				r_sign = 1;
				if (buf[i + 2] == ' ' && buf[i + 3] >= '0' && buf[i + 3] <= '9')
				{
					int k = 0;
					for (int j = i + 3;; j++)
					{
						if (buf[j] != ' ')
						{
							r[k] = buf[j];
							k++;
						}
						else
						{
							i = j - 1;
							break;
						}
					}
				}
				else 
				break;
			case'u':
				u = 1;
				break;
			case 's':
			{
				for (int j = i + 2;; j++)
				{
					if (buf[j] == ' ')continue;
					if (buf[j] == '"')
					{
						int l = 0;
						for (int k = j + 1;; k++)
						{
							if (buf[k] != '"')
							{
								s1[l] = buf[k];
								l++;
							}
							else
							{
								i = j = k;
								break;
							}
						}
						break;
					}
				}
			}
				break;
			default:
				break;
			}
		}
	}
	if (r_sign)
	{
		r_lowwer = r_upper = 0;
		for (int i = 0; i < 10; i++)
		{
			if (r[i] >= '0' && r[i] <= '9')
			{
				int num1 = r[i] - '0';
				r_lowwer = r_lowwer * 10 + num1;
			}
			if (r[i] == '-')
			{
				for (int j = i + 1;; j++)
				{
					if (r[j] >= '0' && r[j] <= '9')
					{
						int num2 = r[j] - '0';
						r_upper = r_upper * 10 + num2;
					}
					else
					{
						i = j;
						break;
					}
				}
				break;
			}
		}
	}
	cout << endl << "r:";
	for (int i = 0; i < 5; i++)cout << r[i];
	cout << endl << "r_low:" << r_lowwer << "; r_up:" << r_upper;
	cout << endl;
	cout << "s1:";
	for (int i = 0; i < 100; i++)cout << s1[i];
	cout << endl;
	cout << "c:" << c << endl;
	cout << "n:" << n << endl;
	cout << "m:" << m << endl;
	cout << "u:" << u << endl;

			//Sudoku sudoku1;
			//sudoku1.GenSolutionGrid(2);
			//sudoku1.sudoku_grids_->print();
			//sudoku1.sudoku_grids_->next_grid->print();
			//sudoku1.GenBaseGrid(6,7);
			//sudoku1.GridWritter();
			//sudoku1.GridReader(2);
			////sudoku1.BackTrace(sudoku1.sudoku_grids_, 0);
			////sudoku1.BackTrace(sudoku1.sudoku_grids_->next_grid, 0);
			//sudoku1.Solution(sudoku1.sudoku_grids_, 2);
			//cout << endl << sudoku1.sudoku_grids_->solutions << endl << sudoku1.sudoku_grids_->next_grid->solutions << endl;
			////s.sudoku_grids_->print();
			////s.sudoku_grids_->next_grid->print();
}