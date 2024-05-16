#pragma once

#include <type_traits>

template <class... ARGS> struct TypeList {};

// size of typelist
template <class TL> struct TypeListSize;

template <class... ARGS> struct TypeListSize<TypeList<ARGS...>> {
  static constexpr std::size_t value = sizeof...(ARGS);
};

template <class TL>
constexpr std::size_t TypeListSizeValue = TypeListSize<TL>::value;

// get element
template <std::size_t i, class TL> struct TypeListGet;

template <std::size_t i, class T, class... ARGS>
struct TypeListGet<i, TypeList<T, ARGS...>> {
  using type = typename TypeListGet<i - 1, TypeList<ARGS...>>::type;
};

template <class T, class... ARGS> struct TypeListGet<0, TypeList<T, ARGS...>> {
  using type = T;
};

// check if exist in list

template <class T, class TL> struct TypeListCheck;

template <class T, class V, class... ARGS>
struct TypeListCheck<T, TypeList<V, ARGS...>> {
  static constexpr bool value = TypeListCheck<T, TypeList<ARGS...>>::value;
};

template <class T, class... ARGS>
struct TypeListCheck<T, TypeList<T, ARGS...>> {
  static constexpr bool value = true;
};

template <class T> struct TypeListCheck<T, TypeList<>> {
  static constexpr bool value = false;
};

template <class T, class TL>
constexpr bool TypeListCheckValue = TypeListCheck<T, TL>::value;

// push back

template <class T, class TL> struct TypeListPushBack;

template <class T, class... ARGS>
struct TypeListPushBack<T, TypeList<ARGS...>> {
  using type = TypeList<ARGS..., T>;
};

// push front

template <class T, class TL> struct TypeListPushFront;

template <class T, class... ARGS>
struct TypeListPushFront<T, TypeList<ARGS...>> {
  using type = TypeList<T, ARGS...>;
};

// get index

template <class T, class TL> struct TypeListGetIndex;

template <class T, class V, class... ARGS>
struct TypeListGetIndex<T, TypeList<V, ARGS...>> {
  static constexpr std::size_t i =
      TypeListGetIndex<T, TypeList<ARGS...>>::i + 1;
};

template <class T, class... ARGS>
struct TypeListGetIndex<T, TypeList<T, ARGS...>> {
  static constexpr std::size_t i = 1;
};

template <class T, class TL>
constexpr std::size_t TypeListGetIndexValue = TypeListGetIndex<T, TL>::i - 1;
