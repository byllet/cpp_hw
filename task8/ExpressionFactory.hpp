#pragma once

#include "Expression.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class ExpressionFactory {
public:
  ExpressionFactory() {
    for (int i = -5; i < 257; ++i) {
      CreateConstant(i);
    }
  }

  std::shared_ptr<Constant> &CreateConstant(int c) {
    if (!_constants.contains(c)) {
      _constants[c] = std::make_shared<Constant>(c);
    }

    return _constants[c];
  }

  std::shared_ptr<Variable> &CreateVariable(const std::string &variable) {
    if (!_variables.contains(variable)) {
      _variables[variable] = std::make_shared<Variable>(variable);
    }

    return _variables[variable];
  }

  void DeleteConstant(int constant) {
    if (constant < -5 || constant > 257) {
      _constants.erase(constant);
    }
  }

  void DeleteVariable(const std::string &variabe) { _variables.erase(variabe); }

private:
  std::unordered_map<int, std::shared_ptr<Constant>> _constants;
  std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
