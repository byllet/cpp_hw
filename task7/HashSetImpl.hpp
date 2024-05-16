#pragma once

#include "SetImpl.hpp"
#include <functional>
#include <vector>

template <class T> class HashSetImpl : public SetImpl<T> {
public:
  HashSetImpl();
  void Add(T &&value) override;
  void Delete(T &&value) override;
  bool Contains(T &&value) override;
  std::size_t Size() const override;

  std::vector<T> Union(SetImpl<T> *other) override;
  std::vector<T> Intersect(SetImpl<T> *other) override;

  std::vector<T> GetData();

private:
  std::size_t Hash(T &&value) {
    return std::hash<T>{}(std::forward<T>(value)) % _data.size();
  }

  void Rehash();

  struct Value {
    bool exist = false;
    T value;
  };

  std::vector<Value> _data;
  std::size_t _size;
};

template <class T>
HashSetImpl<T>::HashSetImpl() : _data{std::vector<Value>(100)}, _size{0} {}

template <class T> void HashSetImpl<T>::Rehash() {
  if ((float)_size / (float)_data.size() > 0.7) {
    _data.resize(_data.size() * 2);
    for (auto &data : _data) {
      _data[Hash(Hash(std::forward<T>(data.value)))] = data;
    }
  }
}

template <class T> void HashSetImpl<T>::Add(T &&value) {
  std::size_t key = Hash(std::forward<T>(value));
  if (!_data[key].exist) {
    ++_size;
    _data[key].value = std::forward<T>(value);
    _data[key].exist = true;
  }

  Rehash();
}

template <class T> void HashSetImpl<T>::Delete(T &&value) {
  std::size_t key = Hash(std::forward<T>(value));
  if (_data[key].exist) {
    _data[key].exist = false;
    --_size;
  }
}

template <class T> bool HashSetImpl<T>::Contains(T &&value) {
  std::size_t key = Hash(std::forward<T>(value));

  if (_data[key].exist) {
    return true;
  }

  return false;
}

template <class T> std::size_t HashSetImpl<T>::Size() const { return _size; }

template <class T> std::vector<T> HashSetImpl<T>::Union(SetImpl<T> *other) {
  std::vector<T> res = GetData();
  for (auto &el : other->GetData()) {
    res.push_back(el);
  }
  return res;
}

template <class T> std::vector<T> HashSetImpl<T>::Intersect(SetImpl<T> *other) {
  std::vector<T> res;

  for (auto &el : other->GetData()) {
    if (_data[Hash(std::forward<T>(el))].exist) {
      res.push_back(el);
    }
  }

  return res;
}

template <class T> std::vector<T> HashSetImpl<T>::GetData() {
  std::vector<T> res;

  for (const auto &el : _data) {
    if (el.exist)
      res.push_back(el.value);
  }

  return res;
}