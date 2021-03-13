#pragma once
#include "Frame.h"
#include "Minesweeper.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void Position(Text *t, float width, float height)
{
	t->setOrigin(t->getGlobalBounds().left + t->getGlobalBounds().width / 2.0f, t->getGlobalBounds().top + t->getGlobalBounds().height / 2.0f);
	t->setPosition(width, height);
}

void Frame::gameRun(RenderWindow & win, int n, int m )
{
	Minesweeper M(n, m);
	Minesweeper SM(n);
	win.clear(Color(145, 163, 176, 255));
	setFrame(win, n);
	SM.game(win, M);
}
void Frame::setFrame(RenderWindow & win, int n)
{
	Vector2u newSize(n * 32, n * 32);
	FloatRect view(0, 0, n * 32, n * 32);
	win.setSize(newSize);
	win.setView(View(view));
}
void Frame::setFrame(RenderWindow & win, float n, float m)
{
	Vector2u newSize(n * 32, m * 32);
	FloatRect view(0, 0, n * 32, m * 32);
	win.setSize(newSize);
	win.setView(View(view));
}
int Frame :: run(RenderWindow & win,int frames)
{
	Event e;
	Font font;
	font.loadFromFile("helvetica.ttf");
	while(frames>0)
	{ 
		switch (frames)
		{
		case 5:
			{
				setFrame(win, 28.125, 18.75);
	
				Text tm("MINESWEEPER", font, 60U);
				Text tp("PLAY", font, 45U);
				Text tq("QUIT", font, 45U);

				tm.setFillColor(sf::Color(0, 0, 0, 255));
				Position(&tm, 450, 100);
				Position(&tp, 450, 300);
				Position(&tq, 450, 375);

				win.clear(Color(145, 163, 176, 255));
				win.draw(tp);
				win.draw(tq);
				win.draw(tm);
				win.display();

				while (win.isOpen())
				{
					while (win.pollEvent(e))
					{

						if (e.type == Event::Closed)
							win.close();

						if (e.type == Event::MouseButtonPressed)
						{
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								if (tp.getGlobalBounds().contains((Vector2f)Mouse::getPosition(win)))
								{
									frames--;

								}
								else if (tq.getGlobalBounds().contains((Vector2f)Mouse::getPosition(win)))
									return -1;
							}

						}
					}
					if (frames != 5)
						break;

				}
				break;
			}
		case 4:
			{
				win.clear(Color(145, 163, 176, 255));
				
				Text td("CHOOSE THE DIFFICULTY:", font, 45U);
				Text te("EASY", font, 35U);
				Text tme("MEDIUM", font, 35U);
				Text th("HARD", font, 35U);

				td.setFillColor(Color(0, 0, 0, 255));
				Position(&td, 450, 100);
				Position(&te, 450, 300);
				Position(&tme, 450, 370);
				Position(&th, 450, 430);

				win.clear(Color(145, 163, 176, 255));
				win.draw(td);
				win.draw(te);
				win.draw(tme);
				win.draw(th);
				win.display();

				while (win.isOpen())
				{
					while (win.pollEvent(e))
					{

						if (e.type == Event::Closed)
							win.close();

						if (e.type == Event::MouseButtonPressed)
						{
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								if (te.getGlobalBounds().contains((Vector2f)Mouse::getPosition(win)))
									frames--;
								else if (tme.getGlobalBounds().contains((Vector2f)Mouse::getPosition(win)))
									frames -= 2;
								else if (th.getGlobalBounds().contains((Vector2f)Mouse::getPosition(win)))
									frames -= 3;

							}

						}
					}
					if (frames != 4)
						break;

				}
				break;
			}

		case 3:
			{
				gameRun(win, 9, 10);
				frames = 5;
				break;
			}
		case 2:
			{
				gameRun(win, 16, 40);
				frames = 5;
				break;
			}
		case 1:
			{
				gameRun(win, 24, 99);
				frames = 5;
				break;
			}
		
		}
	}
	return -1;
}