#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace berezin
{
  constexpr int success = 0;
  constexpr int invalidArgumentsError = 1;
  constexpr int invalidMatrixError = 2;

  constexpr int expectedArgc = 4;
  constexpr std::size_t maxFixedSize = 10000;

  constexpr char nullChar = '\0';
  constexpr char fixedMemory = '1';
  constexpr char dynamicMemory = '2';

  bool readSize(std::istream& input, std::size_t& rows, std::size_t& cols)
  {
    long long int rows_value = 0;
    long long int cols_value = 0;
    if (!(input >> rows_value >> cols_value))
    {
      return false;
    }
    if ((rows_value < 0) || (cols_value < 0))
    {
      return false;
    }
    rows = static_cast< std::size_t >(rows_value);
    cols = static_cast< std::size_t >(cols_value);
    if ((cols != 0) && (rows > (std::numeric_limits< std::size_t >::max() / cols)))
    {
      return false;
    }
    return true;
  }

  bool readElements(std::istream& input, int* matrix, std::size_t matrix_size)
  {
    for (std::size_t i = 0; i < matrix_size; i++)
    {
      if (!(input >> matrix[i]))
      {
        return false;
      }
    }
    return true;
  }

  std::size_t numColLsr(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if ((rows == 0) || (cols == 0))
    {
      return 0;
    }

    std::size_t max_length = 1;
    std::size_t max_length_col = 1;
    for (std::size_t j = 0; j < cols; j++)
    {
      std::size_t length = 1;
      for (std::size_t i = 1; i < rows; i++)
      {
        if (matrix[i * cols + j] == matrix[(i - 1) * cols + j])
        {
          length++;
          if (length > max_length)
          {
            max_length = length;
            max_length_col = j + 1;
          }
        }
        else
        {
          length = 1;
        }
      }
    }
    return max_length_col;
  }

  void lftTopClk(int* matrix, std::size_t rows, std::size_t cols)
  {
    if ((rows == 0) || (cols == 0))
    {
      return;
    }

    std::size_t top = 0;
    std::size_t bottom = rows - 1;
    std::size_t left = 0;
    std::size_t right = cols - 1;
    int step = 1;

    while ((top <= bottom) && (left <= right))
    {
      for (std::size_t j = left; j <= right; j++, step++)
      {
        matrix[top * cols + j] -= step;
      }
      for (std::size_t i = top + 1; i <= bottom; i++, step++)
      {
        matrix[i * cols + right] -= step;
      }
      if (top < bottom)
      {
        for (std::size_t j = right; j > left; j--, step++)
        {
          matrix[bottom * cols + j - 1] -= step;
        }
      }
      if (left < right)
      {
        for (std::size_t i = bottom; i > top + 1; i--, step++)
        {
          matrix[(i - 1) * cols + left] -= step;
        }
      }
      if ((bottom == 0) || (right == 0))
      {
        break;
      }
      top++;
      left++;
      bottom--;
      right--;
    }
  }

  void printMatrix(std::ostream& output, const int* matrix, std::size_t rows, std::size_t cols)
  {
    output << rows << ' ' << cols;
    for (std::size_t i = 0; i < rows * cols; i++)
    {
      output << ' ' << matrix[i];
    }
  }

  int numColLsrAndLftTopClk(std::istream& input, std::ostream& output, int* matrix, std::size_t rows, std::size_t cols)
  {
    if (!readElements(input, matrix, rows * cols))
    {
      std::cerr << "Error: invalid matrix data\n";
      return invalidMatrixError;
    }

    char extra = nullChar;
    if (input >> extra)
    {
      std::cerr << "Error: extra data after matrix\n";
      return invalidMatrixError;
    }

    output << numColLsr(matrix, rows, cols) << '\n';
    lftTopClk(matrix, rows, cols);
    printMatrix(output, matrix, rows, cols);
    output << '\n';
    if (!output)
    {
      std::cerr << "Error: cannot write in output file\n";
      return invalidMatrixError;
    }
    return success;
  }

  int lab(int argc, char** argv)
  {
    if (argc != expectedArgc)
    {
      std::cerr << "Error: wrong number of arguments\n";
      return invalidArgumentsError;
    }

    const char* const mode = argv[1];
    const char* const inputPath = argv[2];
    const char* const outputPath = argv[3];

    if (((mode[0] != fixedMemory) && (mode[0] != dynamicMemory)) || (mode[1] != nullChar))
    {
      std::cerr << "Error: first parameter must be " << fixedMemory << " or " << dynamicMemory << "\n";
      return invalidArgumentsError;
    }

    std::ifstream input{inputPath};
    if (!input)
    {
      std::cerr << "Error: cannot open input file\n";
      return invalidArgumentsError;
    }
    std::ofstream output{outputPath};
    if (!output)
    {
      std::cerr << "Error: cannot open output file\n";
      return invalidArgumentsError;
    }

    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readSize(input, rows, cols))
    {
      std::cerr << "Error: invalid matrix size\n";
      return invalidMatrixError;
    }
    const std::size_t matrix_size = rows * cols;

    if (mode[0] == fixedMemory)
    {
      if (matrix_size > maxFixedSize)
      {
        std::cerr << "Error: matrix size is bigger than " << maxFixedSize << "\n";
        return invalidMatrixError;
      }
      int matrix[maxFixedSize] = {};
      return numColLsrAndLftTopClk(input, output, matrix, rows, cols);
    }

    int* matrix = nullptr;
    try
    {
      matrix = new int[matrix_size];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Error: not enough memory\n";
      return invalidMatrixError;
    }

    const int result = numColLsrAndLftTopClk(input, output, matrix, rows, cols);

    delete[] matrix;
    return result;
  }
}

int main(int argc, char** argv)
{
  return berezin::lab(argc, argv);
}
