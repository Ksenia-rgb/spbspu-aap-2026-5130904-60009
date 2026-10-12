#include <iostream>
#include <stdexcept>

void parseIn();
void cleanup();

int main()
{
  try {
    parseIn();
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}

void parseIn()
{
  int stored = 0;
  int stored_old = 0;
  int count_mon_inc = 0;
  int count_mon_inc_old = 0;
  int count_sgn_chg = 0;
  while (std::cin >> stored) {
    if (std::cin.fail()) {
      throw std::invalid_argument("Bad input, not a proper sequence!\n");
    }
    if (stored == 0) {
      break;
    }
    if (stored_old != 0) {
      if ((stored_old < 0 && stored > 0) || (stored_old > 0 && stored < 0)) {
        count_sgn_chg += 1;
      }
      if (stored >= stored_old) {
        count_mon_inc += 1;
      } else {
        if (count_mon_inc > count_mon_inc_old) {
          count_mon_inc_old = count_mon_inc;
        }
        count_mon_inc = 1;
      }
    } else {
      count_mon_inc = 1;
    }
    stored_old = stored;
  }
  if (std::cin.fail()) {
    throw std::invalid_argument("Bad input, not a proper sequence!\n");
  }

  if (count_mon_inc > count_mon_inc_old) {
    count_mon_inc_old = count_mon_inc;
  }
  std::cout << "count_mon_inc: " << count_mon_inc_old << "\n";
  std::cout << "count_sgn_chg: " << count_sgn_chg << "\n";
}
