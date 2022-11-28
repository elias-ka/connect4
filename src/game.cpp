#include <iostream>

#include "game.hpp"

#include <SDL.h>

Game::Game(const int grid_rows, const int grid_columns)
    : m_grid(grid_rows, grid_columns)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << '\n';
  }

  const int width = m_grid.columns() * 100;
  const int height = m_grid.rows() * 100;

  m_window = SDL_CreateWindow("Connect 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (!m_window) {
    std::cerr << "Could not create window, SDL_Error: " << SDL_GetError() << '\n';
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
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
    using enum Game::State;
    poll_events();
    update_window_title();
    draw_grid();
    if (m_game_state == PLAYING) {
      if (m_grid.are_four_connected(Disc::YELLOW)) {
        m_game_state = YELLOW_WIN;
      } else if (m_grid.are_four_connected(Disc::RED)) {
        m_game_state = RED_WIN;
      } else if (m_grid.is_full()) {
        m_game_state = DRAW;
      }
    }
  }
}

void Game::draw_grid() const
{
  SDL_SetRenderDrawColor(m_renderer, 1, 82, 187, 255);
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
        using enum Disc;
        case RED: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color {219, 31, 4, 255});
          break;
        }
        case YELLOW: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color {245, 214, 2, 255});
          break;
        }
        case EMPTY: {
          draw_disc(m_renderer, x, y, disc_width, disc_height, SDL_Color {2, 66, 163, 255});
          break;
        }
      }
    }
  }

  SDL_RenderPresent(m_renderer);
}

void Game::draw_disc(SDL_Renderer* renderer, const int x, const int y, const int w, const int h, const SDL_Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  const SDL_Rect rect {x, y, w, h};
  SDL_RenderFillRect(renderer, &rect);
}

void Game::poll_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      m_running = false;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
      const int column = event.button.x / 100;
      handle_turn(column);
    }

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_1:
        case SDLK_2:
        case SDLK_3:
        case SDLK_4:
        case SDLK_5:
        case SDLK_6:
        case SDLK_7: {
          handle_turn(event.key.keysym.sym - SDLK_1);
          break;
        }
        case SDLK_ESCAPE: {
          m_running = false;
          break;
        }
        default:
          break;
      }
    }
  }
}

void Game::update_window_title() const
{
  switch (m_game_state) {
    case State::PLAYING: {
      if (m_turn == Turn::YELLOW) {
        SDL_SetWindowTitle(m_window, "Connect 4 - Yellow's turn");
      } else {
        SDL_SetWindowTitle(m_window, "Connect 4 - Red's turn");
      }
      break;
    }
    case State::YELLOW_WIN: {
      SDL_SetWindowTitle(m_window, "Connect 4 - Yellow won!");
      break;
    }
    case State::RED_WIN: {
      SDL_SetWindowTitle(m_window, "Connect 4 - Red won!");
      break;
    }
    case State::DRAW: {
      SDL_SetWindowTitle(m_window, "Connect 4 - Draw!");
      break;
    }
  }
}

void Game::handle_turn(int column)
{
  if (m_game_state == State::PLAYING) {
    if (m_grid.drop_disc(column, m_turn == Turn::YELLOW ? Disc::YELLOW : Disc::RED)) {
      m_turn = m_turn == Turn::YELLOW ? Turn::RED : Turn::YELLOW;
    }
  }
}