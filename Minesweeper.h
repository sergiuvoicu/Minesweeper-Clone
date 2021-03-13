#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Minesweeper {
	
	int rows;
	int mines;
	int **matrix;
	void alloc();
	void clearField(int, int, int **);
public:
	Minesweeper( int, int=0, int** = NULL);
	~Minesweeper();
	Minesweeper &operator=(const Minesweeper &);
	Minesweeper(const Minesweeper &);
	int game(sf::RenderWindow &, Minesweeper &);
	int getMines(int,int);
	void init();
	void prtMat(sf::RenderWindow &, Minesweeper &);

};
