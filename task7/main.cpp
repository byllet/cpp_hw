#include <iostream>
#include <ostream>
#include <vector>

#include "Set.hpp"

template <class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &&v) {
  for (const auto &el : v) {
    os << el << " ";
  }
  return os;
}

int main() {
  Set<int> set;
  set.Add(10);
  set.Add(12);
  set.Add(13);
  std::cout << set.Contains(10) << '\n';
  std::cout << set.Contains(100) << '\n';
  set.Delete(10);
  std::cout << set.Contains(10) << '\n';

  Set<int> set2;
  set2.Add(100);
  set2.Add(12);

  std::cout << set.Union(set2) << '\n';
  std::cout << set.GetData() << '\n';
  std::cout << set2.GetData() << '\n';
  std::cout << set.Intersect(set2) << '\n';

  for (size_t i = 300; i < 350; ++i) {
    set.Add(i);
  }

  std::cout << set.GetData() << '\n';
  std::cout << set.Intersect(set2) << '\n';
  return 0;
}
