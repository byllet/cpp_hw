#include <cstddef>
#include <iostream>
#include <memory>

#include "Expression.hpp"
#include "ExpressionFactory.hpp"
#include "Operators.hpp"

int main() {
  ExpressionFactory factory;
  std::shared_ptr<Expression> two = factory.CreateConstant(2);
  std::shared_ptr<Expression> x = factory.CreateVariable("x");
  std::shared_ptr<Expression> y = factory.CreateVariable("y");
  std::shared_ptr<Expression> z = factory.CreateVariable("z");
  std::shared_ptr<Expression> expression = std::make_shared<Addition>(two, x);
  expression->Add(y);
  expression->Add(std::make_shared<Multiply>(x, y));
  expression->Add(factory.CreateConstant(100));

  factory.DeleteVariable("x");

  std::unordered_map<std::string, int> context;
  context["x"] = 3;
  context["y"] = 6;
  context["z"] = 1;

  std::cout << expression->Calculate(context) << std::endl;
  expression->Print(0);

  return 0;
}