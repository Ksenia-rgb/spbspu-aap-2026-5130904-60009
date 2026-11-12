#include<iostream>
#include<stdexcept>
#include<cstdlib>

namespace stamboliyski
{
  void inputn_str(char *& arr, size_t& sizecount)
  {
    char temparr[51];
    std::cin >> temparr;
    sizecount = 0;
    size_t check = 0;
    for(size_t i = 0; i<=51; i++)
    {
      if(temparr[i]=='\0')
      {
        check = 1;
      }
      if(check == 0)
      {
        sizecount++;
      }
    }
    if(sizecount > 50)
    {
      throw std::bad_alloc();
    }
    arr = (char*)malloc(sizecount);
    for(size_t i = 0; i<sizecount; i++)
    {
      arr[i] = temparr[i];
    }
  }

  void popin(char * arr, size_t& index, char character)
  {
    arr[index] = character;
    index++;
  }

  void task_uni_two(char * arr_one, const size_t size_one, char* arr_two, const size_t size_two)
  {
    size_t higher = size_one;
    if(size_two > higher)
    {
      higher = size_two;
    }
    char * biggar = (char*)malloc(size_one + size_two + 1);
    size_t index = 0;
    for(size_t i = 0; i < higher; i++)
    {
      if(size_one > i)
      {
        popin(biggar, index, arr_one[i]);
      }
      if(size_two > i)
      {
        popin(biggar, index, arr_two[i]);
      }
    }
    std::cout<<biggar<<"\n";
    free(biggar);
  }

  void task_dgt_snd(char * arr_one, const size_t size_one, char* arr_two, const size_t size_two)
  {
    const char * nums = {"0123456789"};
    size_t count = 0;
    for(size_t i = 0; i<size_two; i++)
    {
      for(size_t j = 0; j < 10; j++)
      {
        if(arr_two[i] == nums[j])
        {
          count++;
        }
      }
    }
    char * numarr = (char*)malloc(count + 1);
    size_t index = 0;
    for(size_t i = 0; i<size_two; i++)
    {
      for(size_t j = 0; j < 10; j++)
      {
        if(arr_two[i] == nums[j])
        {
          popin(numarr, index, arr_two[i]);
        }
      }
    }
    std::cout<<arr_one<<numarr<<"\n";
    free(numarr);
  }
}

int main()
{
  char * str_one;
  size_t size_one = 0;
  char * str_two;
  size_t size_two = 0;
  try
  {
  stamboliyski::inputn_str(str_one, size_one);
  stamboliyski::inputn_str(str_two, size_two);
  }
  catch(const std::bad_alloc& c)
  {
    std::cerr<<"Memory problems ig?\n";
    return 1;
  }
  stamboliyski::task_uni_two(str_one, size_one, str_two, size_two);
  stamboliyski::task_dgt_snd(str_one, size_one, str_two, size_two);
  free(str_one);
  free(str_two);
  return 0;
}
