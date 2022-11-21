#include <cstdint>
#include <iostream>

#include "game.hpp"

#include <SDL.h>

Game::Game(const int grid_rows,
           const int grid_columns)
  : m_grid(grid_rows, grid_columns)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << '\n';
  }

  const int width = m_grid.columns() * 100;
  const int height = m_grid.rows() * 100;

  m_window = SDL_CreateWindow("Connect 4",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              0);

  if (!m_window) {
    std::cerr << "Could not create window, SDL_Error: " << SDL_GetError() << '\n';
  }

  m_renderer = SDL_CreateRenderer(m_window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
  if (!m_renderer) {
    std::cerr << "Could not create renderer, SDL_Error: " << SDL_GetError() << '\n';
  }
}

Game::~Game()
{
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Game::run()
{
  while (m_running) {
    draw_grid();
    poll_events();
  }
}

void Game::draw_grid() const
{
  SDL_SetRenderDrawColor(m_renderer, 10, 20, 30, 255);
  SDL_RenderClear(m_renderer);

  constexpr int padding = 2;
  constexpr int margin = 5;
  constexpr int disc_width = 100 - padding * margin;
  constexpr int disc_height = 100 - padding * margin;

  for (int row = 0; row < m_grid.rows(); ++row) {
    for (int column = 0; column < m_grid.columns(); ++column) {
      const int x = column * 100 + margin;
      const int y = row * 100 + margin;

      switch (m_grid.get_disc(row, column)) {
        case Grid::Disc::RED: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color{255, 0, 0, 255});
          break;
        }
        case Grid::Disc::YELLOW: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color{255, 255, 0, 255});
          break;
        }
        case Grid::Disc::EMPTY: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color{40, 50, 60, 255});
          break;
        }
      }
    }
  }

  SDL_RenderPresent(m_renderer);
}

void Game::draw_disc(SDL_Renderer* renderer,
                     const int x,
                     const int y,
                     const int w,
                     const int h,
                     const SDL_Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  const SDL_Rect rect{x, y, w, h};
  SDL_RenderFillRect(renderer, &rect);
}

void Game::poll_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        m_running = false;
        break;

      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_1:
          case SDLK_2:
          case SDLK_3:
          case SDLK_4:
          case SDLK_5:
          case SDLK_6:
          case SDLK_7: {
            m_grid.drop_disc(event.key.keysym.sym - SDLK_1, Grid::Disc::YELLOW);
            break;
          }
          case SDLK_ESCAPE: {
            m_running = false;
            break;
          }
          default:
            break;
        }
        break;
      }

      case SDL_MOUSEBUTTONDOWN:
        const int column = event.button.x / 100;
        m_grid.drop_disc(column, Grid::Disc::YELLOW);
        break;
    }
  }
}