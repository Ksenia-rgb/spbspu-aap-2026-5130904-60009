#include <iostream>
#include <limits>

namespace berezin
{
  constexpr int success = 0;
  constexpr int invalid_input_error = 1;
  constexpr int impossible_calculation_error = 2;

  class GrtLssCounter
  {
  public:
    void add(int value) noexcept;
    bool print(std::ostream& output, std::ostream& error) const;

  private:
    int previous_ = 0;
    int current_ = 0;
    unsigned int count_ = 0;
    bool has_previous_ = false;
    bool has_current_ = false;
    bool overflow_ = false;
  };

  class DivRemCounter
  {
  public:
    void add(int value) noexcept;
    bool print(std::ostream& output, std::ostream& error) const;

  private:
    int previous_ = 0;
    unsigned int count_ = 0;
    bool has_previous_ = false;
    bool has_pair_ = false;
    bool overflow_ = false;
  };

  int process(std::istream& input, std::ostream& output, std::ostream& error);
}

void berezin::GrtLssCounter::add(int value) noexcept
{
  if (!has_previous_)
  {
    previous_ = value;
    has_previous_ = true;
    return;
  }
  if (!has_current_)
  {
    current_ = value;
    has_current_ = true;
    return;
  }
  if ((previous_ > current_) && (current_ > value) && !overflow_)
  {
    if (count_ == std::numeric_limits< unsigned int >::max())
    {
      overflow_ = true;
    }
    else
    {
      count_++;
    }
  }
  previous_ = current_;
  current_ = value;
}

bool berezin::GrtLssCounter::print(std::ostream& output, std::ostream& error) const
{
  if (overflow_)
  {
    error << "Error: overflow in GRT-LSS count\n";
    return false;
  }
  output << count_ << '\n';
  return true;
}

void berezin::DivRemCounter::add(int value) noexcept
{
  if (!has_previous_)
  {
    previous_ = value;
    has_previous_ = true;
    return;
  }
  has_pair_ = true;
  if (!overflow_ && ((previous_ == -1) || ((value % previous_) == 0)))
  {
    if (count_ == std::numeric_limits< unsigned int >::max())
    {
      overflow_ = true;
    }
    else
    {
      count_++;
    }
  }
  previous_ = value;
}

bool berezin::DivRemCounter::print(std::ostream& output, std::ostream& error) const
{
  if (!has_pair_)
  {
    error << "Error: not enough input values for DIV-REM\n";
    return false;
  }
  if (overflow_)
  {
    error << "Error: overflow in DIV-REM count\n";
    return false;
  }
  output << count_ << '\n';
  return true;
}

int berezin::process(std::istream& input, std::ostream& output, std::ostream& error)
{
  GrtLssCounter grt_lss;
  DivRemCounter div_rem;
  int value = 0;
  bool terminated = false;
  while (input >> value)
  {
    if (value == 0)
    {
      terminated = true;
      break;
    }
    grt_lss.add(value);
    div_rem.add(value);
  }

  if (!terminated)
  {
    error << "Error: invalid input\n";
    return invalid_input_error;
  }

  char extra = '\0';
  if ((input >> extra) || !input.eof() || input.bad())
  {
    error << "Error: extra data after \"0\"\n";
    return invalid_input_error;
  }

  const bool grt_lss_success = grt_lss.print(output, error);
  const bool div_rem_success = div_rem.print(output, error);
  if (!grt_lss_success || !div_rem_success)
  {
    return impossible_calculation_error;
  }
  return success;
}

int main()
{
  return berezin::process(std::cin, std::cout, std::cerr);
}
