#include "SDL.h"

#include <ctime>
#include "Game.h"

constexpr int SCREEN_WIDTH = 700;
constexpr int SCREEN_HEIGHT = 900;

int main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Window window{ "GEOA Project Demo", SCREEN_WIDTH , SCREEN_HEIGHT };
	Game pGame{ window };
	pGame.Run();

	return 0;
}

