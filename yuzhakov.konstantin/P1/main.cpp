#include <cctype>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace yuzhakov {
  constexpr int calculate_error = 2;
  constexpr int invalid_input = 1;
  constexpr int success = 0;
  constexpr unsigned long long max_count = std::numeric_limits< unsigned long long >::max();

  class LocalMaxCounter {
  public:
    LocalMaxCounter();
    void operator()(int next) noexcept;
    unsigned long long operator()() const;
  private:
    int s1_;
    int s2_;
    unsigned int size_;
    unsigned long long count_;
    bool overflow_;
  };

  class PythagoreanCounter {
  public:
    PythagoreanCounter();
    void operator()(int next) noexcept;
    unsigned long long operator()() const;
  private:
    int s1_;
    int s2_;
    unsigned int size_;
    unsigned long long count_;
    bool overflow_;
  };

  bool readNumber(int &value);
  int p1();
}

yuzhakov::LocalMaxCounter::LocalMaxCounter():
  s1_(0),
  s2_(0),
  size_(0),
  count_(0),
  overflow_(false)
{}

void yuzhakov::LocalMaxCounter::operator()(int next) noexcept
{
  if (size_ == 2 && s1_ < s2_ && s2_ > next) {
    if (count_ == max_count) {
      overflow_ = true;
    } else {
      ++count_;
    }
  }
  s1_ = s2_;
  s2_ = next;
  if (size_ < 2) {
    ++size_;
  }
}

unsigned long long yuzhakov::LocalMaxCounter::operator()() const
{
  if (size_ == 0) {
    throw std::logic_error("c7: empty sequence");
  }
  if (overflow_) {
    throw std::overflow_error("c7 overflow");
  }
  return count_;
}

yuzhakov::PythagoreanCounter::PythagoreanCounter():
  s1_(0),
  s2_(0),
  size_(0),
  count_(0),
  overflow_(false)
{}

void yuzhakov::PythagoreanCounter::operator()(int next) noexcept
{
  if (size_ == 2) {
    long long const a = s1_;
    long long const b = s2_;
    long long const c = next;
    if (c * c - b * b == a * a) {
      if (count_ == max_count) {
        overflow_ = true;
      } else {
        ++count_;
      }
    }
  }
  s1_ = s2_;
  s2_ = next;
  if (size_ < 2) {
    ++size_;
  }
}

unsigned long long yuzhakov::PythagoreanCounter::operator()() const
{
  if (overflow_) {
    throw std::overflow_error("c13 overflow");
  }
  return count_;
}

bool yuzhakov::readNumber(int &value)
{
  if (!(std::cin >> value)) {
    return false;
  }
  if (std::cin.eof()) {
    return true;
  }
  int const next = std::cin.peek();
  if (std::cin.bad()) {
    return false;
  }
  return std::cin.eof() || std::isspace(static_cast< unsigned char >(next));
}

int yuzhakov::p1()
{
  LocalMaxCounter c7;
  PythagoreanCounter c13;
  int value = 0;

  while (true) {
    if (!readNumber(value)) {
      std::cerr << "invalid input" << '\n';
      return invalid_input;
    }
    if (value == 0) {
      break;
    }
    c7(value);
    c13(value);
  }

  int result = success;
  try {
    std::cout << c7() << '\n';
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    result = calculate_error;
  }
  try {
    std::cout << c13() << '\n';
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    result = calculate_error;
  }
  return result;
}

int main()
{
  return yuzhakov::p1();
}
