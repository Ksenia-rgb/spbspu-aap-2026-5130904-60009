#include <iostream>
#include <stdexcept>
#include <limits>
namespace stamboliyski
{
  void taskSix(int new_num, int old_num, int &local_lenght, int &max_lenght, const int lim_check)
  {
    if (local_lenght == 0)
    {
      local_lenght++;
    }
    if (new_num >= old_num)
    {
      if (local_lenght > std::numeric_limits< int >::max() - lim_check)
      {
        throw std::logic_error("overflow");
      }
      local_lenght++;
    }
    else
    {
      local_lenght = 1;
    }
    if (local_lenght > max_lenght)
    {
      max_lenght = local_lenght;
    }
  }
  void taskSixteen(int new_num, int &smallest_num, int &lenght_count, const int lim_check)
  {
    if (new_num < smallest_num)
    {
      lenght_count = 1;
      smallest_num = new_num;
    }
    else if (new_num == smallest_num)
    {
      if (lenght_count > std::numeric_limits< int >::max() - lim_check)
      {
        throw std::logic_error("overflow");
      }
      lenght_count++;
    }
  }
}
int main()
{
  int task_six_local_lenght = 0;
  int task_six_longest = 0;
  int task_sixteen_smallest_element = 0;
  int task_sixteen_count = 0;
  int sequence_number = 0;
  int old_sequence_number = 0;
  const int invalid_arg_err = 1;
  const int logic_err = 2;
  const int num_lim = 1;
  try
  {
    if (!(std::cin >> sequence_number))
    {
      throw std::invalid_argument("error");
    }
    if (sequence_number == 0)
    {
      throw std::logic_error("error");
    }
    task_sixteen_count = sequence_number;
    task_sixteen_smallest_element = sequence_number;
    while (sequence_number != 0)
    {
      old_sequence_number = sequence_number;
      if (!(std::cin >> sequence_number))
      {
        throw std::invalid_argument("error");
      }
      if (sequence_number + task_six_longest == 0)
      {
        task_six_longest = 1;
      }
      if (sequence_number != 0)
      {
        stamboliyski::taskSix(sequence_number, old_sequence_number, task_six_local_lenght, task_six_longest, num_lim);
        stamboliyski::taskSixteen(sequence_number, task_sixteen_smallest_element, task_sixteen_count, num_lim);
      }
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Invalid Input\n";
    return invalid_arg_err;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << "Invalid Input / logic error\n";
    return logic_err;
  }
  std::cout << task_six_longest << "\n";
  std::cout << task_sixteen_count << "\n";
  return 0;
}
