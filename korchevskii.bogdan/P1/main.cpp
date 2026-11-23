#include <iostream>
#include <limits>

namespace korchevskii
{
constexpr int unexpeted_input_error = 1;
constexpr int too_few_elements_error = 2;
constexpr int counter_overflow_error = 3;
constexpr int everithing_is_alright = 0;
}

int main()
{
  int input = 0;
  int max1 = 0;
  int max2 = std::numeric_limits< int >::min();
  int min = 0;
  unsigned long long count = 0;
  unsigned long long count_min = 0;

  while (std::cin >> input && input != 0) {
    ++count;

    if (count == 1) {
      max1 = input;
      min = input;
      count_min = 1;
      continue;
    }

    if (input >= max1) {
      max2 = max1;
      max1 = input;
    } else if (input > max2) {
      max2 = input;
    }

    if (input == min) {
      if (count_min == std::numeric_limits< unsigned long long >::max()) {
        std::cerr << "Counter overflow\n";
        return korchevskii::counter_overflow_error;
      }
      ++count_min;
    } else if (input < min) {
      min = input;
      count_min = 1;
    }
  }

  if (std::cin.fail()) {
    std::cerr << "Unexpected input\n";
    return korchevskii::unexpeted_input_error;
  }

  auto status = korchevskii::everithing_is_alright;

  if (count < 2) {
    std::cerr << "[SUB-MAX] The sequence must contain at least 2 elements\n";
    status = korchevskii::too_few_elements_error;
  } else {
    std::cout << max2 << '\n';
  }

  std::cout << count_min << '\n';
  return status;
}
