#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Group.hpp"
#include "User.hpp"

class Manager {
public:
  Manager();

  bool AddNewUser(int user_id, std::string &username);
  bool DeleteUser(int user_id);
  const std::unordered_map<int, std::shared_ptr<User>> &GetUsers() const;
  std::shared_ptr<User> &GetUser(int user_id);
  bool IsUserExist(int user_id) const;

  bool AddNewGroup(int group_id);
  bool DeleteGroup(int group_id);
  const std::unordered_map<int, std::shared_ptr<Group>> &GetGroups() const;
  std::shared_ptr<Group> &GetGroup(int group_id);
  bool IsGroupExist(int group_id) const;

private:
  std::unordered_map<int, std::shared_ptr<User>> _users;
  std::unordered_map<int, std::shared_ptr<Group>> _groups;
};