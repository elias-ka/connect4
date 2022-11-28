#include <algorithm>

#include "grid.hpp"

bool Grid::is_full() const
{
  bool is_full = true;
  for (const auto& row : m_discs) {
    for (const auto& disc : row) {
      if (disc == Disc::EMPTY) {
        is_full = false;
      }
    }
  }

  return is_full;
}

Disc Grid::get_disc(const int row, const int column) const
{
  return m_discs[row][column];
}

bool Grid::drop_disc(const int column, const Disc disc)
{
  if (column >= m_columns) {
    return false;
  }

  for (int row = m_rows - 1; row >= 0; --row) {
    if (m_discs[row][column] == Disc::EMPTY) {
      m_discs[row][column] = disc;
      return true;
    }
  }

  return false;
}

bool Grid::are_four_connected(Disc disc) const
{
  for (int row = 0; row < m_rows; ++row) {
    for (int column = 0; column < m_columns; ++column) {
      if (disc == Disc::EMPTY) {
        continue;
      }

      // horizontal
      if (column + 3 < m_columns) {
        if (get_disc(row, column) == disc && get_disc(row, column + 1) == disc && get_disc(row, column + 2) == disc
            && get_disc(row, column + 3) == disc)
        {
          return true;
        }
      }

      // vertical
      if (row + 3 < m_rows) {
        if (get_disc(row, column) == disc && get_disc(row + 1, column) == disc && get_disc(row + 2, column) == disc
            && get_disc(row + 3, column) == disc)
        {
          return true;
        }
      }

      // diagonal
      if (row + 3 < m_rows && column + 3 < m_columns) {
        if (get_disc(row, column) == disc && get_disc(row + 1, column + 1) == disc
            && get_disc(row + 2, column + 2) == disc && get_disc(row + 3, column + 3) == disc)
        {
          return true;
        }
      }

      // anti-diagonal
      if (row + 3 < m_rows && column - 3 >= 0) {
        if (get_disc(row, column) == disc && get_disc(row + 1, column - 1) == disc
            && get_disc(row + 2, column - 2) == disc && get_disc(row + 3, column - 3) == disc)
        {
          return true;
        }
      }
    }
  }

  return false;
}