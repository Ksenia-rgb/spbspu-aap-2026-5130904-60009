#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace berezin
{
  constexpr std::size_t initial_capacity = 64;
  constexpr char end_line = '\n';
  constexpr char null_char = '\0';
  constexpr char second_string[] = "abs";

  enum class ErrorCode : int
  {
    success = 0,
    memory_error = 1,
    input_error = 2,
    output_error = 3
  };

  ErrorCode readLine(std::istream& input, char*& line);
  int hasRepeatedDigit(const char* str) noexcept;
  int hasCommonSymbol(const char* first, const char* second) noexcept;
  int runLab();
}

berezin::ErrorCode berezin::readLine(std::istream& input, char*& line)
{
  std::size_t capacity = initial_capacity;
  std::size_t length = 0;
  line = static_cast< char* >(std::malloc(capacity));
  if (line == nullptr)
  {
    return ErrorCode::memory_error;
  }

  char symbol = null_char;
  while (input.get(symbol))
  {
    if (symbol == end_line)
    {
      break;
    }
    if (symbol == null_char)
    {
      return ErrorCode::input_error;
    }
    if (length == capacity - 1)
    {
      if (capacity > std::numeric_limits< std::size_t >::max() / 2)
      {
        return ErrorCode::memory_error;
      }
      const std::size_t new_capacity = capacity * 2;
      char* const expanded = static_cast< char* >(std::malloc(new_capacity));
      if (expanded == nullptr)
      {
        return ErrorCode::memory_error;
      }
      for (std::size_t i = 0; i < length; i++)
      {
        expanded[i] = line[i];
      }
      std::free(line);
      line = expanded;
      capacity = new_capacity;
    }
    line[length] = symbol;
    length++;
  }

  if (input.bad() || (!input && !input.eof()) || (input.eof() && (length == 0)))
  {
    return ErrorCode::input_error;
  }
  line[length] = null_char;
  return ErrorCode::success;
}

int berezin::hasRepeatedDigit(const char* str) noexcept
{
  unsigned int digits = 0;
  for (std::size_t i = 0; str[i] != null_char; i++)
  {
    const unsigned char symbol = static_cast< unsigned char >(str[i]);
    if ((symbol >= '0') && (symbol <= '9') && (std::isdigit(symbol) != 0))
    {
      const unsigned int bit = 1u << (symbol - '0');
      if ((digits & bit) != 0)
      {
        return 1;
      }
      digits |= bit;
    }
  }
  return 0;
}

int berezin::hasCommonSymbol(const char* first, const char* second) noexcept
{
  for (std::size_t i = 0; first[i] != null_char; i++)
  {
    for (std::size_t j = 0; second[j] != null_char; j++)
    {
      if (first[i] == second[j])
      {
        return 1;
      }
    }
  }
  return 0;
}

int berezin::runLab()
{
  char* line = nullptr;
  const ErrorCode status = readLine(std::cin, line);
  if (status != ErrorCode::success)
  {
    if (status == ErrorCode::memory_error)
    {
      std::cerr << "Error: cannot allocate input buffer\n";
    }
    else
    {
      std::cerr << "Error: invalid input\n";
    }
    std::free(line);
    return static_cast< int >(status);
  }

  const int repeated_digits = hasRepeatedDigit(line);
  const int common_symbols = hasCommonSymbol(line, second_string);
  std::cout << repeated_digits << '\n' << common_symbols << '\n';
  std::cout.flush();
  std::free(line);
  if (!std::cout)
  {
    std::cerr << "Error: cannot write output\n";
    return static_cast< int >(ErrorCode::output_error);
  }
  return static_cast< int >(ErrorCode::success);
}

int main()
{
  return berezin::runLab();
}
