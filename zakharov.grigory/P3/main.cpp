#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>

namespace zakharov
{
  const size_t MAX_FIXED = 10000;

  // Читает размерности матрицы
  bool readSize(std::istream & in, size_t & rows, size_t & cols)
  {
    int r = 0, c = 0;
    if (!(in >> r >> c) || r < 0 || c < 0)
    {
      return false;
    }
    rows = static_cast< size_t >(r);
    cols = static_cast< size_t >(c);
    return true;
  }

  // Читает count элементов в уже выделенный массив (стек или new[])
  bool readElements(std::istream & in, int * data, size_t count)
  {
    for (size_t i = 0; i < count; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  // Вариант 3 [CNT-LOC-MAX]: количество элементов, строго больших всех соседей (8 соседей),
  // не лежащих на границе матрицы
  size_t countLocalMax(const int * a, size_t rows, size_t cols)
  {
    size_t count = 0;
    if (rows < 3 || cols < 3)
    {
      return 0;
    }
    for (size_t i = 1; i + 1 < rows; ++i)
    {
      for (size_t j = 1; j + 1 < cols; ++j)
      {
        int v = a[i * cols + j];
        bool isMax = true;
        for (size_t di = i - 1; di <= i + 1 && isMax; ++di)
        {
          for (size_t dj = j - 1; dj <= j + 1; ++dj)
          {
            if ((di != i || dj != j) && a[di * cols + dj] >= v)
            {
              isMax = false;
              break;
            }
          }
        }
        if (isMax)
        {
          ++count;
        }
      }
    }
    return count;
  }

  // Вариант 19 [LWR-TRI-MTX]: является ли матрица нижней треугольной.
  // Матрица обрезается до максимального квадрата (левый верхний угол)
  bool isLowerTriangular(const int * a, size_t rows, size_t cols)
  {
    size_t n = (rows < cols) ? rows : cols;
    if (n == 0)
    {
      return false;
    }
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        if (a[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  // Общая обработка для обоих способов хранения
  void process(const int * a, size_t rows, size_t cols, std::ostream & out)
  {
    out << countLocalMax(a, rows, cols) << '\n';
    out << std::boolalpha << isLowerTriangular(a, rows, cols) << '\n';
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return 1;
  }
  if (argv[1][0] == '\0' || argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2'))
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }
  const int num = argv[1][0] - '0';

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  size_t rows = 0, cols = 0;
  if (!zakharov::readSize(in, rows, cols))
  {
    std::cerr << "Error: input is not a matrix\n";
    return 2;
  }
  const size_t count = rows * cols;

  std::ofstream out(argv[3]);
  if (!out)
  {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  if (num == 1)
  {
    if (count > zakharov::MAX_FIXED)
    {
      std::cerr << "Error: matrix is too big for a fixed-size array\n";
      return 2;
    }
    int buffer[zakharov::MAX_FIXED] = {};
    if (!zakharov::readElements(in, buffer, count))
    {
      std::cerr << "Error: input is not a matrix\n";
      return 2;
    }
    zakharov::process(buffer, rows, cols, out);
  }
  else
  {
    int * data = nullptr;
    try
    {
      data = new int[count];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Error: not enough memory\n";
      return 2;
    }
    if (!zakharov::readElements(in, data, count))
    {
      delete[] data;
      std::cerr << "Error: input is not a matrix\n";
      return 2;
    }
    zakharov::process(data, rows, cols, out);
    delete[] data;
  }
  return 0;
}
