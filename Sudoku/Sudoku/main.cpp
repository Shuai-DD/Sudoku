#include"Sudoku.h"
#include <iostream>
using namespace std;
int main()
{
	Sudoku s;
	int c = 0;//终盘数量
	char s_path[100] = { ' ' };//路径
	bool s_sign = 0;
	int n = 0;//游戏数量
	int m = 0;//游戏难度1-3
	char r[10] = { ' ' };
	bool r_sign = 0;
	int r_lowwer = 20;//挖空范围下限
	int r_upper = 55;//上限
	bool u = 0;//是否唯一解
	char buf[200] = { ' ' };
	cin.get(buf, 200);
	for (int i = 0; i < 200; i++)
	{
		if (buf[i] == ' ')continue;
		if (buf[i] == '-')
		{
			switch (buf[i + 1])
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
				s_sign = 1;
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
								s_path[l] = buf[k];
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
	char game_txt[16] = "game.txt";
	char solution_txt[16] = "solution.txt";
	char sudoku_txt[16] = "sudoku.txt";
	if (c)
	{
		s.GenSolutionGrid(c);
		s.GridWritter(solution_txt);
	}
	else if (s_sign)
	{
		s.GridReader(s_path);
		s.Solution();
		s.GridWritter(sudoku_txt);
	}
	else if (n)
	{
		if (m)
		{
			switch (m)
			{
			case 1:
				s.GenSolutionGrid(n);
				s.GenBaseGrid(10, 20);
				s.GridWritter(game_txt);
				break;
			case 2:
				s.GenSolutionGrid(n);
				s.GenBaseGrid(20, 40);
				s.GridWritter(game_txt);
				break;
			case 3:
				s.GenSolutionGrid(n);
				s.GenBaseGrid(40, 55);
				s.GridWritter(game_txt);
				break;
			}
		}
		else if (r_sign)
		{
			s.GenSolutionGrid(n);
			s.GenBaseGrid(r_lowwer, r_upper);
			s.GridWritter(game_txt);
		}
		else if (u)
		{
			s.GenUniqeBaseGrid(n);
			s.GridWritter(game_txt);
		}
		else
		{
			s.GenSolutionGrid(n);
			s.GenBaseGrid(30, 40);
			s.GridWritter(game_txt);
		}
	}
}