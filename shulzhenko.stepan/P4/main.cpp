#include <iostream>
#include <cstddef>
#include <cctype>
#include <cstdlib>

namespace shulzhenko
{
  constexpr int success = 0;
  constexpr int cannot_in_dynamic_memory = 1;
  constexpr char null_char = '\0';

  char *readDynamicString(std::istream &in, bool &isMemoryError)
  {
    size_t cap = 16;
    size_t size = 0;
    char *buf = new char[cap];

    if (buf == nullptr)
    {
      isMemoryError = true;
      return nullptr;
    }

    char ch;
    while (in.get(ch) && ch != '\n')
    {
      if (size + 1 >= cap)
      {
        cap *= 2;
        char *new_buf = new char[cap];

        if (new_buf == nullptr)
        {
          delete[] buf;
          isMemoryError = true;
          return nullptr;
        }

        for (std::size_t i = 0; i < size; ++i)
        {
          new_buf[i] = buf[i];
        }

        delete[] buf;
        buf = new_buf;
      }
      buf[size++] = ch;
    }
    buf[size] = null_char;

    return buf;
  }

  char *exceptSecond(const char *first, const char *second, char *result)
  {
    if (first == nullptr || second == nullptr || result == nullptr)
    {
      return result;
    }

    std::size_t j = 0;

    for (std::size_t i = 0; first[i] != null_char; ++i)
    {
      bool found = false;

      for (std::size_t k = 0; second[k] != null_char; ++k)
      {
        if (first[i] == second[k])
        {
          found = true;
          break;
        }
      }

      if (!found)
      {
        result[j++] = first[i];
      }
    }
    result[j] = null_char;

    return result;
  }

  int hasRepeatedDigits(const char *str)
  {
    if (str == nullptr)
    {
      return success;
    }

    int digits[10] = {0};

    for (size_t i = 0; str[i] != null_char; ++i)
    {
      char ch = str[i];

      if (std::isdigit(ch))
      {
        int digit = str[i] - '0';

        if (digits[digit] != 0)
        {
          return cannot_in_dynamic_memory;
        }
        digits[digit] = 1;
      }
    }
    return success;
  }

  int laba()
  {
    bool mem_err = false;

    char *first_str = readDynamicString(std::cin, mem_err);

    if (mem_err)
    {
      std::cerr << "Error: Cannot allocate memory for input string.\n";
      return cannot_in_dynamic_memory;
    }

    char second_str[27];
    for (int i = 0; i < 26; ++i)
    {
      second_str[i] = 'a' + i;
    }
    second_str[26] = null_char;

    size_t len_first = 0;
    while (first_str[len_first] != null_char)
    {
      ++len_first;
    }

    char *result_str = new char[len_first + 1];

    if (result_str == nullptr)
    {
      std::cerr << "Error: Cannot allocate memory for result string.\n";
      delete[] first_str;
      return cannot_in_dynamic_memory;
    }

    exceptSecond(first_str, second_str, result_str);
    std::cout << result_str << '\n';

    std::cout << hasRepeatedDigits(first_str) << '\n';

    delete[] first_str;
    delete[] result_str;

    return success;
  }
}

int main()
{
  return shulzhenko::laba();
}
