#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>
#include <limits>

namespace shulzhenko
{
  constexpr std::size_t max_size = 10000;

  constexpr int success = 0;
  constexpr int invalid_argument = 1;
  constexpr int invalid_matrix = 2;
  constexpr int exp_argc = 4;

  constexpr char nullChar = '\0';
  constexpr char fixedMemory = '1';
  constexpr char dynamicMemory = '2';

  bool readSize(std::istream &input, std::size_t &rows, std::size_t &cols)
  {
    long long int rows_val = 0;
    long long int cols_val = 0;

    if (!(input >> rows_val >> cols_val))
    {
      return false;
    }

    if (rows_val < 0 || cols_val < 0)
    {
      return false;
    }
    if ((cols != 0) && (rows > (std::numeric_limits< std::size_t >::max() / cols)))
    {
      return false;
    }

    rows = static_cast< std::size_t >(rows_val);
    cols = static_cast< std::size_t >(cols_val);
    return true;
  }

  bool readElements(std::istream &input, int *matrix, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i)
    {
      if (!(input >> matrix[i]))
      {
        return false;
      }
    }
    return true;
  }

  int notSameElements(const int *matrix, std::size_t rows, std::size_t cols)
  {
    int count = 0;

    for (std::size_t i = 0; i < rows; ++i)
    {
      bool ok = true;

      for (std::size_t j = 0; j + 1 < cols; ++j)
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

  int minSum(const int *matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    const std::size_t d_count = rows + cols - 1;
    bool first = true;
    int min_sum = 0;

    for (std::size_t d = 0; d < d_count; ++d)
    {
      int sum = 0;

      for (std::size_t i = 0; i < rows; ++i)
      {
        if (i <= d)
        {
          const std::size_t j = d - i;

          if (j < cols)
          {
            sum += matrix[i * cols + j];
          }
        }
      }

      if (first || sum < min_sum)
      {
        min_sum = sum;
        first = false;
      }
    }

    return min_sum;
  }

  bool run(std::istream &input, std::ostream &output, char mode)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!readSize(input, rows, cols))
    {
      return false;
    }

    const std::size_t total = rows * cols;
    long long int result1 = 0;
    long long int result2 = 0;

    if (mode == fixedMemory)
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

      result1 = notSameElements(matrix, rows, cols);
      result2 = minSum(matrix, rows, cols);
    }
    else if (mode == dynamicMemory)
    {
      int *matrix = nullptr;

      if (total > 0)
      {
        matrix = new int[total];

        if (matrix == nullptr)
        {
          return false;
        }

        if (!readElements(input, matrix, total))
        {
          delete[] matrix;
          return false;
        }
      }

      result1 = notSameElements(matrix, rows, cols);
      result2 = minSum(matrix, rows, cols);
      delete[] matrix;
    }

    output << result1 << '\n';
    output << result2 << '\n';

    return output.good();
  }

  int laba(int argc, char **argv)
  {
    if (argc != exp_argc)
    {
      std::cerr << "Error: wrong number\n";
      return invalid_argument;
    }

    const char *const mode = argv[1];
    const char *const input_path = argv[2];
    const char *const output_path = argv[3];

    if ((mode[0] != fixedMemory && mode[0] != dynamicMemory) || mode[1] != nullChar)
    {
      std::cerr << "Error: ffixedMemory or dynamicMemory\n";
      return invalid_argument;
    }

    std::ifstream input{input_path};

    if (!input)
    {
      std::cerr << "Error: cannot open input file\n";
      return invalid_argument;
    }

    std::ofstream output{output_path};

    if (!output)
    {
      std::cerr << "Error: cannot open output file\n";
      return invalid_argument;
    }

    if (!shulzhenko::run(input, output, mode[0]))
    {
      std::cerr << "Error: matrix is too large to process\n";
      return invalid_matrix;
    }

    return success;
  }
}

int main(int argc, char **argv)
{
  return shulzhenko::laba(argc, argv);
}
