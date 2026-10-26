#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

constexpr int MAX_FIXED_SIZE = 10000;
constexpr char DIGIT_ZERO = '0';
constexpr char DIGIT_NINE = '9';
constexpr int MODE_FIXED = 1;
constexpr int MODE_DYNAMIC = 2;
constexpr int MAX_MODE = 2;
constexpr int ERROR_ARGS = 1;
constexpr int ERROR_INPUT = 2;

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cerr << "Invalid number of arguments\n";
    return ERROR_ARGS;
  }

  if (!*argv[1])
  {
    cerr << "First parameter is not a number\n";
    return ERROR_ARGS;
  }

  int mode = 0;
  bool out_of_range = false;
  for (const char *p = argv[1]; *p; ++p)
  {
    if (*p < DIGIT_ZERO || *p > DIGIT_NINE)
    {
      cerr << "First parameter is not a number\n";
      return ERROR_ARGS;
    }
    if (!out_of_range)
    {
      mode = mode * 10 + (*p - DIGIT_ZERO);
      if (mode > MAX_MODE)
      {
        out_of_range = true;
      }
    }
  }
  if (out_of_range || mode < MODE_FIXED)
  {
    cerr << "First parameter is out of range\n";
    return ERROR_ARGS;
  }

  ifstream in(argv[2]);
  if (!in)
  {
    cerr << "Cannot open input file\n";
    return ERROR_INPUT;
  }

  ofstream out(argv[3]);
  if (!out)
  {
    cerr << "Cannot open output file\n";
    return ERROR_INPUT;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0)
  {
    cerr << "Invalid matrix\n";
    return ERROR_INPUT;
  }

  const long long TOTAL_LONG = static_cast< long long >(rows) * cols;
  if (mode == MODE_FIXED && TOTAL_LONG > MAX_FIXED_SIZE)
  {
    cerr << "Matrix is too large for fixed storage\n";
    return ERROR_INPUT;
  }

  const size_t total = static_cast< size_t >(TOTAL_LONG);
  const bool IS_DYNAMIC = (mode == MODE_DYNAMIC);
  int fixed[MAX_FIXED_SIZE] = {};
  int *a = fixed;

  if (IS_DYNAMIC)
  {
    if (TOTAL_LONG > static_cast< long long >(
        numeric_limits< size_t >::max() / sizeof(int)))
    {
      cerr << "Matrix is too large\n";
      return ERROR_INPUT;
    }
    try
    {
      a = new int[total];
    }
    catch (const exception &)
    {
      cerr << "Memory allocation failed\n";
      return ERROR_INPUT;
    }
  }

  for (size_t i = 0; i < total; ++i)
  {
    if (!(in >> a[i]))
    {
      if (IS_DYNAMIC)
      {
        delete[] a;
      }
      cerr << "Invalid matrix\n";
      return ERROR_INPUT;
    }
  }

  char extra = 0;
  if (in >> extra)
  {
    if (IS_DYNAMIC)
    {
      delete[] a;
    }
    cerr << "Invalid matrix\n";
    return ERROR_INPUT;
  }

  int ans = 0;
  if (rows > 0 && cols > 0)
  {
    int best_len = 0;
    for (int col = 0; col < cols; ++col)
    {
      int cur_len = 1;
      int max_len = 1;
      for (int row = 1; row < rows; ++row)
      {
        const size_t IDX_PREV = static_cast< size_t >(row - 1) * cols + col;
        const size_t IDX_CUR = static_cast< size_t >(row) * cols + col;
        if (a[IDX_PREV] == a[IDX_CUR])
        {
          ++cur_len;
          if (cur_len > max_len)
          {
            max_len = cur_len;
          }
        }
        else
        {
          cur_len = 1;
        }
      }
      if (max_len > best_len)
      {
        best_len = max_len;
        ans = col + 1;
      }
    }
  }

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  size_t visited = 0;
  int k = 1;
  int side = 0;
  while (visited < total)
  {
    int pos = 0;
    int len = 0;
    int delta = 0;
    switch (side)
    {
    case 0:
      pos = bottom * cols + left;
      len = right - left + 1;
      delta = 1;
      --bottom;
      break;
    case 1:
      pos = bottom * cols + right;
      len = bottom - top + 1;
      delta = -cols;
      --right;
      break;
    case 2:
      pos = top * cols + right;
      len = right - left + 1;
      delta = -1;
      ++top;
      break;
    default:
      pos = top * cols + left;
      len = bottom - top + 1;
      delta = cols;
      ++left;
      break;
    }
    for (int i = 0; i < len && visited < total; ++i, pos += delta)
    {
      a[pos] += k++;
      ++visited;
    }
    side = (side + 1) & 3;
  }

  out << ans << '\n';
  out << rows << ' ' << cols;
  for (size_t i = 0; i < total; ++i)
  {
    out << ' ' << a[i];
  }
  out << '\n';

  if (IS_DYNAMIC)
  {
    delete[] a;
  }
  return 0;
}
