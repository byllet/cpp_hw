#pragma once

#include <vector>

template <class T> class SetImpl {
public:
  SetImpl() {}
  virtual void Add(T &&value) = 0;
  virtual void Delete(T &&value) = 0;
  virtual bool Contains(T &&value) = 0;
  virtual std::size_t Size() const = 0;

  virtual std::vector<T> Union(SetImpl<T> *other) = 0;
  virtual std::vector<T> Intersect(SetImpl<T> *other) = 0;

  virtual std::vector<T> GetData() = 0;
};
