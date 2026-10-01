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
}

int main()
{
  size_t rows = 0, columns = 0;
  if (!(std::cin >> rows >> columns))
  {
    return inputError;
  }

  Matrix matrix{
      rows,
      columns,
      createMatrix(rows, columns),
  };
  if (matrix.field == nullptr)
  {
    return allocationError;
  }

  if (!readMatrix(matrix))
  {
    clearMatrix(matrix);
    return inputError;
  }

  Matrix transposed = transposeMatrix(matrix);
  if (transposed.field == nullptr)
  {
    clearMatrix(matrix);
    return allocationError;
  }

  printMatrix(transposed);

  clearMatrix(matrix);
  clearMatrix(transposed);

  return success;
}
