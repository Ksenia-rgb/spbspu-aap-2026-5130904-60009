#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace skakov {

  constexpr int success = 0;
  constexpr int memory_error = 1;
  constexpr int input_error = 2;

  constexpr std::size_t start_capacity = 16;

  constexpr char exclude_symbols[] = "abc";
  constexpr char digits_source[] = "g1h2k";

  std::size_t getLength(const char* str) noexcept
  {
    std::size_t length = 0;
    while (str[length] != '\0') {
      ++length;
    }
    return length;
  }

  int hasSymbol(const char* str, char symbol) noexcept
  {
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
      if (str[i] == symbol) {
        return 1;
      }
    }
    return 0;
  }

  std::size_t countDigits(const char* str) noexcept
  {
    std::size_t count = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
      if (std::isdigit(static_cast< unsigned char >(str[i])) != 0) {
        ++count;
      }
    }
    return count;
  }

  char* excludeSecond(char* result, const char* first, const char* second) noexcept
  {
    std::size_t result_length = 0;
    for (std::size_t i = 0; first[i] != '\0'; ++i) {
      if (hasSymbol(second, first[i]) == 0) {
        result[result_length] = first[i];
        ++result_length;
      }
    }
    result[result_length] = '\0';
    return result;
  }

  char* addDigitsFromSecond(char* result, const char* first, const char* second) noexcept
  {
    std::size_t result_length = 0;
    for (std::size_t i = 0; first[i] != '\0'; ++i) {
      result[result_length] = first[i];
      ++result_length;
    }
    for (std::size_t i = 0; second[i] != '\0'; ++i) {
      if (std::isdigit(static_cast< unsigned char >(second[i])) != 0) {
        result[result_length] = second[i];
        ++result_length;
      }
    }
    result[result_length] = '\0';
    return result;
  }

  char* allocateString(std::size_t length) noexcept
  {
    if (length == std::numeric_limits< std::size_t >::max()) {
      return nullptr;
    }
    return static_cast< char* >(std::malloc(length + 1));
  }

  char* readLine(std::istream& input)
  {
    std::size_t capacity = start_capacity;
    char* line = static_cast< char* >(std::malloc(capacity));
    if (line == nullptr) {
      return nullptr;
    }

    std::size_t length = 0;
    char symbol = '\0';
    while (input.get(symbol) && symbol != '\n') {
      if (length + 2 > capacity) {
        if (capacity > std::numeric_limits< std::size_t >::max() / 2) {
          std::free(line);
          return nullptr;
        }
        const std::size_t new_capacity = capacity * 2;
        char* const new_line = static_cast< char* >(std::malloc(new_capacity));
        if (new_line == nullptr) {
          std::free(line);
          return nullptr;
        }
        for (std::size_t i = 0; i < length; ++i) {
          new_line[i] = line[i];
        }
        std::free(line);
        line = new_line;
        capacity = new_capacity;
      }
      line[length] = symbol;
      ++length;
    }
    line[length] = '\0';
    return line;
  }

  int run(std::istream& input, std::ostream& output, std::ostream& error)
  {
    if (input.peek() == std::istream::traits_type::eof()) {
      error << "Error: invalid input\n";
      return input_error;
    }
    char* const first = readLine(input);
    if (first == nullptr) {
      error << "Error: not enough memory\n";
      return memory_error;
    }

    const std::size_t first_length = getLength(first);
    char* const excluded = allocateString(first_length);
    char* const extended = allocateString(first_length + countDigits(digits_source));
    if (excluded == nullptr || extended == nullptr) {
      std::free(extended);
      std::free(excluded);
      std::free(first);
      error << "Error: not enough memory\n";
      return memory_error;
    }

    output << excludeSecond(excluded, first, exclude_symbols) << '\n';
    output << addDigitsFromSecond(extended, first, digits_source) << '\n';

    std::free(extended);
    std::free(excluded);
    std::free(first);
    return success;
  }

}

int main()
{
  return skakov::run(std::cin, std::cout, std::cerr);
}

