#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

class Grid
{
public:
  Grid(int rows, int columns);

  [[nodiscard]] bool is_full() const;

  int rows() const
  {
    return m_rows;
  };

  int columns() const
  {
    return m_columns;
  }

  enum class Disc
  {
    RED,
    YELLOW,
    EMPTY
  };

  [[nodiscard]] Disc get_disc(int row, int column) const;

  const std::vector<std::vector<Disc>>& get_discs() const;

  bool drop_disc(int column, Disc disc);

  bool are_four_connected() const;

private:
  const int m_rows;
  const int m_columns;
  std::vector<std::vector<Disc>> m_discs;
};

#endif
