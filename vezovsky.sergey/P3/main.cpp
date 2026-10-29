#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace vezovsky
{
  const std::size_t fixedlimit = 10000;

  bool readdimensions(std::istream& stream, std::size_t& outrows, std::size_t& outcols)
  {
    long long int rawrows = 0;
    long long int rawcols = 0;
    if (!(stream >> rawrows >> rawcols) || rawrows < 0 || rawcols < 0)
    {
      return false;
    }
    outrows = static_cast< std::size_t >(rawrows);
    outcols = static_cast< std::size_t >(rawcols);
    return outcols == 0 || outrows <= std::numeric_limits< std::size_t >::max() / outcols;
  }

  std::size_t findcolumnwithlongestrun(const int* matrix, std::size_t height, std::size_t width)
  {
    if (height == 0 || width == 0)
    {
      return 0;
    }
    std::size_t bestlength = 1;
    std::size_t bestcolumn = 1;
    for (std::size_t column = 0; column < width; column++)
    {
      std::size_t runlength = 1;
      for (std::size_t line = 1; line < height; line++)
      {
        runlength = (matrix[line * width + column] == matrix[(line - 1) * width + column]) ? runlength + 1 : 1;
        if (runlength > bestlength)
        {
          bestlength = runlength;
          bestcolumn = column + 1;
        }
      }
    }
    return bestcolumn;
  }

  void addspiral(int* cells, std::size_t rowcount, std::size_t colcount)
  {
    std::size_t upper = 0, leftedge = 0, lower = rowcount, rightedge = colcount;
    int addend = 1;
    while (upper < lower && leftedge < rightedge)
    {
      for (std::size_t bottomcol = leftedge; bottomcol < rightedge; bottomcol++)
      {
        cells[(lower - 1) * colcount + bottomcol] += addend++;
      }
      lower--;
      if (upper < lower)
      {
        for (std::size_t rightrow = lower; rightrow > upper; rightrow--)
        {
          cells[(rightrow - 1) * colcount + (rightedge - 1)] += addend++;
        }
        rightedge--;
      }
      if (upper < lower && leftedge < rightedge)
      {
        for (std::size_t topcol = rightedge; topcol > leftedge; topcol--)
        {
          cells[upper * colcount + (topcol - 1)] += addend++;
        }
        upper++;
      }
      if (upper < lower && leftedge < rightedge)
      {
        for (std::size_t leftrow = upper; leftrow < lower; leftrow++)
        {
          cells[leftrow * colcount + leftedge] += addend++;
        }
        leftedge++;
      }
    }
  }

  int processmatrix(std::istream& instream, std::ostream& outstream, int* values, std::size_t rownum, std::size_t colnum)
  {
    for (std::size_t readindex = 0; readindex < rownum * colnum; readindex++)
    {
      if (!(instream >> values[readindex]))
      {
        std::cerr << "error: invalid matrix data\n";
        return 2;
      }
    }
    char leftover = '\0';
    if (instream >> leftover)
    {
      std::cerr << "error: extra data after matrix\n";
      return 2;
    }
    outstream << findcolumnwithlongestrun(values, rownum, colnum) << '\n';
    addspiral(values, rownum, colnum);
    outstream << rownum << ' ' << colnum;
    for (std::size_t writeindex = 0; writeindex < rownum * colnum; writeindex++)
    {
      outstream << ' ' << values[writeindex];
    }
    outstream << '\n';
    if (!outstream)
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
    const char* mode = argv[1];
    if ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\0')
    {
      std::cerr << "error: first parameter must be 1 or 2\n";
      return 1;
    }
    std::ifstream infile{argv[2]};
    if (!infile)
    {
      std::cerr << "error: cannot open input file\n";
      return 1;
    }
    std::ofstream outfile{argv[3]};
    if (!outfile)
    {
      std::cerr << "error: cannot open output file\n";
      return 1;
    }
    std::size_t matrixrows = 0;
    std::size_t matrixcols = 0;
    if (!readdimensions(infile, matrixrows, matrixcols))
    {
      std::cerr << "error: invalid matrix size\n";
      return 2;
    }
    const std::size_t total = matrixrows * matrixcols;
    if (mode[0] == '1')
    {
      if (total > fixedlimit)
      {
        std::cerr << "error: matrix size is bigger than " << fixedlimit << "\n";
        return 2;
      }
      int stackdata[fixedlimit] = {};
      return processmatrix(infile, outfile, stackdata, matrixrows, matrixcols);
    }
    int* heapdata = nullptr;
    try
    {
      heapdata = new int[total];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "error: not enough memory\n";
      return 2;
    }
    int code = processmatrix(infile, outfile, heapdata, matrixrows, matrixcols);
    delete[] heapdata;
    return code;
  }
}

int main(int argc, char** argv)
{
  return vezovsky::runlab(argc, argv);
}
