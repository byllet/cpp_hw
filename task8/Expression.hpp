#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class Expression {
public:
  virtual int Calculate(std::unordered_map<std::string, int> &map) = 0;
  virtual void Print(int offset) = 0;
  virtual void Add(std::shared_ptr<Expression> expression) {
    throw std::runtime_error("unsupported;");
  }

  void PrintTabs(int offset) {
    for (int i = 0; i < offset; ++i) {
      std::cout << "...";
    }
  }
};

class Constant : public Expression {
public:
  Constant(int value) : _value{value} {}
  int Calculate(std::unordered_map<std::string, int> &map) override {
    return _value;
  }
  void Print(int offset) override {
    PrintTabs(offset);
    std::cout << _value << '\n';
  }

private:
  int _value;
};

class Variable : public Expression {
public:
  Variable(const std::string &name) : _name{name} {}
  int Calculate(std::unordered_map<std::string, int> &map) override {
    return map[_name];
  }
  void Print(int offset) override {
    PrintTabs(offset);
    std::cout << _name << '\n';
  }

private:
  std::string _name;
};