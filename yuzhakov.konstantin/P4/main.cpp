#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace yuzhakov {
  char *readLine(std::istream &in, size_t *length);
  char *commonSymbols(char *result, const char *first, const char *second) noexcept;
  int hasEqualAdjacent(const char *str) noexcept;
}

char *yuzhakov::readLine(std::istream &in, size_t *const length)
{
  size_t capacity = 32;
  size_t size = 0;
  char *buffer = new char[capacity];
  try {
    char symbol = '\0';
    while (in.get(symbol) && symbol != '\n') {
      if (symbol == '\0') {
        throw std::invalid_argument("null in input");
      }
      if (size == capacity - 1) {
        size_t const max_size = std::numeric_limits< size_t >::max();
        if (capacity == max_size) {
          throw std::length_error("input is too long");
        }
        size_t const new_capacity = capacity > max_size / 2 ? max_size : capacity * 2;
        char *const expanded = new char[new_capacity];
        for (size_t i = 0; i < size; ++i) {
          expanded[i] = buffer[i];
        }
        delete[] buffer;
        buffer = expanded;
        capacity = new_capacity;
      }
      buffer[size++] = symbol;
    }
    if (in.bad() || (in.fail() && !in.eof())) {
      throw std::runtime_error("error read");
    }
    buffer[size] = '\0';
    *length = size;
    return buffer;
  } catch (...) {
    delete[] buffer;
    throw;
  }
}

char *yuzhakov::commonSymbols(char *const result, const char *const first, const char *const second) noexcept
{
  size_t position = 0;
  for (size_t i = 0; first[i] != '\0'; ++i) {
    for (size_t j = 0; second[j] != '\0'; ++j) {
      if (first[i] == second[j]) {
        result[position++] = first[i];
        break;
      }
    }
  }
  result[position] = '\0';
  return result;
}

int yuzhakov::hasEqualAdjacent(const char *const str) noexcept
{
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] == str[i + 1]) {
      return 1;
    }
  }
  return 0;
}

int main()
{
  char *source = nullptr;
  char *result = nullptr;
  try {
    size_t length = 0;
    source = yuzhakov::readLine(std::cin, &length);

    const char *const second = "abc ef";
    result = new char[length + 1];

    yuzhakov::commonSymbols(result, source, second);
    int const adjacent = yuzhakov::hasEqualAdjacent(source);

    std::cout << result << '\n' << adjacent << '\n';
    std::cout.flush();
    if (!std::cout) {
      throw std::runtime_error("error write");
    }
  } catch (const std::exception &e) {
    delete[] result;
    delete[] source;
    std::cerr << e.what() << '\n';
    return 1;
  }
  delete[] result;
  delete[] source;
  return 0;
}
