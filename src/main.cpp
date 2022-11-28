#include "game.hpp"

int main(int argc, char* argv[])
{
  constexpr int grid_rows = 6;
  constexpr int grid_columns = 7;

  Game game {grid_rows, grid_columns};
  game.run();

  return 0;
}
