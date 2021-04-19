#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
	public:
		TEST_METHOD(TestMethod1)//Judge函数的正确例子1
		{
			Sudoku s;
			s.sudoku_grids_ = new SudokuGrids;
			s.FillNum(s.sudoku_grids_, 0, 0);
			int a = s.sudoku_grids_->suduku_grid[0][0];
			s.sudoku_grids_->suduku_grid[0][0] = 0;
			Assert::AreEqual(1,int(s.JudgeLegitimacy1(s.sudoku_grids_,0,0,a)));
		}

		TEST_METHOD(TestMethod2)//Judge函数的正确例子2
		{
			Sudoku s;
			s.sudoku_grids_ = new SudokuGrids;
			s.FillNum(s.sudoku_grids_, 0, 0);
			int a = s.sudoku_grids_->suduku_grid[8][8];
			s.sudoku_grids_->suduku_grid[8][8] = 0;
			Assert::AreEqual(1, int(s.JudgeLegitimacy1(s.sudoku_grids_, 8, 8, a)));
		}

		TEST_METHOD(TestMethod3)//Judge函数的错误例子1
		{
			Sudoku s;
			s.sudoku_grids_ = new SudokuGrids;
			s.FillNum(s.sudoku_grids_, 0, 0);
			int a = s.sudoku_grids_->suduku_grid[0][0] + 1;
			s.sudoku_grids_->suduku_grid[0][0] = 0;
			Assert::AreEqual(0, int(s.JudgeLegitimacy1(s.sudoku_grids_, 0, 0, a)));
		}

		TEST_METHOD(TestMethod4)//Judge函数的错误例子2
		{
			Sudoku s;
			s.sudoku_grids_ = new SudokuGrids;
			s.FillNum(s.sudoku_grids_, 0, 0);
			int a = s.sudoku_grids_->suduku_grid[8][8] + 1;
			s.sudoku_grids_->suduku_grid[8][8] = 0;
			Assert::AreEqual(0, int(s.JudgeLegitimacy1(s.sudoku_grids_, 8, 8, a)));
		}

		TEST_METHOD(TestMethod5)//FillNum函数
		{
			bool b = 1;
			Sudoku s;
			s.sudoku_grids_ = new SudokuGrids;
			s.FillNum(s.sudoku_grids_, 0, 0);
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					int a = s.sudoku_grids_->suduku_grid[i][j];
					s.sudoku_grids_->suduku_grid[i][j] = 0;
					if (!s.JudgeLegitimacy1(s.sudoku_grids_, i, j, a))b = 0;
				}
			}
			Assert::AreEqual(1, int(b));
		}

		//TEST_METHOD(TestMethod6)//Backtrace函数
		//{
		//	bool b = 1;
		//	Sudoku s;
		//	char path[100] = { "TestBackTrace.txt" };
		//	s.GridReader(path);
		//	s.BackTrace(s.sudoku_grids_, 0);
		//	Assert::AreEqual(1, int(b));
		//}

		TEST_METHOD(TestMethod6)//GenSolution函数
		{
			Sudoku s;
			int a = 0;
			//SudokuGrids* temp;
			s.GenSolutionGrid(20);
			for (int i = 1;;) {
				if (s.sudoku_grids_->next_grid != NULL) {
					i++;
					s.sudoku_grids_ = s.sudoku_grids_->next_grid;
				}
				else {
					a = i;
					break;
				}
			}
			Assert::AreEqual(20, a);
		}
		TEST_METHOD(TestMethod7)//GenSolution函数
		{
			Sudoku s;
			int a = 0;
			//SudokuGrids* temp;
			s.GenSolutionGrid(100000);
			for (int i = 1;;) {
				if (s.sudoku_grids_->next_grid != NULL) {
					i++;
					s.sudoku_grids_ = s.sudoku_grids_->next_grid;
				}
				else {
					a = i;
					break;
				}
			}
			Assert::AreEqual(100000, a);
		}

		TEST_METHOD(TestMethod8)//GenBase函数
		{
			Sudoku s;
			int a = 0;
			//SudokuGrids* temp;
			s.GenSolutionGrid(20);
			s.GenBaseGrid(20,50);
			for (int i = 1;;) {
				if (s.sudoku_grids_->next_grid != NULL) {
					i++;
					s.sudoku_grids_ = s.sudoku_grids_->next_grid;
				}
				else {
					a = i;
					break;
				}
			}
			Assert::AreEqual(20, a);
		}
	};
}
