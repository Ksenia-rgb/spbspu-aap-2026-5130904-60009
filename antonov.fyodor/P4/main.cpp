#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>

namespace antonov
{

  enum StatusCode
  {
    status_ok = 0,
    status_no_memory = 1,
    status_no_input = 2
  };

  enum Capacity
  {
    chunk_size = 64,
    initial_capacity = 64,
    growth_factor = 2,
    null_terminator = 1
  };

  enum SymbolLimit
  {
    symbol_count = 256,
    one_occurrence = 1
  };

  static const char cannot_allocate[] = "Error: cannot allocate memory\n";
  static const char empty_input[] = "Error: empty input\n";

  static bool reserveLine(char *&line, const std::size_t length, std::size_t &capacity, const std::size_t required)
  {
    if (required <= capacity)
    {
      return true;
    }

    const std::size_t factor = static_cast< std::size_t >(growth_factor);
    const std::size_t limit = std::numeric_limits< std::size_t >::max();
    std::size_t next_capacity = capacity;
    while (next_capacity < required)
    {
      if (next_capacity > limit / factor)
      {
        next_capacity = required;
        break;
      }
      next_capacity *= factor;
    }

    char *fresh = nullptr;
    try
    {
      fresh = new char[next_capacity];
    }
    catch (const std::exception &)
    {
      return false;
    }

    for (std::size_t index = 0; index < length; ++index)
    {
      fresh[index] = line[index];
    }
    delete[] line;
    line = fresh;
    capacity = next_capacity;
    return true;
  }

  static bool appendChunk(
      char *&line, std::size_t &length, std::size_t &capacity, const char *const chunk, const std::size_t chunk_length)
  {
    const std::size_t limit = std::numeric_limits< std::size_t >::max();
    const std::size_t terminator = static_cast< std::size_t >(null_terminator);
    if (length >= limit || chunk_length > (limit - length) - terminator)
    {
      return false;
    }

    const std::size_t required = length + chunk_length + terminator;
    if (!reserveLine(line, length, capacity, required))
    {
      return false;
    }

    for (std::size_t index = 0; index < chunk_length; ++index)
    {
      line[length + index] = chunk[index];
    }
    length += chunk_length;
    line[length] = '\0';
    return true;
  }

  static std::size_t countChars(const char *const text)
  {
    std::size_t length = 0;
    while (text[length] != '\0')
    {
      ++length;
    }
    return length;
  }

  static char *readLine(int &status)
  {
    status = status_ok;
    std::size_t capacity = initial_capacity;
    std::size_t length = 0;
    char *line = nullptr;
    try
    {
      line = new char[capacity];
    }
    catch (const std::exception &)
    {
      std::cerr << cannot_allocate;
      status = status_no_memory;
      return nullptr;
    }
    line[0] = '\0';

    bool got_line = false;
    char chunk[chunk_size] = {};
    while (true)
    {
      std::cin.getline(chunk, static_cast< std::streamsize >(chunk_size));
      const bool failed = std::cin.fail();
      const bool ended = std::cin.eof();
      const std::size_t chunk_length = countChars(chunk);
      if (!got_line && failed && chunk_length == 0)
      {
        delete[] line;
        std::cerr << empty_input;
        status = status_no_input;
        return nullptr;
      }
      if (!appendChunk(line, length, capacity, chunk, chunk_length))
      {
        delete[] line;
        std::cerr << cannot_allocate;
        status = status_no_memory;
        return nullptr;
      }
      got_line = true;
      if (ended || !failed || chunk_length == 0)
      {
        break;
      }
      std::cin.clear();
    }
    return line;
  }

  static int countDistinctLatinLetters(const char *const text) noexcept
  {
    bool seen[symbol_count] = {};
    int count = 0;
    for (std::size_t index = 0; text[index] != '\0'; ++index)
    {
      const unsigned char symbol = static_cast< unsigned char >(text[index]);
      if (std::isalpha(symbol) == 0 || seen[symbol])
      {
        continue;
      }
      seen[symbol] = true;
      ++count;
    }
    return count;
  }

  static char *copyRepeatedSymbols(const char *const source, char *const destination) noexcept
  {
    std::size_t counts[symbol_count] = {};
    for (std::size_t index = 0; source[index] != '\0'; ++index)
    {
      const unsigned char symbol = static_cast< unsigned char >(source[index]);
      ++counts[symbol];
    }

    bool emitted[symbol_count] = {};
    std::size_t written = 0;
    for (std::size_t index = 0; source[index] != '\0'; ++index)
    {
      const unsigned char symbol = static_cast< unsigned char >(source[index]);
      if (counts[symbol] <= static_cast< std::size_t >(one_occurrence) || emitted[symbol])
      {
        continue;
      }
      destination[written] = source[index];
      ++written;
      emitted[symbol] = true;
    }
    destination[written] = '\0';
    return destination;
  }

}

int main()
{
  int status = antonov::status_ok;
  char *const line = antonov::readLine(status);
  if (line == nullptr)
  {
    return status;
  }

  const std::size_t length = antonov::countChars(line);
  char *repeated = nullptr;
  try
  {
    repeated = new char[length + static_cast< std::size_t >(antonov::null_terminator)];
  }
  catch (const std::exception &)
  {
    delete[] line;
    std::cerr << antonov::cannot_allocate;
    return antonov::status_no_memory;
  }

  std::cout << antonov::countDistinctLatinLetters(line) << '\n';
  std::cout << antonov::copyRepeatedSymbols(line, repeated) << '\n';
  delete[] repeated;
  delete[] line;
  return antonov::status_ok;
}
