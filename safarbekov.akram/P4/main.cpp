#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace safarbekov
{
  constexpr int exit_success = 0;
  constexpr int exit_memory_error = 1;

  class CharBuffer
  {
  public:
    CharBuffer(CharBuffer&& other) noexcept;
    CharBuffer(const CharBuffer&) = delete;
    explicit CharBuffer(std::size_t capacity);
    ~CharBuffer();

    CharBuffer& operator=(const CharBuffer&) = delete;
    CharBuffer& operator=(CharBuffer&&) = delete;

    char* getData();
    const char* getData() const;
    std::size_t getCapacity() const;
    void swap(CharBuffer& other) noexcept;

  private:
    char* data_;
    std::size_t capacity_;
  };

  CharBuffer readLine(std::istream& in);
  std::size_t getLength(const char* source);
  std::size_t removeLatinLetters(const char* source, char* destination);
  int hasRepeatedSymbols(const char* source);

  namespace
  {
    constexpr char null_terminator = '\0';
    constexpr char line_end = '\n';
    constexpr int result_true = 1;
    constexpr int result_false = 0;
    constexpr std::size_t initial_capacity = 16;
    constexpr std::size_t growth_factor = 2;
    constexpr std::size_t alphabet_size = static_cast< std::size_t >(std::numeric_limits< unsigned char >::max()) + 1;

    void growBuffer(CharBuffer& buffer, const std::size_t length)
    {
      if (buffer.getCapacity() > std::numeric_limits< std::size_t >::max() / growth_factor)
      {
        throw std::runtime_error("line is too long");
      }

      CharBuffer bigger(buffer.getCapacity() * growth_factor);

      for (std::size_t i = 0; i < length; ++i)
      {
        bigger.getData()[i] = buffer.getData()[i];
      }

      buffer.swap(bigger);
    }
  }
}

safarbekov::CharBuffer::CharBuffer(CharBuffer&& other) noexcept:
  data_(other.data_),
  capacity_(other.capacity_)
{
  other.data_ = nullptr;
  other.capacity_ = 0;
}

safarbekov::CharBuffer::CharBuffer(const std::size_t capacity):
  data_(static_cast< char* >(std::malloc(capacity))),
  capacity_(capacity)
{
  if (data_ == nullptr)
  {
    throw std::runtime_error("not enough memory");
  }
}

safarbekov::CharBuffer::~CharBuffer()
{
  std::free(data_);
}

char* safarbekov::CharBuffer::getData()
{
  return data_;
}

const char* safarbekov::CharBuffer::getData() const
{
  return data_;
}

std::size_t safarbekov::CharBuffer::getCapacity() const
{
  return capacity_;
}

void safarbekov::CharBuffer::swap(CharBuffer& other) noexcept
{
  char* const old_data = data_;
  const std::size_t old_capacity = capacity_;

  data_ = other.data_;
  capacity_ = other.capacity_;

  other.data_ = old_data;
  other.capacity_ = old_capacity;
}

safarbekov::CharBuffer safarbekov::readLine(std::istream& in)
{
  CharBuffer buffer(initial_capacity);
  std::size_t length = 0;
  char symbol = null_terminator;
  bool has_input = false;

  while (in.get(symbol) && symbol != line_end)
  {
    has_input = true;

    if (length + 1 >= buffer.getCapacity())
    {
      growBuffer(buffer, length);
    }

    buffer.getData()[length] = symbol;
    ++length;
  }

  if (!has_input && in.eof())
  {
    throw std::runtime_error("input is empty");
  }

  buffer.getData()[length] = null_terminator;
  return buffer;
}

std::size_t safarbekov::getLength(const char* const source)
{
  std::size_t length = 0;

  while (source[length] != null_terminator)
  {
    ++length;
  }

  return length;
}

std::size_t safarbekov::removeLatinLetters(const char* const source, char* const destination)
{
  std::size_t length = 0;

  for (std::size_t i = 0; source[i] != null_terminator; ++i)
  {
    if (std::isalpha(static_cast< unsigned char >(source[i])) == 0)
    {
      destination[length] = source[i];
      ++length;
    }
  }

  destination[length] = null_terminator;
  return length;
}

int safarbekov::hasRepeatedSymbols(const char* const source)
{
  int seen[alphabet_size] = {};

  for (std::size_t i = 0; source[i] != null_terminator; ++i)
  {
    const unsigned char symbol = static_cast< unsigned char >(source[i]);

    if (seen[symbol] != result_false)
    {
      return result_true;
    }

    seen[symbol] = result_true;
  }

  return result_false;
}

int main()
{
  try
  {
    const safarbekov::CharBuffer input = safarbekov::readLine(std::cin);
    safarbekov::CharBuffer output(safarbekov::getLength(input.getData()) + 1);

    safarbekov::removeLatinLetters(input.getData(), output.getData());

    std::cout << output.getData() << std::endl;
    std::cout << safarbekov::hasRepeatedSymbols(input.getData()) << std::endl;
  }
  catch (const std::exception& error)
  {
    std::cerr << "error: " << error.what() << std::endl;
    return safarbekov::exit_memory_error;
  }

  return safarbekov::exit_success;
}
