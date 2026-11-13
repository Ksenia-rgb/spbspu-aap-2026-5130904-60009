#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace vezovsky
{
  const std::size_t start_size = 32;
  const std::size_t letters = 26;
  const char second[] = "abc";

  char* readLine(std::istream& in, int& error);
  std::size_t strLen(const char* s) noexcept;
  char* excludeChars(char* res, const char* a, const char* b) noexcept;
  char* missingLetters(char* res, const char* s) noexcept;
  int runLab();
}

char* vezovsky::readLine(std::istream& in, int& error)
{
  std::size_t size = start_size;
  std::size_t len = 0;
  error = 0;
  char* str = static_cast< char* >(std::malloc(size));
  if (str == nullptr)
  {
    error = 1;
    return nullptr;
  }

  char c = '\0';
  while (in.get(c) && c != '\n')
  {
    if (len + 1 == size)
    {
      const std::size_t newSize = size * 2;
      char* const bigger = static_cast< char* >(std::malloc(newSize));
      if (bigger == nullptr)
      {
        std::free(str);
        error = 1;
        return nullptr;
      }
      for (std::size_t i = 0; i < len; i++)
      {
        bigger[i] = str[i];
      }
      std::free(str);
      str = bigger;
      size = newSize;
    }
    str[len] = c;
    len++;
  }

  if (len == 0 && in.eof())
  {
    std::free(str);
    error = 2;
    return nullptr;
  }
  str[len] = '\0';
  return str;
}

std::size_t vezovsky::strLen(const char* s) noexcept
{
  std::size_t n = 0;
  while (s[n] != '\0')
  {
    n++;
  }
  return n;
}

char* vezovsky::excludeChars(char* res, const char* a, const char* b) noexcept
{
  std::size_t k = 0;
  for (std::size_t i = 0; a[i] != '\0'; i++)
  {
    int found = 0;
    for (std::size_t j = 0; b[j] != '\0'; j++)
    {
      if (a[i] == b[j])
      {
        found = 1;
      }
    }
    if (found == 0)
    {
      res[k] = a[i];
      k++;
    }
  }
  res[k] = '\0';
  return res;
}

char* vezovsky::missingLetters(char* res, const char* s) noexcept
{
  int used[letters] = {};
  for (std::size_t i = 0; s[i] != '\0'; i++)
  {
    const unsigned char c = static_cast< unsigned char >(s[i]);
    if (std::isalpha(c) != 0)
    {
      const int low = std::tolower(c);
      if (low >= 'a' && low <= 'z')
      {
        used[low - 'a'] = 1;
      }
    }
  }

  std::size_t k = 0;
  for (std::size_t i = 0; i < letters; i++)
  {
    if (used[i] == 0)
    {
      res[k] = static_cast< char >('a' + i);
      k++;
    }
  }
  res[k] = '\0';
  return res;
}

int vezovsky::runLab()
{
  int error = 0;
  char* const line = readLine(std::cin, error);
  if (line == nullptr)
  {
    if (error == 1)
    {
      std::cerr << "Error: not enough memory\n";
    }
    else
    {
      std::cerr << "Error: empty input\n";
    }
    return 1;
  }

  char* const first = static_cast< char* >(std::malloc(strLen(line) + 1));
  char* const last = static_cast< char* >(std::malloc(letters + 1));
  if (first == nullptr || last == nullptr)
  {
    std::cerr << "Error: not enough memory\n";
    std::free(first);
    std::free(last);
    std::free(line);
    return 1;
  }

  excludeChars(first, line, second);
  missingLetters(last, line);
  std::cout << first << '\n' << last << '\n';

  std::free(first);
  std::free(last);
  std::free(line);
  return 0;
}

int main()
{
  return vezovsky::runLab();
}
