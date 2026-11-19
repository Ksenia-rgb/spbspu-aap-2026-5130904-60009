#include <iostream>
#include <limits>
#include <stdexcept>

namespace savkin {
  size_t strlength(const char *str)
  {
    size_t count = 0;
    while (str[count] != '\0') {
      count += 1;
    }
    return count;
  }
  int cmnsym(const char *str1, const char *str2)
  {
    size_t len1 = strlength(str1);
    size_t len2 = strlength(str2);
    bool *existsInStr1 = new bool[256];
    for (size_t i = 0; i < len1; i++) {
      existsInStr1[static_cast< unsigned char >(str1[i])] = true;
    }
    size_t minimum = len2;
    if (len2 > len1) {
      minimum = len1;
    }
    char *str3 = new char[minimum];
    size_t counter = 0;

    bool *existsInStr2 = new bool[256];
    for (size_t i = 0; i < len2; i++) {
      unsigned char ch = static_cast< unsigned char >(str2[i]);
      if (existsInStr1[ch] && !existsInStr2[ch]) {
        str3[counter] = str2[i];
        existsInStr2[ch] = true;
        counter += 1;
      }
    }
    std::cout << str3 << "\n";
    delete[] str3;
    delete[] existsInStr2;
    delete[] existsInStr1;
    return 0;
  }

  int unitwo(const char *str1, const char *str2)
  {
    size_t len1 = strlength(str1);
    size_t len2 = strlength(str2);
    char *str3 = new char[len1 + len2];
    size_t maximum = len1;
    if (len2 > len1) {
      maximum = len2;
    }
    size_t counter = 0;
    for (size_t i = 0; i < maximum; i++) {
      if (i < len1) {
        str3[counter] = str1[i];
        counter += 1;
      }
      if (i < len2) {
        str3[counter] = str2[i];
        counter += 1;
      }
    }
    std::cout << str3 << "\n";
    delete[] str3;
    return 0;
  }
  void readLine(std::istream &input, char *&line)
  {
    size_t capacity = 128;
    size_t length = 0;
    line = new char[capacity];
    if (line == nullptr) {
      throw std::bad_alloc();
    }

    char symbol = '\0';
    while (input.get(symbol)) {
      if (symbol == '\n') {
        break;
      }
      if (symbol == '\0') {
        throw std::invalid_argument("Bad input!");
      }
      if (length == capacity - 1) {
        if (capacity > std::numeric_limits< std::size_t >::max() / 2) {
          throw std::bad_alloc();
        }
        size_t new_capacity = capacity * 2;
        char *expanded = new char[new_capacity];
        if (expanded == nullptr) {
          throw std::bad_alloc();
        }
        for (std::size_t i = 0; i < length; i++) {
          expanded[i] = line[i];
        }
        delete[] line;
        line = expanded;
        capacity = new_capacity;
      }
      line[length] = symbol;
      length++;
    }

    if (input.bad() || (!input && !input.eof()) || (input.eof() && (length == 0))) {
      throw std::invalid_argument("Bad input!");
    }
    line[length] = '\0';
  }
  int labRun()
  {
    try {
      char *str1 = nullptr;
      savkin::readLine(std::cin, str1);
      const char *str2 = "abc 123 hello";
      savkin::cmnsym(str1, str2);
      savkin::unitwo(str1, str2);

    } catch (const std::invalid_argument &e) {
      std::cerr << e.what();
      return 1;
    } catch (const std::bad_alloc &e) {
      std::cerr << e.what();
      return 2;
    } catch (...) {
      return 2;
    }
    return 0;
  }
  int main()
  {
    return savkin::labRun();
  }
