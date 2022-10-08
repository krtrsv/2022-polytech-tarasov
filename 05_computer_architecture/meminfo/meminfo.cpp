#include <iostream>
#include <fstream>
#include <cmath>

void show_meminfo()
{
  char parameter[20];
  int value;
  char unit[3];
  int total, free, avail;

  std::ifstream in("/proc/meminfo", std::ios_base::in);
  if(in.is_open()) {
    in >> parameter >> total >> unit;
    in >> parameter >> free >> unit;
    in >> parameter >> avail >> unit;
  } else {
    exit(1);
  }

  float percent = (total - avail) / static_cast<float>(total) * 100;
  short bars_count = round(percent/10);

  for (int i = 0; i != bars_count; ++i)
    std::cout << "|";
  for (int i = 0; i != 10 - bars_count; ++i)
    std::cout << ".";
  std::cout << " " << static_cast<int>(percent) << "%" << std::endl;
}

int main()
{
  show_meminfo();
  return 0;
}
