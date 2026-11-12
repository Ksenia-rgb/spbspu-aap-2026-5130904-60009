#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>
void transformUpperLower(const char * src, char * dest)
{
  if (src == nullptr || dest == nullptr)
  {
    return;
  }
  std::size_t i = 0;
  while (src[i] != '\0')
  {
    dest[i] = static_cast< char >(std::tolower(static_cast< unsigned char >(src[i])));
    ++i;
  }
  dest[i] = '\0';
}

int checkDuplicateDigits(const char * src)
{
  if (src == nullptr)
  {
    return 0;
  }
  int counts[10] = {};
  std::size_t i = 0;
  while (src[i] != '\0')
  {
    if (std::isdigit(static_cast< unsigned char >(src[i])) != 0)
    {
      int digit = src[i] - '0';
      ++counts[digit];
      if (counts[digit] > 1)
      {
        return 1;
      }
    }
    ++i;
  }
  return 0;
}

char * readString(std::istream & input, std::size_t & length)
{
  std::size_t capacity = 16;
  std::size_t len = 0;
  char * buffer = nullptr;
  try
  {
    buffer = new char[capacity];
    char c = 0;
    while (input.get(c) && c != '\n')
    {
      if (len + 1 >= capacity)
      {
        capacity *= 2;
        char * newBuffer = new char[capacity];
        for (std::size_t i = 0; i < len; ++i)
        {
          newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
      }
      buffer[len++] = c;
    }
    buffer[len] = '\0';
  }
  catch (const std::bad_alloc &)
  {
    delete[] buffer;
    return nullptr;
  }
  length = len;
  return buffer;
}

int run()
{
  std::size_t length = 0;
  char * input = readString(std::cin, length);
  if (input == nullptr)
  {
    std::cerr << "Error: memory allocation failed\n";
    return 1;
  }

  char * output = nullptr;
  try
  {
    output = new char[length + 1];
  }
  catch (const std::bad_alloc &)
  {
    delete[] input;
    std::cerr << "Error: memory allocation failed\n";
    return 1;
  }

  transformUpperLower(input, output);
  int hasDuplicate = checkDuplicateDigits(input);

  std::cout << output << '\n';
  std::cout << hasDuplicate << '\n';

  delete[] input;
  delete[] output;
  return 0;
}

int main()
{
  return run();
}
