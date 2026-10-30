#include <fstream>
#include <iostream>

namespace safarbekov
{
  const int max_fixed_size = 10000;

  bool parseMode(const char* arg, int& mode)
  {
    if ((arg[0] == '1' || arg[0] == '2') && arg[1] == '\0')
    {
      mode = arg[0] - '0';
      return true;
    }
    return false;
  }

  bool readDimensions(std::istream& in, int& rows, int& cols)
  {
    if (!(in >> rows >> cols))
    {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::istream& in, int* data, long long count)
  {
    for (long long i = 0; i < count; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  int countLocalMinima(const int* data, int rows, int cols)
  {
    int count = 0;
    for (int i = 1; i < rows - 1; ++i)
    {
      for (int j = 1; j < cols - 1; ++j)
      {
        const int value = data[i * cols + j];
        bool is_min = true;
        for (int di = -1; di <= 1 && is_min; ++di)
        {
          for (int dj = -1; dj <= 1; ++dj)
          {
            if (di == 0 && dj == 0)
            {
              continue;
            }
            if (data[(i + di) * cols + (j + dj)] <= value)
            {
              is_min = false;
              break;
            }
          }
        }
        if (is_min)
        {
          ++count;
        }
      }
    }
    return count;
  }

  int countColumnsWithoutRepeats(const int* data, int rows, int cols)
  {
    int count = 0;
    for (int j = 0; j < cols; ++j)
    {
      bool has_repeat = false;
      for (int i = 1; i < rows; ++i)
      {
        if (data[i * cols + j] == data[(i - 1) * cols + j])
        {
          has_repeat = true;
          break;
        }
      }
      if (!has_repeat)
      {
        ++count;
      }
    }
    return count;
  }

  bool writeResults(const char* output_name, const int* data, int rows, int cols)
  {
    std::ofstream out(output_name);
    if (!out)
    {
      return false;
    }
    const int res_2 = countLocalMinima(data, rows, cols);
    const int res_9 = countColumnsWithoutRepeats(data, rows, cols);
    out << res_2 << '\n';
    out << res_9 << '\n';
    return static_cast< bool >(out);
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return 1;
  }

  int mode = 0;
  if (!safarbekov::parseMode(argv[1], mode))
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!safarbekov::readDimensions(in, rows, cols))
  {
    std::cerr << "Error: input is not a matrix\n";
    return 2;
  }
  const long long count = static_cast< long long >(rows) * cols;

  if (mode == 1)
  {
    if (count > safarbekov::max_fixed_size)
    {
      std::cerr << "Error: matrix is too large for fixed array\n";
      return 2;
    }
    int data[safarbekov::max_fixed_size] = {};
    if (!safarbekov::readElements(in, data, count))
    {
      std::cerr << "Error: input is not a matrix\n";
      return 2;
    }
    if (!safarbekov::writeResults(argv[3], data, rows, cols))
    {
      std::cerr << "Error: cannot write output file\n";
      return 2;
    }
  }
  else
  {
    int* const data = new int[count];
    if (!safarbekov::readElements(in, data, count))
    {
      delete[] data;
      std::cerr << "Error: input is not a matrix\n";
      return 2;
    }
    const bool is_written = safarbekov::writeResults(argv[3], data, rows, cols);
    delete[] data;
    if (!is_written)
    {
      std::cerr << "Error: cannot write output file\n";
      return 2;
    }
  }
  return 0;
}
