#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

template <class T> struct Counter {
private:
  static std::size_t _instances_count;

public:
  Counter() { ++_instances_count; };
  static std::size_t InstancesCount() { return _instances_count; }
  ~Counter() { --_instances_count; }
};

template <class T> std::size_t Counter<T>::_instances_count = 0;

//-----------------

template <class D> struct less_than_comparable {
  bool operator<(const D &other) const {
    return static_cast<const D *>(this)->operator<(other);
  }
};

template <class D>
bool operator>(const less_than_comparable<D> &lhs,
               const less_than_comparable<D> &rhs) {
  return rhs < static_cast<const D &>(lhs);
}

template <class D>
bool operator<=(const less_than_comparable<D> &lhs,
                const less_than_comparable<D> &rhs) {
  return !(lhs > rhs);
}

template <class D>
bool operator>=(const less_than_comparable<D> &lhs,
                const less_than_comparable<D> &rhs) {
  return !(lhs < static_cast<const D &>(rhs));
}

template <class D>
bool operator==(const less_than_comparable<D> &lhs,
                const less_than_comparable<D> &rhs) {
  return (lhs >= rhs) && (lhs <= rhs);
}

template <class D>
bool operator!=(const less_than_comparable<D> &lhs,
                const less_than_comparable<D> &rhs) {
  return !(rhs == lhs);
}

class Number : public less_than_comparable<Number>, public Counter<Number> {
public:
  Number(int num) : _value{num} {}
  int GetValue() const { return _value; }
  bool operator<(const Number &other) const { return _value < other._value; }

private:
  int _value;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};
  assert(one >= one);
  assert(three <= four);
  assert(two == two);
  assert(three > two);
  assert(one < two);
  std::cout << "Count: " << Counter<Number>::InstancesCount() << std::endl;
  return 0;
}