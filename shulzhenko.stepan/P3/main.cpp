#include <fstream>
#include <cstddef>
#include <iostream>

namespace shulzhenko
{
  int readSize(std::istream &input, size_t &rows, size_t &cols)
  {
    size_t rowsVal = 0;
    size_t colsVal = 0;
    if (!(input >> rowsVal >> colsVal))
    {
      return false;
    }

    if (rowsVal < 0 || colsVal < 0)
    {
      return false;
    }
    return true;
  }

  bool readElements(std::istream &input, int *matrix, size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      if (!(input >> matrix[i]))
      {
        return false;
      }
    }
    return true;
  }

  int notSameElements(const int *matrix, size_t rows, size_t cols)
  {
    int count = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      bool ok = true;
      for (size_t j = 0; j + 1 < cols; ++j)
      {
        if (matrix[i * cols + j] == matrix[i * cols + j + 1])
        {
          ok = false;
          break;
        }
      }
      if (ok)
      {
        ++count;
      }
    }
    return count;
  }

  int minSum(const int *matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    size_t dCount = rows + cols - 1;
    bool first = true;
    int minSum = 0;

    for (size_t d = 0; d < dCount; ++d)
    {
      int sum = 0;
      for (size_t i = 0; i < rows; ++i)
      {
        size_t j = d - i;
        if (j < cols && i + j == d)
        {
          sum += matrix[i * cols + j];
        }
      }

      if (first || sum < minSum)
      {
        minSum = sum;
        first = false;
      }
    }

    return minSum;
  }

  bool run(std::istream &input, std::ostream &output, char mode)
  {
    size_t rows = 0;
    size_t cols = 0;
    size_t total = rows * cols;
    int result1 = 0;
    int result2 = 0;
    if (!(input >> rows >> cols))
    {
      return false;
    }
    size_t max_size = 10000;
    if (mode == '1')
    {
      if (total > max_size)
      {
        return false;
      }

      int matrix[max_size];
      if (!readElements(input, matrix, total))
      {
        return false;
      }

      if (!readSize(input, rows, cols))
      {
        return 2;
      }

      result1 = notSameElements(matrix, rows, cols);
      result2 = minSum(matrix, rows, cols);
    }
    else
    {
      int *matrix = new int[total];
      if (!readElements(input, matrix, total))
      {
        delete[] matrix;
        return false;
      }

      result1 = notSameElements(matrix, rows, cols);
      result2 = minSum(matrix, rows, cols);
      delete[] matrix;
    }

    output << result1 << '\n';
    output << result2 << '\n';
    return output.good();
  }
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    return 1;
  }

  const char *mode = argv[1];
  const char *inputPath = argv[2];
  const char *outputPath = argv[3];

  std::ifstream input{inputPath};
  if (!input)
  {
    return 1;
  }
  std::ofstream output{outputPath};
  if (!output)
  {
    return 1;
  }

  if ((mode[0] != '1' && mode[0] != '2') || (mode[1] != '\0'))
  {
    return 1;
  }

  if (!shulzhenko::run(input, output, *mode))
  {
    return 2;
  }

  return 0;
}
