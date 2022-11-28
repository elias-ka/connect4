#ifndef CONNECT4_GRID_HPP
#define CONNECT4_GRID_HPP

#include <vector>

enum class Disc
{
  RED,
  YELLOW,
  EMPTY
};

class Grid
{
public:
  Grid(int rows, int columns)
      : m_rows(rows)
      , m_columns(columns)
      , m_discs(rows, std::vector(columns, Disc::EMPTY))
  {}

  [[nodiscard]] bool is_full() const;

  [[nodiscard]] int rows() const
  {
    return m_rows;
  };

  [[nodiscard]] int columns() const
  {
    return m_columns;
  }

  [[nodiscard]] Disc get_disc(int row, int column) const;

  bool drop_disc(int col, Disc disc);

  [[nodiscard]] bool are_four_connected(Disc disc) const;

private:
  const int m_rows;
  const int m_columns;
  std::vector<std::vector<Disc>> m_discs;
};

#endif  // CONNECT4_GRID_HPP
