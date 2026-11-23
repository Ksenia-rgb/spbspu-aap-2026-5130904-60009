#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <new>

namespace anokhin
{
  const std::size_t maxFixedSize = 10000;
  const int expectedArgc = 4;
  const char fixedMode = '1';
  const char dynamicMode = '2';
  const int exitSuccess = 0;
  const int exitArgsError = 1;
  const int exitDataError = 2;

  bool diagonalHasZero(const int * data, std::size_t rows, std::size_t cols,
      std::size_t i, std::size_t j)
  {
    while (i < rows && j < cols)
    {
      if (data[i * cols + j] == 0)
      {
        return true;
      }
      ++i;
      ++j;
    }
    return false;
  }

  std::size_t countNonZeroDiagonals(const int * data, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    std::size_t count = 0;
    for (std::size_t i = 1; i + 1 < rows; ++i)
    {
      if (!diagonalHasZero(data, rows, cols, i, 0))
      {
        ++count;
      }
    }
    if (rows >= 2 && cols >= 2 && !diagonalHasZero(data, rows, cols, 0, 0))
    {
      ++count;
    }
    for (std::size_t j = 1; j + 1 < cols; ++j)
    {
      if (!diagonalHasZero(data, rows, cols, 0, j))
      {
        ++count;
      }
    }
    return count;
  }

  void spiralIncrease(int * data, std::size_t rows, std::size_t cols)
  {
    std::size_t top = 0;
    std::size_t bottom = rows;
    std::size_t left = 0;
    std::size_t right = cols;
    int step = 1;
    while (top < bottom && left < right)
    {
      for (std::size_t j = left; j < right; ++j)
      {
        data[(bottom - 1) * cols + j] += step++;
      }
      --bottom;
      for (std::size_t i = bottom; i > top; --i)
      {
        data[(i - 1) * cols + (right - 1)] += step++;
      }
      --right;
      if (top < bottom)
      {
        for (std::size_t j = right; j > left; --j)
        {
          data[top * cols + (j - 1)] += step++;
        }
        ++top;
      }
      if (left < right)
      {
        for (std::size_t i = top; i < bottom; ++i)
        {
          data[i * cols + left] += step++;
        }
        ++left;
      }
    }
  }

  bool readSize(std::istream & input, std::size_t & rows, std::size_t & cols)
  {
    long long r = 0;
    long long c = 0;
    if (!(input >> r >> c)  r < 0  c < 0)
    {
      return false;
    }
    rows = static_cast< std::size_t >(r);
    cols = static_cast< std::size_t >(c);
    return rows == 0 || cols <= SIZE_MAX / rows;
  }

  bool readElements(std::istream & input, int * data, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i)
    {
      if (!(input >> data[i]))
      {
        return false;
      }
    }
    char extra = 0;
    return !(input >> extra);
  }

  bool writeMatrix(std::ostream & output, const int * data, std::size_t rows, std::size_t cols)
  {
    output << rows << ' ' << cols;
    for (std::size_t i = 0; i < rows * cols; ++i)
    {
      output << ' ' << data[i];
    }
    output << '\n';
    return output.good();
  }

  int processMatrix(std::istream & input, std::ostream & output, int * data,
      std::size_t rows, std::size_t cols)
  {
    if (!readElements(input, data, rows * cols))
    {
      std::cerr << "Error: invalid matrix elements\n";
      return exitDataError;
    }
    output << countNonZeroDiagonals(data, rows, cols) << '\n';
    spiralIncrease(data, rows, cols);
    if (!writeMatrix(output, data, rows, cols))
    {
      std::cerr << "Error: cannot write output\n";
      return exitDataError;
    }
    return exitSuccess;
  }

  int run(std::istream & input, std::ostream & output, bool dynamic)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readSize(input, rows, cols))
    {
      std::cerr << "Error: invalid matrix size\n";
      return exitDataError;
    }
    std::size_t size = rows * cols;
    if (!dynamic)
    {
      if (size > maxFixedSize)
      {
        std::cerr << "Error: matrix is too large\n";
        return exitDataError;
      }
      int buffer[maxFixedSize] = {};
      return processMatrix(input, output, buffer, rows, cols);
    }
    int * buffer = nullptr;
    try
    {
      buffer = new int[size]();
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Error: not enough memory\n";
      return exitDataError;
    }
    int code = processMatrix(input, output, buffer, rows, cols);
    delete[] buffer;
    return code;
  }
}

int main(int argc, char ** argv)
{
  if (argc != anokhin::expectedArgc)
  {
    std::cerr << "Usage: ./lab num input output\n";
    return anokhin::exitArgsError;
  }
  const char * mode = argv[1];
  if (mode[0] == '\0' || mode[1] != '\0'
      || (mode[0] != anokhin::fixedMode && mode[0] != anokhin::dynamicMode))
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return anokhin::exitArgsError;
  }
  bool dynamic = (mode[0] == anokhin::dynamicMode);

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: cannot open input file\n";
    return anokhin::exitDataError;
  }
  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    return anokhin::exitDataError;
  }
  return anokhin::run(input, output, dynamic);
}
