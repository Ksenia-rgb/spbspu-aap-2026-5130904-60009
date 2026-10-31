#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <new>
{
  const std::size_t maxFixedSize = 10000;

  std::size_t countNonZeroDiagonals(const int * data, std::size_t rows, std::size_t cols)
  {
    long long r = static_cast< long long >(rows);
    long long c = static_cast< long long >(cols);
    std::size_t count = 0;
    for (long long d = -(r - 2); d <= c - 2; ++d)
    {
      long long i = (d < 0) ? -d : 0;
      long long j = i + d;
      bool hasZero = false;
      while (i < r && j < c)
      {
        if (data[i * c + j] == 0)
        {
          hasZero = true;
          break;
        }
        ++i;
        ++j;
      }
      if (!hasZero)
      {
        ++count;
      }
    }
    return count;
  }

  void spiralIncrease(int * data, std::size_t rows, std::size_t cols)
  {
    long long c = static_cast< long long >(cols);
    long long top = 0;
    long long bottom = static_cast< long long >(rows) - 1;
    long long left = 0;
    long long right = c - 1;
    int step = 1;
    while (top <= bottom && left <= right)
    {
      for (long long j = left; j <= right; ++j)
      {
        data[bottom * c + j] += step++;
      }
      --bottom;
      for (long long i = bottom; i >= top; --i)
      {
        data[i * c + right] += step++;
      }
      --right;
      if (top <= bottom)
      {
        for (long long j = right; j >= left; --j)
        {
          data[top * c + j] += step++;
        }
        ++top;
      }
      if (left <= right)
      {
        for (long long i = top; i <= bottom; ++i)
        {
          data[i * c + left] += step++;
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
    return true;
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
      return 2;
    }
    output << countNonZeroDiagonals(data, rows, cols) << '\n';
    spiralIncrease(data, rows, cols);
    if (!writeMatrix(output, data, rows, cols))
    {
      std::cerr << "Error: cannot write output\n";
      return 2;
    }
    return 0;
  }

  int run(std::istream & input, std::ostream & output, bool dynamic)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readSize(input, rows, cols))
    {
      std::cerr << "Error: invalid matrix size\n";
      return 2;
    }
    std::size_t size = rows * cols;
    if (!dynamic)
    {
      if (size > maxFixedSize)
      {
        std::cerr << "Error: matrix is too large\n";
        return 2;
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
      return 2;
    }
    int code = processMatrix(input, output, buffer, rows, cols);
    delete[] buffer;
    return code;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: ./lab num input output\n";
    return 1;
  }
  const char * mode = argv[1];
  if (mode[0] == '\0'  mode[1] != '\0'  (mode[0] != '1' && mode[0] != '2'))
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }
  bool dynamic = (mode[0] == '2');

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }
  return anokhin::run(input, output, dynamic);
}
