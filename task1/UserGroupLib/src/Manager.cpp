#include "Manager.hpp"
#include "Group.hpp"
#include <memory>

Manager::Manager() {}

bool Manager::AddNewUser(int user_id, std::string &name) {
  if (IsUserExist(user_id)) {
    return false;
  }
  _users[user_id] = std::make_shared<User>(user_id, name);
  return true;
}

bool Manager::DeleteUser(int user_id) {
  if (IsUserExist(user_id) == 0) {
    return false;
  }
  _users.erase(user_id);
  return true;
}

const std::unordered_map<int, std::shared_ptr<User>> &
Manager::GetUsers() const {
  return _users;
}

std::shared_ptr<User> &Manager::GetUser(int user_id) { return _users[user_id]; }

bool Manager::IsUserExist(int user_id) const { return _users.count(user_id); }

bool Manager::AddNewGroup(int group_id) {
  if (IsGroupExist(group_id)) {
    return false;
  }

  _groups[group_id] = std::make_shared<Group>(group_id);
  return true;
}

bool Manager::DeleteGroup(int group_id) {
  if (IsGroupExist(group_id) == 0) {
    return false;
  }
  _groups.erase(group_id);
  return true;
}

const std::unordered_map<int, std::shared_ptr<Group>> &
Manager::GetGroups() const {
  return _groups;
}

std::shared_ptr<Group> &Manager::GetGroup(int group_id) {
  return _groups[group_id];
}

bool Manager::IsGroupExist(int group_id) const {
  return _groups.count(group_id);
}