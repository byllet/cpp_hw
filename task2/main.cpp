#include "TypeList.hpp"
#include <iostream>

static_assert(TypeListSizeValue<TypeList<int, double, std::size_t>> == 3);
static_assert(std::is_same_v<
              TypeListGet<2, TypeList<int, std::string, float>>::type, float>);
static_assert(TypeListCheckValue<int, TypeList<int, std::string, float>> ==
              true);
static_assert(TypeListCheckValue<double, TypeList<int, std::string, float>> ==
              false);
static_assert(
    std::is_same_v<TypeList<int, float, std::string>,
                   TypeListPushBack<std::string, TypeList<int, float>>::type>);
static_assert(TypeListGetIndexValue<double, TypeList<int, float, double>> == 2);

int main() { return 0; }