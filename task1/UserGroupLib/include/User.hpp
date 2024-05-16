#pragma once

#include <memory>
#include <string>

class Group;

class User {
public:
  User(int id, std::string &name);

  int GetUserId() const;
  std::string &GetName();

  int GetGroupId() const;
  Group *GetGroupPtr() const;
  void SetGroup(std::weak_ptr<Group> &group);

private:
  int _id;
  std::string _name;
  std::weak_ptr<Group> _group;
};