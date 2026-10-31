#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace yuzhakov {
  const size_t max_size = 10000;

  bool number(const char *str);
  bool read(std::istream &in, int *a, size_t n);
  size_t min(size_t a, size_t b);
  long long minDiagSum(const int *a, size_t rows, size_t cols);
  void increase(int *a, size_t rows, size_t cols);
  void printMatrix(std::ostream &out, const int *a, size_t rows, size_t cols);
  void solve(int *a, size_t rows, size_t cols, std::ostream &out);
  bool run(int mode, std::istream &in, std::ostream &out);
}

bool yuzhakov::number(const char *const str)
{
  if (str[0] == '\0') {
    return false;
  }
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool yuzhakov::read(std::istream &in, int *const a, size_t n)
{
  for (size_t i = 0; i < n; ++i) {
    if (!(in >> a[i])) {
      return false;
    }
  }
  return true;
}

size_t yuzhakov::min(size_t a, size_t b)
{
  return a < b ? a : b;
}

long long yuzhakov::minDiagSum(const int *const a, size_t rows, size_t cols)
{
  size_t const n = min(rows, cols);
  if (n < 2) {
    return 0;
  }
  long long min_sum = a[0];
  for (size_t s = 1; s < 2 * n - 1; ++s) {
    if (s == n - 1) {
      continue;
    }
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
      if (i <= s && s - i < n) {
        sum += a[i * cols + (s - i)];
      }
    }
    if (sum < min_sum) {
      min_sum = sum;
    }
  }
  return min_sum;
}

void yuzhakov::increase(int *const a, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      size_t const layer = min(min(i, j), min(rows - 1 - i, cols - 1 - j));
      int const add = static_cast< int >(layer + 1);
      int &x = a[i * cols + j];
      if (x > std::numeric_limits< int >::max() - add) {
        throw std::overflow_error("overflow");
      }
      x += add;
    }
  }
}

void yuzhakov::printMatrix(std::ostream &out, const int *const a, size_t rows, size_t cols)
{
  out << rows << ' ' << cols;
  for (size_t i = 0; i < rows * cols; ++i) {
    out << ' ' << a[i];
  }
  out << '\n';
}

void yuzhakov::solve(int *const a, size_t rows, size_t cols, std::ostream &out)
{
  out << minDiagSum(a, rows, cols) << '\n';
  increase(a, rows, cols);
  printMatrix(out, a, rows, cols);
}

bool yuzhakov::run(int mode, std::istream &in, std::ostream &out)
{
  long long r = 0;
  long long c = 0;
  if (!(in >> r >> c) || r < 0 || c < 0) {
    return false;
  }
  size_t const rows = static_cast< size_t >(r);
  size_t const cols = static_cast< size_t >(c);
  if (rows != 0 && cols > std::numeric_limits< size_t >::max() / rows) {
    return false;
  }
  size_t const n = rows * cols;
  if (mode == 1) {
    if (n > max_size) {
      return false;
    }
    int a[max_size] = {};
    if (!read(in, a, n)) {
      return false;
    }
    solve(a, rows, cols, out);
    return true;
  }
  int *const a = new int[n];
  if (!read(in, a, n)) {
    delete[] a;
    return false;
  }
  try {
    solve(a, rows, cols, out);
  } catch (...) {
    delete[] a;
    throw;
  }
  delete[] a;
  return true;
}

int main(int argc, char *const *const argv)
{
  if (argc < 4) {
    std::cerr << "not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "too many arguments\n";
    return 1;
  }
  if (!yuzhakov::number(argv[1])) {
    std::cerr << "not a number\n";
    return 1;
  }
  if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2')) {
    std::cerr << "out of range\n";
    return 1;
  }
  int const mode = argv[1][0] - '0';
  std::ifstream input{argv[2]};
  if (!input) {
    std::cerr << "error open input\n";
    return 1;
  }
  std::ofstream output{argv[3]};
  if (!output) {
    std::cerr << "error open output\n";
    return 1;
  }
  try {
    if (!yuzhakov::run(mode, input, output)) {
      std::cerr << "error read matrix\n";
      return 2;
    }
  } catch (const std::overflow_error &e) {
    std::cerr << e.what() << '\n';
    return 2;
  } catch (const std::exception &) {
    std::cerr << "not enough memory\n";
    return 2;
  }
  if (!output) {
    std::cerr << "error write\n";
    return 2;
  }
  return 0;
}
