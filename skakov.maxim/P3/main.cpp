#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace skakov {

  constexpr int success = 0;
  constexpr int arguments_error = 1;
  constexpr int matrix_error = 2;

  constexpr int expected_argc = 4;
  constexpr std::size_t max_fixed_elements = 10000;

  struct LabError {
    int code;
    const char* message;
  };

  void inputSize(std::istream& input, std::size_t& rows, std::size_t& cols)
  {
    long long rows_value = 0;
    long long cols_value = 0;
    if (!(input >> rows_value >> cols_value) || rows_value < 0 || cols_value < 0) {
      throw LabError{matrix_error, "invalid matrix size"};
    }

    rows = static_cast< std::size_t >(rows_value);
    cols = static_cast< std::size_t >(cols_value);
    if (rows != 0 && cols > std::numeric_limits< std::size_t >::max() / rows) {
      throw LabError{matrix_error, "invalid matrix size"};
    }
  }

  void inputMatrix(std::istream& input, int* matrix, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i) {
      if (!(input >> matrix[i])) {
        throw LabError{matrix_error, "invalid matrix data"};
      }
    }
  }

  std::size_t countNonZeroDiagonals(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    std::size_t count = 0;
    for (long long d = -static_cast< long long >(rows - 1); d <= static_cast< long long >(cols - 1); ++d) {
      if (d == 0) {
        continue;
      }

      std::size_t i = d < 0 ? static_cast< std::size_t >(-d) : 0;
      std::size_t j = d > 0 ? static_cast< std::size_t >(d) : 0;

      bool has_zero = false;
      for (; i < rows && j < cols; ++i, ++j) {
        if (matrix[i * cols + j] == 0) {
          has_zero = true;
          break;
        }
      }
      if (!has_zero) {
        ++count;
      }
    }
    return count;
  }

  long long minAntiDiagonalSum(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    bool is_first = true;
    long long min_sum = 0;
    for (std::size_t s = 0; s <= rows + cols - 2; ++s) {
      const std::size_t i_begin = s >= cols ? s - (cols - 1) : 0;
      const std::size_t i_end = s < rows ? s : rows - 1;

      long long sum = 0;
      for (std::size_t i = i_begin; i <= i_end; ++i) {
        sum += matrix[i * cols + (s - i)];
      }

      if (is_first || sum < min_sum) {
        min_sum = sum;
        is_first = false;
      }
    }
    return min_sum;
  }

  void processMatrix(std::istream& input, std::ostream& output, int* matrix, std::size_t rows, std::size_t cols)
  {
    inputMatrix(input, matrix, rows * cols);

    output << countNonZeroDiagonals(matrix, rows, cols) << '\n';
    output << minAntiDiagonalSum(matrix, rows, cols) << '\n';
    if (!output) {
      throw LabError{arguments_error, "cannot write output"};
    }
  }

  void runFixed(std::istream& input, std::ostream& output, std::size_t rows, std::size_t cols)
  {
    if (rows * cols > max_fixed_elements) {
      throw LabError{matrix_error, "matrix is too large"};
    }
    int matrix[max_fixed_elements];
    processMatrix(input, output, matrix, rows, cols);
  }

  void runDynamic(std::istream& input, std::ostream& output, std::size_t rows, std::size_t cols)
  {
    int* const matrix = new int[rows * cols];
    try {
      processMatrix(input, output, matrix, rows, cols);
    } catch (...) {
      delete[] matrix;
      throw;
    }
    delete[] matrix;
  }

  int lab(int argc, char** argv)
  {
    try {
      if (argc != expected_argc) {
        throw LabError{arguments_error, "invalid number of arguments"};
      }

      const char* const mode = argv[1];
      const bool is_fixed = mode[0] == '1' && mode[1] == '\0';
      const bool is_dynamic = mode[0] == '2' && mode[1] == '\0';
      if (!is_fixed && !is_dynamic) {
        throw LabError{arguments_error, "invalid task number"};
      }

      std::ifstream input{argv[2]};
      if (!input) {
        throw LabError{arguments_error, "cannot open input file"};
      }
      std::ofstream output{argv[3]};
      if (!output) {
        throw LabError{arguments_error, "cannot open output file"};
      }

      std::size_t rows = 0;
      std::size_t cols = 0;
      inputSize(input, rows, cols);

      if (is_dynamic) {
        runDynamic(input, output, rows, cols);
      } else {
        runFixed(input, output, rows, cols);
      }
    } catch (const LabError& error) {
      std::cerr << "Error: " << error.message << '\n';
      return error.code;
    } catch (const std::bad_alloc&) {
      std::cerr << "Error: not enough memory\n";
      return matrix_error;
    }
    return success;
  }

}

int main(int argc, char** argv)
{
  return skakov::lab(argc, argv);
}
