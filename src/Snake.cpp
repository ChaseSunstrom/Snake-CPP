#include "Snake.hpp"

namespace Snake
{
    Game::Game(const std::string& name, i32 width, i32 height) :
        m_win_name(name), m_win_width(width), m_win_height(height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        reset();
    }

    Game::~Game()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Game::run()
    {
        SDL_Event event;
        bool running = true;

        while (running && !m_game_over)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:    if (m_dir != MoveDirection::DOWN) m_dir = MoveDirection::UP; break;
                    case SDLK_DOWN:  if (m_dir != MoveDirection::UP) m_dir = MoveDirection::DOWN; break;
                    case SDLK_LEFT:  if (m_dir != MoveDirection::RIGHT) m_dir = MoveDirection::LEFT; break;
                    case SDLK_RIGHT: if (m_dir != MoveDirection::LEFT) m_dir = MoveDirection::RIGHT; break;
                    }
                }
            }

            update();
            render();
            SDL_Delay(100); // Update the game state every 100 ms
        }
    }

    void Game::reset()
    {
        m_snake = { {m_win_width / 2, m_win_height / 2}, {m_win_width / 2, m_win_height / 2 - m_cell_size} };
        m_dir = MoveDirection::NONE;
        m_game_over = false;
        m_win = false;
        place_fruit();
    }

    void Game::place_fruit()
    {
        i32 nx = rand() % (m_win_width / m_cell_size);
        i32 ny = rand() % (m_win_height / m_cell_size);
        m_fruit = { nx * m_cell_size, ny * m_cell_size };
    }

    void Game::update()
    {
        if (m_dir == MoveDirection::NONE)
            return;

        // Move the snake body
        for (i32 i = m_snake.size() - 1; i > 0; --i)
        {
            m_snake[i] = m_snake[i - 1];
        }

        // Change the head position based on the current direction
        switch (m_dir)
        {
        case MoveDirection::UP: m_snake[0].y -= m_cell_size; break;
        case MoveDirection::DOWN: m_snake[0].y += m_cell_size; break;
        case MoveDirection::LEFT: m_snake[0].x -= m_cell_size; break;
        case MoveDirection::RIGHT: m_snake[0].x += m_cell_size; break;
        }

        // Check fruit collision
        if (m_snake[0].x == m_fruit.x && m_snake[0].y == m_fruit.y)
        {
            m_snake.push_back({ m_snake.back().x, m_snake.back().y });
            place_fruit();
            if (m_snake.size() >= m_win_length) {
                m_win = true;
                m_game_over = true; // Optional: you could let the game continue or stop here.
            }
        }

        // Check wall collision
        if (m_snake[0].x < 0 || m_snake[0].x >= m_win_width || m_snake[0].y < 0 || m_snake[0].y >= m_win_height)
        {
            m_game_over = true;
        }

        // Check self collision
        for (i32 i = 1; i < m_snake.size(); ++i)
        {
            if (m_snake[0].x == m_snake[i].x && m_snake[0].y == m_snake[i].y)
            {
                m_game_over = true;
            }
        }
    }

    void Game::render()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(m_renderer);

        // Render fruit
        SDL_Rect fruit_rect = { m_fruit.x, m_fruit.y, m_cell_size, m_cell_size };
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // red
        SDL_RenderFillRect(m_renderer, &fruit_rect);

        // Render snake
        for (auto& segment : m_snake)
        {
            SDL_Rect rect = { segment.x, segment.y, m_cell_size, m_cell_size };
            SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255); // green
            SDL_RenderFillRect(m_renderer, &rect);
        }

        SDL_RenderPresent(m_renderer);

        if (m_game_over)
        {
            if (m_win) 
            {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You Win!", "Congratulations! You reached the target length.", m_window);
            }
            else 
            {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You have lost. Try again!", m_window);
            }
            SDL_Quit();
            exit(0);
        }
    }
}