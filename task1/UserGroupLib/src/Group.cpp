#include "Group.hpp"

Group::Group(int group_id) : _id{group_id} {}

int Group::GetGroupId() const { return _id; }

std::vector<std::weak_ptr<User>> &Group::GetUsers() { return _users; }

void Group::AddUser(std::weak_ptr<User> &user) { _users.push_back(user); }
