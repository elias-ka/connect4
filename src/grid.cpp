#include <algorithm>
#include <ranges>

#include "Grid.hpp"

Grid::Grid(const int rows, const int columns)
  : m_rows(rows),
    m_columns(columns),
    m_discs(rows, std::vector(columns, Disc::EMPTY)) {}

bool Grid::is_full() const
{
  return std::ranges::none_of(m_discs | std::views::join,
                              [](const Disc disc)
                              {
                                return disc == Disc::EMPTY;
                              });
}

Grid::Disc Grid::get_disc(const int row, const int column) const
{
  return m_discs[row][column];
}

const std::vector<std::vector<Grid::Disc>>& Grid::get_discs() const
{
  return m_discs;
}

bool Grid::drop_disc(const int column, const Disc disc)
{
  if (column >= m_columns) {
    return false;
  }

  for (auto& row : m_discs | std::views::reverse) {
    if (row[column] == Disc::EMPTY) {
      row[column] = disc;
      break;
    }
  }

  return true;
}

bool Grid::are_four_connected() const
{
  for (int row = 0; row < m_rows; ++row) {
    for (int column = 0; column < m_columns; ++column) {
      const Disc disc = get_disc(row, column);
      if (disc == Disc::EMPTY) {
        continue;
      }

      // horizontal
      if (column + 3 < m_columns) {
        if (get_disc(row, column + 1) == disc
          && get_disc(row, column + 2) == disc
          && get_disc(row, column + 3) == disc) {
          return true;
        }
      }

      // vertical
      if (row + 3 < m_rows) {
        if (get_disc(row + 1, column) == disc
          && get_disc(row + 2, column) == disc
          && get_disc(row + 3, column) == disc) {
          return true;
        }
      }

      // diagonal
      if (row + 3 < m_rows && column + 3 < m_columns) {
        if (get_disc(row + 1, column + 1) == disc
          && get_disc(row + 2, column + 2) == disc
          && get_disc(row + 3, column + 3) == disc) {
          return true;
        }
      }

      // anti-diagonal
      if (row + 3 < m_rows && column - 3 >= 0) {
        if (get_disc(row + 1, column - 1) == disc
          && get_disc(row + 2, column - 2) == disc
          && get_disc(row + 3, column - 3) == disc) {
          return true;
        }
      }
    }
  }

  return false;
}
