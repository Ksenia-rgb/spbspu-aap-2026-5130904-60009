#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace safarbekov
{
  constexpr int exit_success = 0;
  constexpr int exit_invalid_sequence = 1;
  constexpr int exit_incalculable = 2;

  class AfterMaxCounter
  {
  public:
    void operator()(int next);
    std::size_t operator()() const;

  private:
    int max_ = 0;
    std::size_t count_after_ = 0;
    bool has_max_ = false;
  };

  class DescentMiddleCounter
  {
  public:
    void operator()(int next);
    std::size_t operator()() const;

  private:
    int previous_ = 0;
    int current_ = 0;
    std::size_t count_ = 0;
    bool has_previous_ = false;
    bool has_current_ = false;
  };

  int processSequence(std::istream& in, std::ostream& out, std::ostream& err);

  namespace
  {
    template< class Counter >
    int printCharacteristic(const Counter& counter, std::ostream& out, std::ostream& err)
   
    {
      try
      {
        out << counter() << std::endl;
      }
      catch (const std::logic_error& error)
      {
        err << error.what() << std::endl;
        return exit_incalculable;
      }
      return exit_success;
    }
  }
}

void safarbekov::AfterMaxCounter::operator()(const int next)
{
  if (!has_max_ || next > max_)
  {
    max_ = next;
    count_after_ = 0;
    has_max_ = true;
  }
  else
  {
    ++count_after_;
  }
}

std::size_t safarbekov::AfterMaxCounter::operator()() const
{
  if (!has_max_)
  {
    throw std::logic_error("sequence is empty, maximum does not exist");
  }
  return count_after_;
}

void safarbekov::DescentMiddleCounter::operator()(const int next)
{
  if (has_previous_ && previous_ > current_ && current_ > next)
  {
    ++count_;
  }
  if (has_current_)
  {
    previous_ = current_;
    has_previous_ = true;
  }
  current_ = next;
  has_current_ = true;
}

std::size_t safarbekov::DescentMiddleCounter::operator()() const
{
  return count_;
}

int safarbekov::processSequence(std::istream& in, std::ostream& out, std::ostream& err)
{
  AfterMaxCounter after_max;
  DescentMiddleCounter descent_middle;
  int number = 0;
  while (in >> number && number != 0)
  {
    after_max(number);
    descent_middle(number);
  }
  if (!in)
  {
    err << "input is not a sequence of integers terminated by zero" << std::endl;
    return exit_invalid_sequence;
  }
  const int after_max_code = printCharacteristic(after_max, out, err);
  const int descent_middle_code = printCharacteristic(descent_middle, out, err);
  if (after_max_code != exit_success)
  {
    return after_max_code;
  }
  return descent_middle_code;
}

int main()
{
  return safarbekov::processSequence(std::cin, std::cout, std::cerr);
}
