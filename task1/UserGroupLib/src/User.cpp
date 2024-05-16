#include "User.hpp"
#include "Group.hpp"

User::User(int id, std::string &name) : _id{id}, _name{name} {}

int User::GetUserId() const { return _id; }

std::string &User::GetName() { return _name; }

int User::GetGroupId() const {
  if (GetGroupPtr()) {
    return GetGroupPtr()->GetGroupId();
  }
  return -1;
}

Group *User::GetGroupPtr() const { return _group.lock().get(); }

void User::SetGroup(std::weak_ptr<Group> &group) { _group = group; }
