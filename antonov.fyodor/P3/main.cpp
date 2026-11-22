#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace antonov
{

  enum StorageMode
  {
    fixed_storage = 1,
    dynamic_storage = 2
  };

  enum StatusCode
  {
    status_ok = 0,
    status_bad_usage = 1,
    status_bad_data = 2
  };

  enum Capacity
  {
    max_fixed_elements = 10000,
    required_argc = 4
  };

  enum ArgIndex
  {
    arg_mode = 1,
    arg_input = 2,
    arg_output = 3
  };

  bool parseMode(const char *const text, StorageMode &mode)
  {
    if (text[0] == '1' && text[1] == '\0')
    {
      mode = fixed_storage;
      return true;
    }
    if (text[0] == '2' && text[1] == '\0')
    {
      mode = dynamic_storage;
      return true;
    }
    return false;
  }

  bool endOfMatrix(std::istream &input)
  {
    char extra = '\0';
    if (input >> extra)
    {
      return false;
    }
    return input.eof();
  }

  bool readValue(std::istream &input, int &value)
  {
    return static_cast< bool >(input >> value);
  }

  bool readShape(std::istream &input, int &rows, int &cols, int &count, int capacity)
  {
    if (!(input >> rows >> cols))
    {
      return false;
    }
    if (rows < 0 || cols < 0)
    {
      return false;
    }
    if (cols != 0 && rows > capacity / cols)
    {
      return false;
    }
    count = rows * cols;
    return true;
  }

  bool readElements(std::istream &input, int *const data, int count)
  {
    for (int index = 0; index < count; ++index)
    {
      if (!readValue(input, data[static_cast< std::size_t >(index)]))
      {
        return false;
      }
    }
    return endOfMatrix(input);
  }

  int elementAt(const int *const data, int cols, int row, int col)
  {
    const std::size_t index
        = static_cast< std::size_t >(row) * static_cast< std::size_t >(cols) + static_cast< std::size_t >(col);
    return data[index];
  }

  bool isLowerTriangular(const int *const data, int rows, int cols)
  {
    const int side = (rows < cols) ? rows : cols;
    if (side == 0)
    {
      return false;
    }
    for (int row = 0; row < side; ++row)
    {
      for (int col = row + 1; col < side; ++col)
      {
        if (elementAt(data, cols, row, col) != 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  int countSaddlePoints(const int *const data, int rows, int cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    int count = 0;
    for (int row = 0; row < rows; ++row)
    {
      int row_min = elementAt(data, cols, row, 0);
      for (int col = 1; col < cols; ++col)
      {
        const int value = elementAt(data, cols, row, col);
        if (value < row_min)
        {
          row_min = value;
        }
      }
      for (int col = 0; col < cols; ++col)
      {
        const int value = elementAt(data, cols, row, col);
        if (value != row_min)
        {
          continue;
        }
        int col_max = elementAt(data, cols, 0, col);
        for (int other = 1; other < rows; ++other)
        {
          const int candidate = elementAt(data, cols, other, col);
          if (candidate > col_max)
          {
            col_max = candidate;
          }
        }
        if (value == col_max)
        {
          ++count;
        }
      }
    }
    return count;
  }

  bool writeResults(std::ostream &output, const int *const data, int rows, int cols)
  {
    output << std::boolalpha << isLowerTriangular(data, rows, cols) << '\n';
    output << countSaddlePoints(data, rows, cols) << '\n';
    output.flush();
    return output.good();
  }

  int processLoaded(std::istream &input, std::ostream &output, int *const data, int rows, int cols, int count)
  {
    if (!readElements(input, data, count))
    {
      std::cerr << "Error: invalid matrix\n";
      return status_bad_data;
    }
    if (!writeResults(output, data, rows, cols))
    {
      std::cerr << "Error: cannot write output file\n";
      return status_bad_data;
    }
    return status_ok;
  }

}

int main(int argc, char *const *const argv)
{
  if (argc != antonov::required_argc)
  {
    std::cerr << "Error: invalid arguments\n";
    return antonov::status_bad_usage;
  }

  antonov::StorageMode mode = antonov::fixed_storage;
  if (!antonov::parseMode(argv[antonov::arg_mode], mode))
  {
    std::cerr << "Error: invalid arguments\n";
    return antonov::status_bad_usage;
  }

  std::ifstream input{argv[antonov::arg_input]};
  if (!input)
  {
    std::cerr << "Error: cannot open input file\n";
    return antonov::status_bad_usage;
  }

  std::ofstream output{argv[antonov::arg_output], std::ios::out | std::ios::binary};
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    return antonov::status_bad_usage;
  }

  int rows = 0;
  int cols = 0;
  int count = 0;
  const int capacity
      = (mode == antonov::fixed_storage) ? antonov::max_fixed_elements : std::numeric_limits< int >::max();
  if (!antonov::readShape(input, rows, cols, count, capacity))
  {
    std::cerr << "Error: invalid matrix\n";
    return antonov::status_bad_data;
  }

  if (mode == antonov::fixed_storage)
  {
    int data[antonov::max_fixed_elements] = {};
    return antonov::processLoaded(input, output, data, rows, cols, count);
  }

  int *data = nullptr;
  try
  {
    if (count > 0)
    {
      data = new int[static_cast< std::size_t >(count)];
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: invalid matrix\n";
    return antonov::status_bad_data;
  }

  const int code = antonov::processLoaded(input, output, data, rows, cols, count);
  delete[] data;
  return code;
}
