#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "Frame.h"
using namespace sf;


int main()
{
	RenderWindow window(VideoMode(900, 600), "Minesweeper Clone");

	Frame pq;
	pq.run(window,5);
	

	return 0;
}
