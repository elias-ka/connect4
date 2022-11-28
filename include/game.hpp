#ifndef CONNECT4_GAME_HPP
#define CONNECT4_GAME_HPP

#include <SDL.h>

#include "grid.hpp"

class Game
{
public:
  Game(int grid_rows, int grid_columns);
  ~Game();

  void run();

  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

private:
  static void draw_disc(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color);
  void handle_turn(int column);
  void draw_grid() const;
  void poll_events();
  void update_window_title() const;

  enum class Turn
  {
    YELLOW,
    RED,
  };

  enum class State
  {
    PLAYING,
    YELLOW_WIN,
    RED_WIN,
    DRAW
  };

  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  Grid m_grid;

  Turn m_turn {Turn::YELLOW};
  State m_game_state {State::PLAYING};
  bool m_running {true};
};

#endif  // CONNECT4_GAME_HPP
