#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace vezovsky
{
  const std::size_t fixedLimit = 10000;

  bool readDimensions(std::istream& in, std::size_t& rows, std::size_t& cols)
  {
    long long int r = 0;
    long long int c = 0;
    if (!(in >> r >> c) || r < 0 || c < 0)
    {
      return false;
    }
    rows = static_cast< std::size_t >(r);
    cols = static_cast< std::size_t >(c);
    return cols == 0 || rows <= std::numeric_limits< std::size_t >::max() / cols;
  }

  std::size_t findColumnWithLongestRun(const int* data, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    std::size_t bestLength = 1;
    std::size_t bestColumn = 1;
    for (std::size_t col = 0; col < cols; col++)
    {
      std::size_t length = 1;
      for (std::size_t row = 1; row < rows; row++)
      {
        length = (data[row * cols + col] == data[(row - 1) * cols + col]) ? length + 1 : 1;
        if (length > bestLength)
        {
          bestLength = length;
          bestColumn = col + 1;
        }
      }
    }
    return bestColumn;
  }

  void addSpiral(int* data, std::size_t rows, std::size_t cols)
  {
    std::size_t top = 0, left = 0, bottom = rows, right = cols;
    int number = 1;
    while (top < bottom && left < right)
    {
      for (std::size_t col = left; col < right; col++)
      {
        data[(bottom - 1) * cols + col] += number++;
      }
      bottom--;
      if (top < bottom)
      {
        for (std::size_t row = bottom; row > top; row--)
        {
          data[(row - 1) * cols + (right - 1)] += number++;
        }
        right--;
      }
      if (top < bottom && left < right)
      {
        for (std::size_t col = right; col > left; col--)
        {
          data[top * cols + (col - 1)] += number++;
        }
        top++;
      }
      if (top < bottom && left < right)
      {
        for (std::size_t row = top; row < bottom; row++)
        {
          data[row * cols + left] += number++;
        }
        left++;
      }
    }
  }

  int processMatrix(std::istream& in, std::ostream& out, int* data, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows * cols; i++)
    {
      if (!(in >> data[i]))
      {
        std::cerr << "Error: invalid matrix data\n";
        return 2;
      }
    }
    char extra = '\0';
    if (in >> extra)
    {
      std::cerr << "Error: extra data after matrix\n";
      return 2;
    }
    out << findColumnWithLongestRun(data, rows, cols) << '\n';
    addSpiral(data, rows, cols);
    out << rows << ' ' << cols;
    for (std::size_t i = 0; i < rows * cols; i++)
    {
      out << ' ' << data[i];
    }
    out << '\n';
    if (!out)
    {
      std::cerr << "Error: cannot write in output file\n";
      return 2;
    }
    return 0;
  }

  int runLab(int argc, char** argv)
  {
    if (argc != 4)
    {
      std::cerr << "Error: wrong number of arguments\n";
      return 1;
    }
    const char* mode = argv[1];
    if ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\0')
    {
      std::cerr << "Error: first parameter must be 1 or 2\n";
      return 1;
    }
    std::ifstream in{argv[2]};
    if (!in)
    {
      std::cerr << "Error: cannot open input file\n";
      return 1;
    }
    std::ofstream out{argv[3]};
    if (!out)
    {
      std::cerr << "Error: cannot open output file\n";
      return 1;
    }
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readDimensions(in, rows, cols))
    {
      std::cerr << "Error: invalid matrix size\n";
      return 2;
    }
    const std::size_t total = rows * cols;
    if (mode[0] == '1')
    {
      if (total > fixedLimit)
      {
        std::cerr << "Error: matrix size is bigger than " << fixedLimit << "\n";
        return 2;
      }
      int data[fixedLimit] = {};
      return processMatrix(in, out, data, rows, cols);
    }
    int* data = nullptr;
    try
    {
      data = new int[total];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Error: not enough memory\n";
      return 2;
    }
    int code = processMatrix(in, out, data, rows, cols);
    delete[] data;
    return code;
  }
}

int main(int argc, char** argv)
{
  return vezovsky::runLab(argc, argv);
}

