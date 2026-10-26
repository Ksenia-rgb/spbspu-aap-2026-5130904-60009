#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

bool fillMatrix(int *a, size_t sized, std::istream &input);
int solve(int *a, size_t n, size_t m, std::istream &input, std::ostream &output);
long int maxSumSdg(int *a, size_t n, size_t m);
long int minSumSdg(int *a, size_t n, size_t m);

int main(int argc, char *argv[])
{
  try {
    if (argc < 4) {
      throw std::invalid_argument("Not enough arguments\n");
    }
    if (argc > 4) {
      throw std::invalid_argument("Too many arguments\n");
    }
    char *memType = argv[1];
    char *inputName = argv[2];
    char *outputName = argv[3];
    std::ifstream input{inputName};
    std::ofstream output{outputName};
    if (!input) {
      throw std::invalid_argument("Bad input file argument\n");
    }
    if (!output) {
      throw std::invalid_argument("Bad output file argument\n");
    }
    size_t n = 0;
    size_t m = 0;
    if (!(input >> n >> m)) {
      std::cerr << "Wrong matrix size input\n";
      return 2;
    }

    int parsedMemType = 0;
    if (memType[1] != '\0') {
      throw std::invalid_argument("First parameter is not a number\n");
    }
    if (memType[0] != '1' && memType[0] != '2') {
      throw std::invalid_argument("First parameter is out of range\n");
    }
    if (memType[0] == '1') {
      int matrixed[10000] = {};
      return solve(matrixed, n, m, input, output);
    } else {
      if (n > std::numeric_limits<size_t>::max() / m) {
        std::cerr << "Matrix size input is too large\n";
        return 2;
      }
      size_t sized = n * m;
      int *matrixed = new int[sized];
      int retVal = solve(matrixed, n, m, input, output);
      delete[] matrixed;
      return retVal;
    }
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::bad_alloc &e) {
    std::cerr << e.what();
    return 2;
  } catch (...) {
    return 2;
  }
}

int solve(int *a, size_t n, size_t m, std::istream &input, std::ostream &output)
{
  if (!fillMatrix(a, n * m, input)) {
    std::cerr << "Wrong matrix value input\n";
    return 2;
  }

  output << maxSumSdg(a, n, m) << "\n" << minSumSdg(a, n, m) << "\n";
  if (!output) {
    std::cerr << "Issue with saving output\n";
    return 2;
  }

  return 0;
}

bool fillMatrix(int *a, size_t sized, std::istream &input) {
  for (size_t i = 0; i < sized; i++) {
    if (!(input >> a[i])) {
      return false;
    }
  }
  return true;
}

long int maxSumSdg(int *a, size_t n, size_t m)
{
  long int max = std::numeric_limits<long int>::min();
  size_t squareSide = n;
  if (squareSide > m) {
    squareSide = m;
  }
  for (size_t i = 0; i < squareSide; i++) {
    long int summed = 0;
    for (size_t j = 0; j < squareSide; j++) {
      summed += a[j * m + (i + j) % squareSide];
    }
    if (max > summed) {
      max = summed;
    }
  }
  return max;
}

long int minSumSdg(int *a, size_t n, size_t m)
{
  long int min = std::numeric_limits<long int>::max();
  size_t squareSide = n;
  if (squareSide > m) {
    squareSide = m;
  }
  for (size_t i = 0; i < squareSide; i++) {
    long int summed = 0;
    for (size_t j = 0; j < squareSide; j++) {
      summed += a[j * m + (i + j) % squareSide];
    }
    if (min > summed) {
      min = summed;
    }
  }
  return min;
}
