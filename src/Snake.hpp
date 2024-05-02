#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <SDL.h>

#include <vector>
#include <string>

#include "Types.hpp"

namespace Snake
{
    enum class MoveDirection
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct SnakeSegment
    {
        i32 x, y;
    };

    class Game
    {
    public:
        Game(const std::string& name, i32 width, i32 height);
        ~Game();
        void run();
    private:
        void reset();
        void place_fruit();
        void update();
        void render();
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        std::vector<SnakeSegment> m_snake;
        SnakeSegment m_fruit;
        MoveDirection m_dir;
        bool m_game_over;
        bool m_win;

		const std::string m_win_name;
		const i32 m_win_width;
		const i32 m_win_height;
		const i32 m_cell_size = 20;
        const i32 m_win_length = 50;
    };
}

#endif