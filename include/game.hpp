#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

#include "grid.hpp"

class Game
{
public:
  Game(int grid_rows, int grid_columns);
  ~Game();

  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  void run();

  void draw_grid() const;

  void poll_events();

private:
  static void draw_disc(SDL_Renderer* renderer,
                        int x,
                        int y,
                        int w,
                        int h,
                        SDL_Color color);

  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  Grid m_grid;
  bool m_running{true};
};

#endif
