#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace vezovsky
{
  const std::size_t limit = 10000;

  bool readdimensions(std::istream& in, std::size_t& rows, std::size_t& cols)
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

  std::size_t findcolumnwithlongestrun(const int* m, std::size_t h, std::size_t w)
  {
    if (h == 0 || w == 0)
    {
      return 0;
    }
    std::size_t best = 1;
    std::size_t col = 1;
    for (std::size_t j = 0; j < w; j++)
    {
      std::size_t run = 1;
      for (std::size_t i = 1; i < h; i++)
      {
        run = (m[i * w + j] == m[(i - 1) * w + j]) ? run + 1 : 1;
        if (run > best)
        {
          best = run;
          col = j + 1;
        }
      }
    }
    return col;
  }

  void addspiral(int* m, std::size_t rows, std::size_t cols)
  {
    std::size_t top = 0, left = 0, bottom = rows, right = cols;
    int add = 1;
    while (top < bottom && left < right)
    {
      for (std::size_t j = left; j < right; j++)
      {
        m[(bottom - 1) * cols + j] += add++;
      }
      bottom--;
      if (top < bottom)
      {
        for (std::size_t i = bottom; i > top; i--)
        {
          m[(i - 1) * cols + (right - 1)] += add++;
        }
        right--;
      }
      if (top < bottom && left < right)
      {
        for (std::size_t j = right; j > left; j--)
        {
          m[top * cols + (j - 1)] += add++;
        }
        top++;
      }
      if (top < bottom && left < right)
      {
        for (std::size_t i = top; i < bottom; i++)
        {
          m[i * cols + left] += add++;
        }
        left++;
      }
    }
  }

  int processmatrix(std::istream& in, std::ostream& out, int* data, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows * cols; i++)
    {
      if (!(in >> data[i]))
      {
        std::cerr << "error: invalid matrix data\n";
        return 2;
      }
    }
    char extra = '\0';
    if (in >> extra)
    {
      std::cerr << "error: extra data after matrix\n";
      return 2;
    }
    out << findcolumnwithlongestrun(data, rows, cols) << '\n';
    addspiral(data, rows, cols);
    out << rows << ' ' << cols;
    for (std::size_t i = 0; i < rows * cols; i++)
    {
      out << ' ' << data[i];
    }
    out << '\n';
    if (!out)
    {
      std::cerr << "error: cannot write in output file\n";
      return 2;
    }
    return 0;
  }

  int runlab(int argc, char** argv)
  {
    if (argc != 4)
    {
      std::cerr << "error: wrong number of arguments\n";
      return 1;
    }
    const char* const mode = argv[1];
    if ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\0')
    {
      std::cerr << "error: first parameter must be 1 or 2\n";
      return 1;
    }
    std::ifstream in{argv[2]};
    if (!in)
    {
      std::cerr << "error: cannot open input file\n";
      return 1;
    }
    std::ofstream out{argv[3]};
    if (!out)
    {
      std::cerr << "error: cannot open output file\n";
      return 1;
    }
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readdimensions(in, rows, cols))
    {
      std::cerr << "error: invalid matrix size\n";
      return 2;
    }
    const std::size_t total = rows * cols;
    if (mode[0] == '1')
    {
      if (total > limit)
      {
        std::cerr << "error: matrix size is bigger than " << limit << "\n";
        return 2;
      }
      int data[limit] = {};
      return processmatrix(in, out, data, rows, cols);
    }
    int* data = nullptr;
    try
    {
      data = new int[total];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "error: not enough memory\n";
      return 2;
    }
    const int code = processmatrix(in, out, data, rows, cols);
    delete[] data;
    return code;
  }
}

int main(int argc, char** argv)
{
  return vezovsky::runlab(argc, argv);
}
