#include "Minesweeper.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;
Minesweeper::Minesweeper(int n, int m, int** mat) :rows(n + 2), mines(m) {


	alloc();
	for (int i = 1; i < rows - 1; i++)
		for (int j = 1; j < rows - 1; j++)
			matrix[i][j] = 10;
	for (int i = 0; i < rows; i++)
	{
		matrix[0][i] = 999;
		matrix[rows - 1][i] = 999;
	}
	for (int i = 1; i < rows - 1; i++)
	{
		matrix[i][0] = 999;
		matrix[i][rows - 1] = 999;
	}

}
void Minesweeper::alloc()
{
	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new int[rows];
}
int Minesweeper::getMines(int i, int j)
{
			int counter = 0;
			if (matrix[i - 1][j] == 9) counter++;
			if (matrix[i - 1][j - 1] == 9) counter++;
			if (matrix[i - 1][j + 1] == 9) counter++;
			if (matrix[i][j - 1] == 9) counter++;
			if (matrix[i][j + 1] == 9) counter++;
			if (matrix[i + 1][j - 1] == 9) counter++;
			if (matrix[i + 1][j] == 9) counter++;
			if (matrix[i + 1][j + 1] == 9) counter++;
			return counter;
}

void Minesweeper::init()
{


		srand(time(NULL));
		for (int i = 0; i < mines; i++)
		{
			int r1 = rand() % (rows - 2) + 1;
			int r2 = rand() % (rows - 2) + 1;
			while (matrix[r1][r2] == 9|| 
			(matrix[r1][r2]==0 || 
			matrix[r1+1][r2+1]==0 ||
			matrix[r1+1][r2]==0||
			matrix[r1+1][r2-1]==0||
			matrix[r1][r2+1]==0||
			matrix[r1][r2-1]==0||
			matrix[r1-1][r2+1]==0||
			matrix[r1-1][r2]==0||
			matrix[r1-1][r2-1]==0))
			{
				r1 = rand() % (rows - 2) + 1;
				r2 = rand() % (rows - 2) + 1;
			}
			matrix[r1][r2] = 9;
		}

		for (int i = 1; i < rows - 1; i++)
			for (int j = 1; j < rows - 1; j++)
			{
				int counter = 0;
				if (matrix[i][j] == 9) continue;
				if (matrix[i - 1][j] == 9) counter++;
				if (matrix[i - 1][j - 1] == 9) counter++;
				if (matrix[i - 1][j + 1] == 9) counter++;
				if (matrix[i][j - 1] == 9) counter++;
				if (matrix[i][j + 1] == 9) counter++;
				if (matrix[i + 1][j - 1] == 9) counter++;
				if (matrix[i + 1][j] == 9) counter++;
				if (matrix[i + 1][j + 1] == 9) counter++;
				matrix[i][j] = counter;
			}

}
Minesweeper & Minesweeper::operator=(const Minesweeper & x)
{
	if (this != &x)
	{
		rows = x.rows;
		mines = x.mines;

		alloc();

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < rows; j++)
				matrix[i][j] = x.matrix[i][j];
	}
	return *this;
}
Minesweeper::Minesweeper(const Minesweeper &x)
{
	*this = x;
}
Minesweeper::~Minesweeper()
{
	for (int i = 0; i < rows; i++)
		delete[]matrix[i];
	delete[]matrix;
}

void Minesweeper::clearField(int i, int j, int **y)
{
	
	if (i > 0 && i < rows - 1 && j>0 && j < rows - 1 && matrix[i][j] != y[i][j])
	{

		if (getMines(i, j) == 0 && y[i][j] == 0)
		{
			matrix[i][j] = y[i][j];
			clearField(i - 1, j - 1, y);
			clearField(i - 1, j, y);
			clearField(i - 1, j + 1, y);
			clearField(i, j - 1, y);
			clearField(i, j + 1, y);
			clearField(i + 1, j + 1, y);
			clearField(i + 1, j, y);
			clearField(i + 1, j - 1, y);
		}
		else 
			matrix[i][j] = y[i][j];
		
	}
	
}
void Minesweeper::prtMat(RenderWindow &win, Minesweeper &M)
{
	Texture T;
	T.loadFromFile("tiles.jpg");
	Sprite S(T);
	for (int i = 1; i < rows - 1; i++)
		for (int j = 1; j < rows - 1; j++)
		{
			if (matrix[i][j] == 9)
				matrix[i][j] = M.matrix[i][j];
			S.setTextureRect(IntRect(matrix[i][j] * 32, 0, 32, 32));
			S.setPosition((float)(i - 1) * 32, (float)(j - 1) * 32);
			win.draw(S);
		}
	win.display();

}
int Minesweeper::game(RenderWindow & win, Minesweeper & M)
{
	
	Event e;
	int flag(0);

	while (win.isOpen())
	{
		prtMat(win,M);
		while (win.pollEvent(e))
		{

			if (e.type == Event::Closed)
				win.close();

			if (e.type == Event::MouseButtonPressed)
			{

				Vector2i pos = Mouse::getPosition(win);
				
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (flag == 0)
					{
						M.matrix[pos.x / 32 + 1][pos.y / 32 + 1] = 0;
						M.init();
						flag = -1;
					}
					if (matrix[pos.x / 32 + 1][pos.y / 32 + 1] != 11)
					{
						if (M.matrix[pos.x / 32 + 1][pos.y / 32 + 1] == 0)
						{
							int i = pos.x / 32 + 1;
							int j = pos.y / 32 + 1;
							clearField(i, j, M.matrix);
						}
						matrix[pos.x / 32 + 1][pos.y / 32 + 1] = M.matrix[pos.x / 32 + 1][pos.y / 32 + 1];

						if (matrix[pos.x / 32 + 1][pos.y / 32 + 1] == 9)
						{
							for (int i = 1; i < rows - 1; i++)
								for (int j = 1; j < rows - 1; j++)
									matrix[i][j] = M.matrix[i][j];
							prtMat(win, M);
							cout << " YOU LOST. " << endl;
							std::this_thread::sleep_for(3s);
							return 0;

						}
					}
					
				}
				else if (Mouse::isButtonPressed(Mouse::Right))
				{
					if(matrix[pos.x / 32 + 1][pos.y / 32 + 1] == 11)
							matrix[pos.x / 32 + 1][pos.y / 32 + 1] = 10;
					else
						matrix[pos.x / 32 + 1][pos.y / 32 + 1] = 11;
				}

			}
		}
		int counter = 0;
		for (int i = 1; i < rows - 1; i++)
			for (int j = 1; j < rows - 1; j++)
				if (matrix[i][j] == 11 && M.matrix[i][j] == 9)
					counter++;

		if (counter == M.mines)
		{

			cout << " YOU WON. " << endl;
			for (int i = 1; i < rows-1; i++)
				for (int j = 1; j < rows-1; j++)
					if (matrix[i][j] != 11)
						matrix[i][j] = M.matrix[i][j];
			prtMat(win, M);
			std::this_thread::sleep_for(5s);
			return 1;
		}
	}
}
