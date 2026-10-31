#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <fstream>

namespace sokolova {
  constexpr std::size_t max_fix = 10000;

  size_t countLocalMax(const int * m, std::size_t rows, std::size_t cols)
  {
    if (rows < 3 || cols < 3) {
      return 0;
    }
    std::size_t count = 0;
    for (std::size_t i = 1; i + 1 < rows; ++i) {
      for (std::size_t j = 1; j + 1 < cols; ++j) {
        const int v = m[i * cols + j];
        bool is_max = true;
        for (std::size_t di = 0; di < 3 && is_max; ++di) {
          for (std::size_t dj = 0; dj < 3; ++dj) {
            if (di == 1 && dj == 1) {
              continue;
            }
            if (m[(i + di - 1) * cols + (j + dj - 1)] >= v) {
              is_max = false;
              break;
            }
          }
        }
        if (is_max) {
          ++count;
        }
      }
    }
    return count;
  }

  void spiralInc(int * m, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return;
    }
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    const int w = cols;
    int step = 1;

    while (top <= bottom && left <= right) {
      for (int j = left; j <= right; ++j) {
        m[bottom * w + j] += step++;
      }
      --bottom;
      for (int i = bottom; i >= top; --i) {
        m[i * w + right] += step++;
      }
      --right;
      if (top <= bottom) {
        for (int j = right; j >= left; --j) {
          m[top * w + j] += step++;
        }
        ++top;
      }
      if (left <= right) {
        for (int i = top; i <= bottom; ++i) {
          m[i * w + left] += step++;
        }
        ++left;
      }
    }
  }

  bool readElements(std::istream & in, int * data, size_t n)
  {
    for (size_t i = 0; i < n; ++i) {
      if (!(in >> data[i])) {
        return false;
      }
    }
    return true;
  }

  bool process(std::istream & in, std::ostream & out, int * data, std::size_t rows, std::size_t cols)
  {
    if (!readElements(in, data, rows * cols)) {
      return false;
    }

    out << countLocalMax(data, rows, cols) << '\n';

    spiralInc(data, rows, cols);
    out << rows << ' ' << cols;
    for (size_t i = 0; i < rows * cols; ++i) {
      out << ' ' << data[i];
    }
    out << '\n';

    return out.good();
  }

  bool runFixed(std::istream & in, std::ostream & out, std::size_t rows, std::size_t cols)
  {
    int data[max_fix] = {};
    return process(in, out, data, rows, cols);
  }

  bool runDynamic(std::istream & in, std::ostream & out, std::size_t rows, std::size_t cols)
  {
    const std::size_t n = rows * cols;
    int * const data = static_cast< int * >(std::malloc((n == 0 ? 1 : n) * sizeof(int)));
    if (data == nullptr) {
      return false;
    }
    const bool ok = process(in, out, data, rows, cols);
    std::free(data);
    return ok;
  }

  int parseMode(const char * s)
  {
    if (s[0] != '\0' && s[1] == '\0') {
      if (s[0] == '1') {
        return 1;
      }
      if (s[0] == '2') {
        return 2;
      }
    }
    return 0;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return 1;
  }

  const int mode = sokolova::parseMode(argv[1]);
  if (mode == 0) {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  long long r = 0;
  long long c = 0;
  if (!(input >> r >> c) || r < 0 || c < 0) {
    std::cerr << "Error: invalid matrix size\n";
    return 2;
  }
  const std::size_t rows = static_cast< std::size_t >(r);
  const std::size_t cols = static_cast< std::size_t >(c);

  if (cols != 0 && rows > std::numeric_limits< std::size_t >::max() / cols) {
    std::cerr << "Error: matrix is too large\n";
    return 2;
  }

  bool ok = false;
  if (mode == 1) {
    if (rows * cols > sokolova::max_fix) {
      std::cerr << "Error: matrix is too large for fixed array\n";
      return 2;
    }
    ok = sokolova::runFixed(input, output, rows, cols);
  } else {
    ok = sokolova::runDynamic(input, output, rows, cols);
  }

  if (!ok) {
    std::cerr << "Error: invalid matrix data\n";
    return 2;
  }
  return 0;
}
