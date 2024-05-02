#include "Snake.hpp"

i32 main(i32 argc, char** argv)
{
	Snake::Game game("Snake", 800, 600);
	game.run();

	return 0;
}