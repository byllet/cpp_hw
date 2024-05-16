#pragma once

#include "SetImpl.hpp"

#include <algorithm>
#include <vector>

template <class T> class LightSetImpl : public SetImpl<T> {
public:
  LightSetImpl(){};
  void Add(T &&value) override;
  void Delete(T &&value) override;
  bool Contains(T &&value) override;
  std::size_t Size() const override { return _data.size(); }

  std::vector<T> Union(SetImpl<T> *other) override;
  std::vector<T> Intersect(SetImpl<T> *other) override;

  std::vector<T> GetData() { return _data; }

private:
  std::vector<T> _data;
};

template <class T> void LightSetImpl<T>::Add(T &&value) {
  _data.push_back(std::forward<T>(value));
}

template <class T> void LightSetImpl<T>::Delete(T &&value) {
  if (Contains(std::forward<T>(value))) {
    T v = value;
    auto value_place =
        std::find(this->_data.begin(), _data.end(), std::forward<T>(value));
    _data.erase(value_place);
  }
}

template <class T> bool LightSetImpl<T>::Contains(T &&value) {
  if (Size() && std::find(_data.begin(), _data.end(), std::forward<T>(value)) !=
                    _data.end()) {
    return true;
  }

  return false;
}

template <class T> std::vector<T> LightSetImpl<T>::Union(SetImpl<T> *other) {
  std::vector<T> res = _data;
  for (const auto &el : other->GetData()) {
    res.push_back(el);
  }
  return res;
}

template <class T>
std::vector<T> LightSetImpl<T>::Intersect(SetImpl<T> *other) {
  std::vector<T> res;
  for (const auto &el : other->GetData()) {
    if (std::find(_data.begin(), _data.end(), el) < _data.end()) {
      res.push_back(el);
    }
  }
  return res;
}