#include <iostream>
#include <stdexcept>
void task_six(int new_num, int old_num, int &local_lenght, int &max_lenght)
{
  if (local_lenght == 0)
  {
    local_lenght++;
  }
  if (new_num >= old_num)
  {
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
void task_sixteen(int new_num, int &smallest_num, int &lenght_count)
{
  if (new_num < smallest_num)
  {
    lenght_count = 1;
    smallest_num = new_num;
  }
  else if (new_num == smallest_num)
  {
    lenght_count++;
  }
}
int main()
{
  int task_six_local_lenght = 0;
  int task_six_longest = 0;
  int task_sixteen_smallest_element;
  int task_sixteen_count = 0;
  int sequence_number;
  int old_sequence_number;
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
        task_six(sequence_number, old_sequence_number, task_six_local_lenght, task_six_longest);
        task_sixteen(sequence_number, task_sixteen_smallest_element, task_sixteen_count);
      }
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Invalid Input\n";
    return 1;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << "Invalid Input / logic error\n";
    return 2;
  }
  std::cout << "task 6  : " << task_six_longest << "\ntask 16 : " << task_sixteen_count << "\n";
  return 0;
}
