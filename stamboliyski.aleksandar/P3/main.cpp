#include <iostream>
#include <fstream>
#include <stdexcept>

namespace stamboliyski
{
  int sedelementmodeone(const size_t rows, const size_t cols, int arr[100][100])
  {
    int countsedl = 0;
    for (size_t i = 0; i < rows; i++)
    {
      int snc = 0;
      bool check = true;
      for (size_t j = 0; j < cols; j++)
      {
        if (arr[i][j] < arr[i][snc])
        {
          snc = j;
        }
      }
      for (size_t j = 0; j < rows; j++)
      {
        if (arr[i][snc] < arr[j][snc])
        {
          check = false;
        }
      }
      if (check == true)
      {
        countsedl++;
      }
    }
    return countsedl;
  }
  int sedelementmodetwo(size_t rows, size_t cols, int **p)
  {
    int countsedl = 0;
    for (size_t i = 0; i < rows; i++)
    {
      int snc = 0;
      bool check = true;
      for (size_t j = 0; j < cols; j++)
      {
        if (p[i][j] < p[i][snc])
        {
          snc = j;
        }
      }
      for (size_t j = 0; j < rows; j++)
      {
        if (p[i][snc] < p[j][snc])
        {
          check = false;
        }
      }
      if (check == true)
      {
        countsedl++;
      }
    }
    return countsedl;
  }
  int equalcolumnnumone(const size_t rows, const size_t cols, int arr[100][100])
  {
    int colnum = 0;
    for (size_t i = 0; i < cols; i++)
    {
      int contnum = 1;
      for (size_t j = 0; j < rows; j++)
      {
        if (j != 0 && arr[j][i] == arr[j - 1][i])
        {
          contnum++;
        }
        else
        {
          contnum = 1;
        }
        if (contnum > colnum)
        {
          colnum = contnum;
        }
      }
    }
    return colnum;
  }
  int equalcolumnnumtwo(const size_t rows, const size_t cols, int **p)
  {
    int colnum = 0;
    for (size_t i = 0; i < cols; i++)
    {
      int contnum = 1;
      for (size_t j = 0; j < rows; j++)
      {
        if (j != 0 && p[j][i] == p[j - 1][i])
        {
          contnum++;
        }
        else
        {
          contnum = 1;
        }
        if (contnum > colnum)
        {
          colnum = contnum;
        }
      }
    }
    return colnum;
  }
}

int main(int argc, char **argv)
{
  size_t rows;
  size_t cols;
  const char *mode = argv[1];
  try
  {
    if (mode[0] != '1' && mode[0] != '2')
    {
      throw std::invalid_argument("Invalid mode");
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Invalid mode\n";
    return 1;
  }
  const char *inputpath = argv[2];
  const char *outputpath = argv[3];
  std::ifstream input(inputpath);
  try
  {
    if (!input.is_open())
    {
      throw std::invalid_argument("input did not open");
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Input did not open\n";
    return 1;
  }
  try
  {
    if (!(input >> rows >> cols))
    {
      throw std::invalid_argument("invalid row/col input");
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Invalid cow/rol input\n";
    return 2;
  }

  if (mode[0] == '1')
  {
    int matrix[100][100];
    try
    {
      for (size_t i = 0; i < rows; i++)
      {
        for (size_t j = 0; j < cols; j++)
        {
          if (!(input >> matrix[i][j]))
          {
            throw std::invalid_argument("invalid input into matrix");
          }
        }
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Invalid input into matrix";
      return 2;
    }
    input.close();
    std::ofstream output(outputpath);
    try
    {
      if (!output.is_open())
      {
        throw std::invalid_argument("output did not open");
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Output did not open";
      return 1;
    }
    output << stamboliyski::sedelementmodeone(rows, cols, matrix) << "\n";
    output << stamboliyski::equalcolumnnumone(rows, cols, matrix);
    output.close();
  }
  if (mode[0] == '2')
  {
    int **matrix = new int *[rows];
    try
    {
      for (size_t i; i < rows; i++)
      {
        matrix[i] = new int[cols];
      }
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << "Bad alloc at matrix creation";
      return 2;
    }
    try
    {
      for (size_t i = 0; i < rows; i++)
      {
        for (size_t j = 0; j < cols; j++)
        {
          if (!(input >> matrix[i][j]))
          {
            throw std::invalid_argument("invalid input into matrix");
          }
        }
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Invalid input into matrix";
      return 2;
    }
    input.close();
    std::ofstream output(outputpath);
    try
    {
      if (!output.is_open())
      {
        throw std::invalid_argument("output did not open");
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Output did not open";
      return 1;
    }
    output << stamboliyski::sedelementmodetwo(rows, cols, matrix) << "\n";
    output << stamboliyski::equalcolumnnumtwo(rows, cols, matrix);
    output.close();
    for (size_t i = 0; i < rows; i++)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  return 0;
}
