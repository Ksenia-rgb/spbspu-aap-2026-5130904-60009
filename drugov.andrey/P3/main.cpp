#include <cstddef>
#include <fstream>
#include <iostream>

namespace drugov
{
  bool run(std::istream &input, std::ostream &output, int mode)
  {
    size_t rows = 0;
    size_t cols = 0;

    if (!(input >> rows >> cols))
    {
      return false;
    }

    constexpr size_t MAX_MATRIX_SIZE = 10000;
    int fixed_matrix[MAX_MATRIX_SIZE];
    int *matrix = nullptr;

    if (mode == 1)
    {
      matrix = fixed_matrix;
    }
    else
    {
      if (rows * cols > 0)
      {
        try
        {
          matrix = new int[rows * cols];
        }
        catch (...)
        {
          throw 2;
        }
      }
    }

    for (size_t i = 0; i < rows * cols; ++i)
    {
      if (!(input >> matrix[i]))
      {
        if (mode == 2)
        {
          delete[] matrix;
        }
        return false;
      }
    }

    bool is_lower_triangular = true;

    if (rows == 0 || cols == 0 || rows != cols)
    {
      is_lower_triangular = false;
    }
    else
    {
      for (size_t r = 0; r < rows; ++r)
      {
        for (size_t c = 0; c < cols; ++c)
        {
          if (r < c && matrix[r * cols + c] != 0)
          {
            is_lower_triangular = false;
          }
        }
      }
    }

    if (rows > 0 && cols > 0)
    {
      int top = 0;
      int bottom = rows - 1;
      int left = 0;
      int right = cols - 1;
      int current_inc = 1;

      while (left <= right && top <= bottom)
      {
        for (int c = left; c <= right; ++c)
        {
          matrix[bottom * cols + c] += current_inc;
          current_inc++;
        }
        bottom--;

        for (int r = bottom; r >= top; --r)
        {
          matrix[r * cols + right] += current_inc;
          current_inc++;
        }
        right--;

        if (top <= bottom)
        {
          for (int c = right; c >= left; --c)
          {
            matrix[top * cols + c] += current_inc;
            current_inc++;
          }
          top++;
        }

        if (left <= right)
        {
          for (int r = top; r <= bottom; ++r)
          {
            matrix[r * cols + left] += current_inc;
            current_inc++;
          }
          left++;
        }
      }
    }

    output << rows << " " << cols;
    for (size_t i = 0; i < rows * cols; ++i)
    {
      output << " " << matrix[i];
    }
    output << "\n";

    if (is_lower_triangular)
    {
      output << "true\n";
    }
    else
    {
      output << "false\n";
    }

    if (mode == 2)
    {
      delete[] matrix;
    }

    return output.good();
  }
}

int main(int argc, char **argv)
{
  try
  {
    if (argc != 4)
    {
      return 1;
    }

    const char *const mode_str = argv[1];
    const char *const input_path = argv[2];
    const char *const output_path = argv[3];

    int mode = 0;
    if (mode_str[0] == '1' && mode_str[1] == '\0')
    {
      mode = 1;
    }
    else if (mode_str[0] == '2' && mode_str[1] == '\0')
    {
      mode = 2;
    }
    else
    {
      return 1;
    }

    std::ifstream input_file{input_path};
    if (!input_file)
    {
      return 1;
    }

    std::ofstream output_file{output_path};
    if (!output_file)
    {
      return 1;
    }

    if (!drugov::run(input_file, output_file, mode))
    {
      return 1;
    }

    return 0;
  }
  catch (int error)
  {
    return error;
  }
  catch (...)
  {
    return 3;
  }
}
