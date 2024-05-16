#pragma once

#include <stdexcept>
#include <type_traits>

template <class... Ts> struct TypeMap;

template <class T, class... Ts> struct TypeMap<T, Ts...> {
  T value;
  bool deleted = false;
  TypeMap<Ts...> *tail = nullptr;

  TypeMap() {
    if constexpr (sizeof...(Ts) > 0) {
      tail = new TypeMap<Ts...>;
    }
  }

  template <class U> void AddValue(U v) { AddValueImpl(v, *this); }

  template <class U> U GetValue() {
    if constexpr (std::is_same_v<T, U>) {
      if (!deleted)
        return value;
      throw std::runtime_error("deleted");
    } else {
      if (tail) {
        return tail->template GetValue<U>();
      }
    }
    throw std::runtime_error("err");
  }

  template <class U> bool Contains() {
    if constexpr (std::is_same_v<U, T>) {
      if (!deleted)
        return true;
    }

    if constexpr (sizeof...(Ts)) {
      if (tail)
        return tail->template Contains<U>();
    }

    return false;
  }

  template <class U> void RemoveValue() {
    if constexpr (std::is_same_v<U, T>) {
      if (!deleted)
        deleted = true;
      return;
    }

    if constexpr (std::is_same_v<U, T>) {
      if (deleted)
        throw std::runtime_error("deleting deleted");
    }

    if constexpr (sizeof...(Ts)) {
      if (tail) {
        tail->template RemoveValue<U>();
      }
      return;
    }

    throw std::runtime_error("err");
  }
};

//----------------------------------

template <class U, class T, class... Ts>
void AddValueImpl(U value, TypeMap<T, Ts...> &tm) {
  if (tm.tail)
    AddValueImpl(value, *tm.tail);
}

template <class T, class... Ts>
void AddValueImpl(T value, TypeMap<T, Ts...> &tm) {
  tm.value = value;
}
