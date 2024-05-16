#pragma once

#include "HashSetImpl.hpp"
#include "LightSetImpl.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <class T> class Set {
public:
  Set() : _impl{std::make_unique<LightSetImpl<T>>()}, _size{0} {};

  void Add(T &&value);
  void Delete(T &&value);
  bool Contains(T &&value);

  std::vector<T> Union(Set<T> &other);
  std::vector<T> Intersect(Set<T> &other);

  std::vector<T> GetData();

protected:
  std::unique_ptr<SetImpl<T>> _impl;
  std::size_t _size;
};

template <class T> void Set<T>::Add(T &&value) {
  _impl->Add(std::forward<T>(value));

  if (_impl->Size() == 20) {
    std::vector<T> old = _impl->GetData();
    _impl.reset();
    _impl = std::make_unique<HashSetImpl<T>>();
    for (auto &el : old) {
      _impl->Add(std::forward<T>(el));
    }
  }
}

template <class T> void Set<T>::Delete(T &&value) {
  _impl->Delete(std::forward<T>(value));
}

template <class T> bool Set<T>::Contains(T &&value) {
  return _impl->Contains(std::forward<T>(value));
}

template <class T> std::vector<T> Set<T>::Union(Set<T> &other) {
  return _impl->Union(other._impl.get());
}

template <class T> std::vector<T> Set<T>::Intersect(Set<T> &other) {
  return _impl->Intersect(other._impl.get());
}

template <class T> std::vector<T> Set<T>::GetData() { return _impl->GetData(); }