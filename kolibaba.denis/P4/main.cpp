#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>

namespace kolibaba
{
  int seq_sym(const char *str) noexcept
  {
    for (std::size_t i = 0; str[i] != '\0' && str[i + 1] != '\0'; ++i)
    {
      if (str[i] == str[i + 1])
      {
        return 1;
      }
    }
    return 0;
  }

  void cmn_sym(const char *str1, const char *str2, char *out) noexcept
  {
    std::size_t k = 0;
    for (std::size_t i = 0; str1[i] != '\0'; ++i)
    {
      bool found = false;
      for (std::size_t j = 0; str2[j] != '\0'; ++j)
      {
        if (str1[i] == str2[j])
        {
          found = true;
          break;
        }
      }
      if (found)
      {
        out[k++] = str1[i];
      }
    }
    out[k] = '\0';
  }

  char *read_line(std::istream &in)
  {
    const std::size_t step = 32;
    std::size_t capacity = step;
    std::size_t length = 0;
    char *line = static_cast< char * >(std::malloc(capacity));
    if (!line)
    {
      return nullptr;
    }
    char c = 0;
    while (in.get(c) && c != '\n')
    {
      if (length + 1 == capacity)
      {
        char *bigger = static_cast< char * >(std::malloc(capacity + step));
        if (!bigger)
        {
          std::free(line);
          return nullptr;
        }
        for (std::size_t i = 0; i < length; ++i)
        {
          bigger[i] = line[i];
        }
        std::free(line);
        line = bigger;
        capacity += step;
      }
      line[length++] = c;
    }
    line[length] = '\0';
    return line;
  }
}

int main()
{
  char *line = kolibaba::read_line(std::cin);
  if (!line)
  {
    std::cerr << "not enough memory\n";
    return 1;
  }

  std::cout << kolibaba::seq_sym(line) << '\n';

  const char *second_str = "abc_ef";
  std::size_t max_len = std::strlen(line);
  char *result = static_cast< char * >(std::malloc(max_len + 1));
  
  if (!result)
  {
    std::cerr << "not enough memory\n";
    std::free(line);
    return 1;
  }

  kolibaba::cmn_sym(line, second_str, result);
  
  std::cout << result << '\n';

  std::free(result);
  std::free(line);
  return 0;
}	
