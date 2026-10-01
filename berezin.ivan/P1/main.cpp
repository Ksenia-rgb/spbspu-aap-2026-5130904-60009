#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>

struct Matrix
{
  size_t rows = 0;
  size_t columns = 0;
  int** field = nullptr;
};

int** createMatrix(const size_t rows, const size_t columns)
{
  int** const matrix = new int*[rows];
  std::size_t created_rows = 0;
  try
  {
    for (; created_rows < rows; created_rows++)
    {
      matrix[created_rows] = new int[columns];
    }
  }
  catch (...)
  {
    for (size_t i = 0; i < created_rows; i++)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
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

void readMatrix(Matrix& matrix)
{
  for (size_t i = 0; i < matrix.rows; i++)
  {
    for (size_t j = 0; j < matrix.columns; j++)
    {
      if (!(std::cin >> matrix.field[i][j]))
      {
        throw std::runtime_error("failed to read matrix's element");
      }
    }
  }
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
  try
  {
    size_t rows = 0, columns = 0;
    if (!(std::cin >> rows >> columns))
    {
      throw std::runtime_error("failed to read matrix size");
    }
    Matrix matrix{
        rows,
        columns,
        createMatrix(rows, columns),
    };
    try
    {
      readMatrix(matrix);
      Matrix transposed = transposeMatrix(matrix);
      printMatrix(transposed);
      clearMatrix(matrix);
      clearMatrix(transposed);
    }
    catch (...)
    {
      clearMatrix(matrix);
      throw;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
