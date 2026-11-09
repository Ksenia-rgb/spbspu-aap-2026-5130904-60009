#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>

namespace shulzhenko
{
  constexpr int success = 0;
  constexpr int cannot_in_dynamic_memory = 1;
  constexpr int has_repeats = 1;
  constexpr char null_char = '\0';

  char *readDynamicString(std::istream &in, bool &is_memory_error)
  {
    std::size_t cap = 16;
    std::size_t size = 0;
    char *buf = nullptr;

    try
    {
      buf = new char[cap];
    }
    catch (const std::exception &)
    {
      is_memory_error = true;
      return nullptr;
    }

    char ch = 0;
    while (in.get(ch) && ch != '\n')
    {
      if (size + 1 >= cap)
      {
        char *new_buf = nullptr;

        try
        {
          new_buf = new char[cap * 2];
        }
        catch (const std::exception &)
        {
          delete[] buf;
          is_memory_error = true;
          return nullptr;
        }

        cap *= 2;

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

    for (std::size_t i = 0; str[i] != null_char; ++i)
    {
      const char ch = str[i];

      if (std::isdigit(static_cast< unsigned char >(ch)))
      {
        const int digit = ch - '0';

        if (digits[digit] != 0)
        {
          return has_repeats;
        }
        digits[digit] = 1;
      }
    }
    return success;
  }

  int laba()
  {
    bool mem_err = false;

    char *const first_str = readDynamicString(std::cin, mem_err);

    if (mem_err)
    {
      std::cerr << "Error: Cannot allocate memory for input string.\n";
      return cannot_in_dynamic_memory;
    }

    if (!std::cin && first_str[0] == null_char)
    {
      std::cerr << "Error: Empty input.\n";
      delete[] first_str;
      return cannot_in_dynamic_memory;
    }

    char second_str[27];
    for (std::size_t i = 0; i < 26; ++i)
    {
      second_str[i] = static_cast< char >('a' + i);
    }
    second_str[26] = null_char;

    std::size_t len_first = 0;
    while (first_str[len_first] != null_char)
    {
      ++len_first;
    }

    char *result_str = nullptr;

    try
    {
      result_str = new char[len_first + 1];
    }
    catch (const std::exception &)
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
