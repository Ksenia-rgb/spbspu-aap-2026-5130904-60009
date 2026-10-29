#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>

namespace chugunov
{
  const std::size_t FIXED_CAP = 10000;

// 9 варик
  std::size_t countNoEqual(const int * data, std::size_t rows, std::size_t cols)
  {
    std::size_t result = 0;
    for (std::size_t j = 0; j < cols; ++j) {
      bool hasEqual = false;
      for (std::size_t i = 1; i < rows; ++i) {
        if (data[i * cols + j] == data[(i - 1) * cols + j]) {
          hasEqual = true;
          break;
        }
      }
      if (!hasEqual) {
        ++result;
      }
    }
    return result;
  }

// 19 варик
  bool lowTriang(const int * data, std::size_t rows, std::size_t cols)
  {
    if (rows != cols || rows == 0) {
      return false;
    }
    for (std::size_t i = 0; i < rows; ++i) {
      for (std::size_t j = i + 1; j < cols; ++j) {
        if (data[i * cols + j] != 0) {
          return false;
        }
      }
    }
    return true;
  }

  bool readMatrix(std::istream & input, int * data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i) {
      if (!(input >> data[i])) {
        return false;
      }
    }
    return true;
  }

  bool writeRes(std::ostream & output, const int * data, std::size_t rows, std::size_t cols)
  {
    std::size_t count9 = countNoEqual(data, rows, cols);
    bool answer19 = lowTriang(data, rows, cols);
    output << count9 << ' ' << (answer19 ? "true" : "false") << '\n';
    return output.good();
  }

  bool run(std::istream & input, std::ostream & output, bool dynamic)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!(input >> rows >> cols)) {
      return false;
    }

    const std::size_t maxCount = static_cast< std::size_t >(-1) / sizeof(int);
    if (rows != 0 && cols > maxCount / rows) {
      return false;
    }
    const std::size_t count = rows * cols;

    if (!dynamic) {
      if (count > FIXED_CAP) {
        return false;
      }
      int fixed[FIXED_CAP];
      if (!readMatrix(input, fixed, count)) {
        return false;
      }
      return writeRes(output, fixed, rows, cols);
    }

    int * data = new (std::nothrow) int[count];
    if (data == nullptr) {
      return false;
    }
    bool ok = readMatrix(input, data, count) && writeRes(output, data, rows, cols);
    delete[] data;
    return ok;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <1|2> <input> <output>\n";
    return 1;
  }

  const char * mode = argv[1];
  if ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\0') {
    std::cerr << "mode only 1/2\n";
    return 1;
  }
  bool dynamic = (mode[0] == '2');

  std::ifstream input { argv[2] };
  if (!input) {
    std::cerr << "cant open input file\n";
    return 1;
  }
  std::ofstream output { argv[3] };
  if (!output) {
    std::cerr << "cant open output file\n";
    return 1;
  }

  if (!chugunov::run(input, output, dynamic)) {
    std::cerr << "invalid in/output\n";
    return 1;
  }
  return 0;
}
