#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Expression.hpp"

class Operator {
public:
  Operator(const std::shared_ptr<Expression> &lhs,
           const std::shared_ptr<Expression> &rhs) {
    if (lhs) {
      _expresions.push_back(lhs);
    }

    if (rhs) {
      _expresions.push_back(rhs);
    }
  }

protected:
  std::vector<std::shared_ptr<Expression>> _expresions;

  void PrintWithOp(int offset, char op) {
    std::cout << op << '\n';
    for (const auto &expr : _expresions) {
      expr->Print(offset + 1);
    }
  }
};

class Addition : public Operator, public Expression {
public:
  Addition(const std::shared_ptr<Expression> &lhs,
           const std::shared_ptr<Expression> &rhs)
      : Operator(lhs, rhs) {}

  int Calculate(std::unordered_map<std::string, int> &map) override {
    int sum = 0;
    for (const auto expr : _expresions) {
      sum += expr->Calculate(map);
    }
    return sum;
  }

  void Add(std::shared_ptr<Expression> expresion) override {
    if (expresion) {
      _expresions.push_back(expresion);
    }
  }

  void Print(int offset) override {
    PrintTabs(offset);
    PrintWithOp(offset, '+');
  }
};

class Minus : public Operator, public Expression {
public:
  Minus(const std::shared_ptr<Expression> &lhs,
        const std::shared_ptr<Expression> &rhs)
      : Operator(lhs, rhs) {}

  int Calculate(std::unordered_map<std::string, int> &map) override {
    int sum = 0;
    for (const auto expr : _expresions) {
      sum -= expr->Calculate(map);
    }

    return sum;
  }

  void Add(std::shared_ptr<Expression> expresion) override {
    if (expresion) {
      _expresions.push_back(expresion);
    }
  }

  void Print(int offset) override {
    PrintTabs(offset);
    PrintWithOp(offset, '-');
  }
};

class Multiply : public Operator, public Expression {
public:
  Multiply(const std::shared_ptr<Expression> &lhs,
           const std::shared_ptr<Expression> &rhs)
      : Operator(lhs, rhs) {}

  int Calculate(std::unordered_map<std::string, int> &map) override {
    int mult = 1;
    for (const auto expr : _expresions) {
      mult *= expr->Calculate(map);
    }

    return mult;
  }

  void Add(std::shared_ptr<Expression> expresion) override {
    if (expresion) {
      _expresions.push_back(expresion);
    }
  }

  void Print(int offset) override {
    PrintTabs(offset);
    PrintWithOp(offset, '*');
  }
};

class Divide : public Operator, public Expression {
public:
  Divide(const std::shared_ptr<Expression> &lhs,
         const std::shared_ptr<Expression> &rhs)
      : Operator(lhs, rhs) {}
  int Calculate(std::unordered_map<std::string, int> &map) override {
    int mult = 0;
    for (const auto expr : _expresions) {
      mult /= expr->Calculate(map);
    }

    return mult;
  }

  void Add(std::shared_ptr<Expression> expresion) override {
    if (expresion) {
      _expresions.push_back(expresion);
    }
  }

  void Print(int offset) override {
    PrintTabs(offset);
    PrintWithOp(offset, '/');
  }
};