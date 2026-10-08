<<<<<<< Updated upstream
#include <cstddef>
#include <iostream>

constexpr int success = 0;
constexpr int input_error = 1;
constexpr int allocation_error = 2;

struct Matrix
{
  size_t rows = 0;
  size_t columns = 0;
  int** field = nullptr;
};

int** createMatrix(const size_t rows, const size_t columns)
{
  int** const matrix = new int*[rows];
  if (matrix == nullptr)
  {
    return nullptr;
  }
  for (size_t i = 0; i < rows; i++)
  {
    matrix[i] = new int[columns];
    if (matrix[i] == nullptr)
    {
      for (size_t j = 0; j < i; j++)
      {
        delete[] matrix[j];
      }
      delete[] matrix;
      return nullptr;
    }
  }
  return matrix;
}

void clearMatrix(Matrix& matrix) noexcept
{
  for (size_t i = 0; i < matrix.rows; i++)
  {
    delete[] matrix.field[i];
  }
  delete[] matrix.field;
  matrix.field = nullptr;
  matrix.rows = 0;
  matrix.columns = 0;
}

bool readMatrix(Matrix& matrix)
{
  for (size_t i = 0; i < matrix.rows; i++)
  {
    for (size_t j = 0; j < matrix.columns; j++)
    {
      if (!(std::cin >> matrix.field[i][j]))
      {
        return false;
      }
    }
  }
  return true;
}

void printMatrix(const Matrix& matrix)
{
  for (size_t i = 0; i < matrix.rows; i++)
  {
    for (size_t j = 0; j < matrix.columns; j++)
    {
      std::cout << matrix.field[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

Matrix transposeMatrix(const Matrix& matrix)
{
  const size_t new_rows = matrix.columns;
  const size_t new_columns = matrix.rows;
  Matrix result{
      new_rows,
      new_columns,
      createMatrix(new_rows, new_columns),
  };
  if (result.field == nullptr)
  {
    return result;
  }
  for (size_t i = 0; i < matrix.rows; i++)
  {
    for (size_t j = 0; j < matrix.columns; j++)
    {
      result.field[j][i] = matrix.field[i][j];
    }
  }
  return result;
=======
#include <iostream>

namespace berezin {

  int GRT_LSS_DIV_REM()
  {
    int first = 0;
    if (!(std::cin >> first)) {
      std::cerr << "Error: invalid input\n";
      return 1;
    }
    if (first == 0) {
      std::cout << "0\n";
      std::cerr << "Error: not enough input values for DIV-REM\n";
      return 2;
    }

    int second = 0;
    if (!(std::cin >> second)) {
      std::cerr << "Error: invalid input\n";
      return 1;
    }
    if (second == 0) {
      std::cout << "0\n";
      std::cerr << "Error: not enough input values for DIV-REM\n";
      return 2;
    }

    unsigned int grt_lss_count = 0;
    unsigned int div_rem_count = (second % first) == 0;

    int prev = first;
    int curr = second;
    int next = 0;

    while (std::cin >> next) {
      if (next == 0) {
        break;
      }
      grt_lss_count += (curr < prev) && (curr > next);
      div_rem_count += (next % curr) == 0;
      prev = curr;
      curr = next;
    }

    if (!std::cin) {
      std::cerr << "Error: invalid input\n";
      return 1;
    }

    char extra = 0;
    if (std::cin >> extra) {
      std::cerr << "Error: extra data after \"0\"\n";
      return 1;
    }

    std::cout << grt_lss_count << '\n';
    std::cout << div_rem_count << '\n';

    return 0;
  }

>>>>>>> Stashed changes
}

int main()
{
<<<<<<< Updated upstream
  size_t rows = 0, columns = 0;
  if (!(std::cin >> rows >> columns))
  {
    return input_error;
  }

  Matrix matrix{
      rows,
      columns,
      createMatrix(rows, columns),
  };
  if (matrix.field == nullptr)
  {
    return allocation_error;
  }

  if (!readMatrix(matrix))
  {
    clearMatrix(matrix);
    return input_error;
  }

  Matrix transposed = transposeMatrix(matrix);
  if (transposed.field == nullptr)
  {
    clearMatrix(matrix);
    return allocation_error;
  }

  printMatrix(transposed);

  clearMatrix(matrix);
  clearMatrix(transposed);

  return success;
=======
  return berezin::GRT_LSS_DIV_REM();
>>>>>>> Stashed changes
}
