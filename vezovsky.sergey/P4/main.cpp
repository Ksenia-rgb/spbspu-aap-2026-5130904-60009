#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace vezovsky
{
  constexpr std::size_t initial_capacity = 64;
  constexpr std::size_t alphabet_size = 26;
  constexpr char end_line = '\n';
  constexpr char null_char = '\0';
  constexpr char second_string[] = "abc";

  enum class ErrorCode : int
  {
    success = 0,
    memory_error = 1,
    input_error = 2,
    output_error = 3
  };

  ErrorCode readLine(std::istream& input, char*& line);
  std::size_t getLength(const char* str) noexcept;
  char* excludeSecond(char* result, const char* first, const char* second) noexcept;
  char* shortageSymbols(char* result, const char* str) noexcept;
  int runLab();
}

vezovsky::ErrorCode vezovsky::readLine(std::istream& input, char*& line)
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

std::size_t vezovsky::getLength(const char* str) noexcept
{
  std::size_t length = 0;
  while (str[length] != null_char)
  {
    length++;
  }
  return length;
}

char* vezovsky::excludeSecond(char* result, const char* first, const char* second) noexcept
{
  std::size_t length = 0;
  for (std::size_t i = 0; first[i] != null_char; i++)
  {
    bool found = false;
    for (std::size_t j = 0; second[j] != null_char; j++)
    {
      if (first[i] == second[j])
      {
        found = true;
        break;
      }
    }
    if (!found)
    {
      result[length] = first[i];
      length++;
    }
  }
  result[length] = null_char;
  return result;
}

char* vezovsky::shortageSymbols(char* result, const char* str) noexcept
{
  unsigned int present = 0;
  for (std::size_t i = 0; str[i] != null_char; i++)
  {
    const unsigned char symbol = static_cast< unsigned char >(str[i]);
    if (std::isalpha(symbol) != 0)
    {
      const unsigned char lower = static_cast< unsigned char >(std::tolower(symbol));
      if ((lower >= 'a') && (lower <= 'z'))
      {
        present |= 1u << (lower - 'a');
      }
    }
  }

  std::size_t length = 0;
  for (std::size_t i = 0; i < alphabet_size; i++)
  {
    if ((present & (1u << i)) == 0)
    {
      result[length] = static_cast< char >('a' + i);
      length++;
    }
  }
  result[length] = null_char;
  return result;
}

int vezovsky::runLab()
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

  char* excluded = static_cast< char* >(std::malloc(getLength(line) + 1));
  char* shortage = static_cast< char* >(std::malloc(alphabet_size + 1));
  if ((excluded == nullptr) || (shortage == nullptr))
  {
    std::cerr << "Error: cannot allocate result buffer\n";
    std::free(excluded);
    std::free(shortage);
    std::free(line);
    return static_cast< int >(ErrorCode::memory_error);
  }

  excludeSecond(excluded, line, second_string);
  shortageSymbols(shortage, line);
  std::cout << excluded << '\n' << shortage << '\n';
  std::cout.flush();
  std::free(excluded);
  std::free(shortage);
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
  return vezovsky::runLab();
}
