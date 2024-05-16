#pragma once

#include <memory>
#include <vector>

class User;

class Group {
public:
  Group(int group_id);
  int GetGroupId() const;

  std::vector<std::weak_ptr<User>> &GetUsers();
  void AddUser(std::weak_ptr<User> &user);

private:
  int _id;
  std::vector<std::weak_ptr<User>> _users;
};