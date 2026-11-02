#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>
#include <stdexcept>

namespace safarbekov
{
  const std::size_t max_fixed_size = 10000;
  const int exit_ok = 0;
  const int exit_args_error = 1;
  const int exit_input_error = 2;

  bool parseMode(const char* text, int& mode)
  {
    if (text == nullptr || text[0] == '\0' || text[1] != '\0')
    {
      return false;
    }
    if (text[0] == '1')
    {
      mode = 1;
      return true;
    }
    if (text[0] == '2')
    {
      mode = 2;
      return true;
    }
    return false;
  }

  bool readDimensions(std::istream& input, std::size_t& rows, std::size_t& cols)
  {
    long long raw_rows = 0;
    long long raw_cols = 0;
    if (!(input >> raw_rows >> raw_cols))
    {
      return false;
    }
    if (raw_rows < 0 || raw_cols < 0)
    {
      return false;
    }
    rows = static_cast< std::size_t >(raw_rows);
    cols = static_cast< std::size_t >(raw_cols);
    if (cols != 0 && rows > std::numeric_limits< std::size_t >::max() / cols)
    {
      return false;
    }
    return true;
  }

  bool readElements(std::istream& input, int* data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      if (!(input >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  std::size_t countLocalMinima(const int* data, std::size_t rows, std::size_t cols)
  {
    if (rows < 3 || cols < 3)
    {
      return 0;
    }
    std::size_t count = 0;
    for (std::size_t i = 1; i + 1 < rows; ++i)
    {
      for (std::size_t j = 1; j + 1 < cols; ++j)
      {
        const int current = data[i * cols + j];
        bool is_min = true;
        for (std::size_t di = 0; di < 3 && is_min; ++di)
        {
          for (std::size_t dj = 0; dj < 3; ++dj)
          {
            if (di == 1 && dj == 1)
            {
              continue;
            }
            if (data[(i + di - 1) * cols + (j + dj - 1)] <= current)
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

  std::size_t countColumnsWithoutRepeats(const int* data, std::size_t rows, std::size_t cols)
  {
    std::size_t count = 0;
    for (std::size_t j = 0; j < cols; ++j)
    {
      bool has_repeat = false;
      for (std::size_t i = 1; i < rows; ++i)
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

  bool writeResults(std::ostream& output, const int* data, std::size_t rows, std::size_t cols)
  {
    output << countLocalMinima(data, rows, cols) << '\n';
    output << countColumnsWithoutRepeats(data, rows, cols) << '\n';
    return output.good();
  }

  int processFixed(std::istream& input, std::ostream& output)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readDimensions(input, rows, cols))
    {
      std::cerr << "invalid matrix size\n";
      return exit_input_error;
    }
    if (cols != 0 && rows > max_fixed_size / cols)
    {
      std::cerr << "matrix is too large\n";
      return exit_input_error;
    }
    int data[max_fixed_size];
    if (!readElements(input, data, rows * cols))
    {
      std::cerr << "invalid matrix elements\n";
      return exit_input_error;
    }
    if (!writeResults(output, data, rows, cols))
    {
      std::cerr << "write error\n";
      return exit_args_error;
    }
    return exit_ok;
  }

  int processDynamic(std::istream& input, std::ostream& output)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readDimensions(input, rows, cols))
    {
      std::cerr << "invalid matrix size\n";
      return exit_input_error;
    }
    const std::size_t count = rows * cols;
    int* data = nullptr;
    try
    {
      data = new int[count];
    }
    catch (const std::exception&)
    {
      std::cerr << "memory allocation error\n";
      return exit_input_error;
    }
    int result = exit_ok;
    if (!readElements(input, data, count))
    {
      std::cerr << "invalid matrix elements\n";
      result = exit_input_error;
    }
    else
    {
      if (!writeResults(output, data, rows, cols))
      {
        std::cerr << "write error\n";
        result = exit_args_error;
      }
    }
    delete[] data;
    return result;
  }

  int lab(int argc, char** argv)
  {
    if (argc != 4)
    {
      std::cerr << "usage: ./lab num input output\n";
      return exit_args_error;
    }

    int mode = 0;
    if (!parseMode(argv[1], mode))
    {
      std::cerr << "invalid first parameter\n";
      return exit_args_error;
    }

    std::ifstream input{argv[2]};
    if (!input)
    {
      std::cerr << "cannot open input file\n";
      return exit_args_error;
    }

    std::ofstream output{argv[3]};
    if (!output)
    {
      std::cerr << "cannot open output file\n";
      return exit_args_error;
    }

    if (mode == 1)
    {
      return processFixed(input, output);
    }
    return processDynamic(input, output);
  }
}

int main(int argc, char** argv)
{
  return safarbekov::lab(argc, argv);
}
